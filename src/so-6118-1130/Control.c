#include "stderr.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_usage("");
    err_setlogopts(ERR_PID|ERR_MILLI);

    int fd[2], B, C, D;
    if (pipe(fd) < 0)
        err_syserr("pipe() failed: ");
    else if ((B = fork()) < 0)
        err_syserr("fork() B failed: ");
    else if (B == 0)
    {
        close(fd[0]);
        char arg1[12];
        snprintf(arg1, sizeof(arg1), "%d", fd[1]);
        char *args[] = { "PipeW1", arg1, NULL };
        execv(args[0], args);
        err_syserr("execv %s failed: ", args[0]);
    }
    else if ((C = fork()) < 0)
        err_syserr("fork() C failed: ");
    else if (C == 0)
    {
        close(fd[0]);
        char arg1[12];
        snprintf(arg1, sizeof(arg1), "%d", fd[1]);
        char *args[] = { "PipeW2", arg1, NULL };
        execv(args[0], args);
        err_syserr("execv %s failed: ", args[0]);
    }
    else if ((D = fork()) < 0)
        err_syserr("fork() D failed: ");
    else if (D == 0)
    {
        close(fd[1]);
        char arg1[12];
        snprintf(arg1, sizeof(arg1), "%d", fd[0]);
        char *args[] = { "PipeR", arg1, NULL };
        execv(args[0], args);
        err_syserr("execv %s failed: ", args[0]);
    }
    err_remark("Launched children B %d, C %d, D %d\n", B, C, D);
    close(fd[0]);
    close(fd[1]);
    int status;
    int corpse;
    while ((corpse = wait(&status)) > 0)
        err_remark("Child %d exited with status 0x%.4X\n", corpse, status);

    return(0);
}

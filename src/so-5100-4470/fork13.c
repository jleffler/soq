#include "stderr.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    int fd[2];
    int pid1;
    int pid2;

    if (pipe(fd) != 0)
        err_syserr("failed to pipe: ");
    if ((pid1 = fork()) < 0)
        err_syserr("failed to fork 1: ");
    else if (pid1 == 0)
    {
        char *sort[] = { "sort", 0 };
        if (dup2(fd[0], STDIN_FILENO) < 0)
            err_syserr("failed to dup2 read end of pipe to standard input: ");
        close(fd[0]);
        if (argc > 1)
            close(fd[1]);
        execvp(sort[0], sort);
        err_syserr("failed to exec %s: ", sort[0]);
    }
    else if ((pid2 = fork()) < 0)
        err_syserr("failed to fork 2: ");
    else if (pid2 == 0)
    {
        char *ls[] = { "ls", "-l", 0 };
        if (dup2(fd[1], STDOUT_FILENO) < 0)
            err_syserr("failed to dup2 write end of pipe to standard output: ");
        close(fd[1]);
        close(fd[0]);
        execvp(ls[0], ls);
        err_syserr("failed to exec %s: ", ls[0]);
    }
    else
    {
        int corpse;
        int status;
        close(fd[0]);
        close(fd[1]);
        printf("write end of pipe is%s closed for sort\n", (argc > 1) ? "" : " not");
        printf("shell process is PID %d\n", (int)getpid());
        printf("sort launched as PID %d\n", pid1);
        printf("ls   launched as PID %d\n", pid2);
        while ((corpse = wait(&status)) > 0)
            printf("%d exited with status 0x%.4X\n", corpse, status);
        printf("shell process is exiting\n");
    }
}

/* https://stackoverflow.com/questions/37893172/tcsetpgrps-enigmatic-behavior-in-this-very-short-program-in-c */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    pid_t pid = fork();
    if (pid < 0)
        err_syserr("Failed to fork: ");
    if (pid)
    {
        printf("Parent process (PID %d) forked child PID %d\n", (int)getpid(), (int)pid);
        if (setpgid(pid, pid) != 0)
            err_syserr("setpgid() failed: ");
        if (tcsetpgrp(STDIN_FILENO, pid) != 0)
            err_syserr("tcsetpgrp() failed: ");
        printf("tcsetpgrp(%d,%d) succeeded\n", STDIN_FILENO, (int)pid);
        int status;
        int corpse = waitpid(pid, &status, WUNTRACED);
        printf("PID %d exited with status 0x%.4X\n", corpse, status);
        if (argc > 1)
        {
            printf("Resetting pgrp\n");
            if (tcsetpgrp(STDIN_FILENO, getpgrp()) != 0)
                err_syserr("tcsetpgrp() to %d failed\n", (int)getpgrp());
        }
        while (1)
            ;
    }
    else
    {
        // child
        printf("Child process %d\n", (int)getpid());
        while (1)
            ;
    }
    return 0;
}

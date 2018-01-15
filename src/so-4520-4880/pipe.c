#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) != 0)
    {
        fprintf(stderr, "could not create pipe\n");
        return(1);
    }

    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "could not fork\n");
        return(1);
    }
    else if (pid == 0)
    {
        close(1);
        if (dup(fd[1]) != 1)
            return(1);
        close(fd[0]);
        close(fd[1]);
        char *arg1[] = { "./pre", 0 };
        execv(arg1[0], arg1);
        fprintf(stderr, "failed to execute %s\n", arg1[0]);
        return(1);
    }
    else
    {
        close(0);
        if (dup(fd[0]) != 0)
            return(1);
        close(fd[0]);
        close(fd[1]);
        char *arg2[] = { "./sort", 0 };
        execv(arg2[0], arg2);
        fprintf(stderr, "failed to execute %s\n", arg2[0]);
        return(1);
    }

    return 0;
}

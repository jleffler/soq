/* SO 4418-0272 */
/* Variant 1 - send messages terminated by newline only */
#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void wait_for(pid_t pid)
{
    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
    {
        printf("%d: PID %d exit status 0x%.4X\n", (int)getpid(), corpse, status);
        if (corpse == pid)
            break;
    }
}

static void write_log(int fd, const char *msg)
{
    ssize_t len = strlen(msg);
    if (write(fd, msg, len) != len)
    {
        fprintf(stderr, "%d: failed to write message to logger\n", (int)getpid());
        exit(EXIT_FAILURE);
    }
    printf("%d: Wrote: %zd [%s]\n", (int)getpid(), len, msg);
}

int main(void)
{
    int pipefd[2];
    pid_t pid;
    char szLogtest1[] = "Log Event: Blah blah blah\n";
    char szLogtest2[] = "Log Event: Blah blah 2\n";

    if (pipe(pipefd) != 0)
        exit(1);

    if ((pid = fork()) == -1)
    {
        fprintf(stderr, "Fork error!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("%d: I am child!\n", (int)getpid());
        close(pipefd[1]);     // close the write end of pipe

        while (1)
        {
            char readbuffer[512];
            int nbytes = read(pipefd[0], readbuffer, sizeof(readbuffer));
            if (nbytes <= 0)
            {
                close(pipefd[0]);
                printf("EOF on pipe -exiting\n");
                exit(EXIT_SUCCESS);
            }
            printf("%d: Logging string: %d [%s]\n", (int)getpid(), nbytes, readbuffer);
        }
    }
    else
    {
        printf("%d: I am parent!\n", (int)getpid());
        close(pipefd[0]);     // close read end of pipe

        write_log(pipefd[1], szLogtest1);
        write_log(pipefd[1], szLogtest2);
        close(pipefd[1]);
        wait_for(pid);
    }

    return 0;
}

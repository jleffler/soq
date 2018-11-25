/* SO 4418-0272 */
/* Variant 2 - send message length (1..255) and message */
#include "posixver.h"
#include <assert.h>
#include <limits.h>
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
    unsigned char byte = len;
    assert(len > 0 && len <= UCHAR_MAX);

    if (write(fd, &byte, sizeof(byte)) != sizeof(byte) ||
        write(fd, msg, len) != len)
    {
        fprintf(stderr, "%d: failed to write message to logger\n", (int)getpid());
        exit(EXIT_FAILURE);
    }
    printf("%d: Wrote: %zd [%s]\n", (int)getpid(), len, msg);
}

static int read_log(int fd, size_t buflen, char buffer[buflen])
{
    unsigned char byte;
    if (read(fd, &byte, sizeof(byte)) != sizeof(byte))
    {
        fprintf(stderr, "%d: EOF on file descriptor %d\n", (int)getpid(), fd);
        return 0;
    }
    if (buflen < (size_t)(byte + 1))        // avoid signed/unsigned comparison
    {
        fprintf(stderr, "%d: buffer length %zu cannot hold %d bytes\n",
                (int)getpid(), buflen, byte + 1);
        exit(EXIT_FAILURE);
    }
    if (read(fd, buffer, byte) != byte)
    {
        fprintf(stderr, "%d: failed to read %d bytes from file descriptor %d\n",
                (int)getpid(), byte, fd);
        exit(EXIT_FAILURE);
    }
    buffer[byte] = '\0';
    return byte;
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

        char readbuffer[512];
        int nbytes;
        while ((nbytes = read_log(pipefd[0], sizeof(readbuffer), readbuffer)) > 0)
        {
            printf("%d: Logging string: %d [%s]\n", (int)getpid(), nbytes, readbuffer);
        }
        close(pipefd[0]);
        printf("EOF on pipe -exiting\n");
        exit(EXIT_SUCCESS);
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

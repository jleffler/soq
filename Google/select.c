#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/stat.h>
#include "stderr.h"

static inline int max(int a, int b) { return (a > b) ? a : b; }

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    if (argc != 1)
        err_usage("");

    char const fifoname[] = "test.fifo";
    if (mkfifo(fifoname, 0600) != 0)
        err_syserr("Failed to create FIFO %s\n", fifoname);
    int fd_p[2];
    if (pipe(fd_p) != 0)
        err_syserr("Failed to create pipe\n");
    int fd_f = open(fifoname, O_RDONLY | O_NONBLOCK);

    int mode = fcntl(fd_p[0], F_GETFL);
    if (mode < 0)
        err_syserr("Unexpected mode %d from fcntl()\n", mode);
    mode |= O_NONBLOCK;
    if (fcntl(fd_p[0], F_SETFL, mode) != 0)
        err_syserr("Failed to F_SETFL in fcntl()\n");

    for (int i = 0; i < 10; i++)
    {
        struct timeval t = { .tv_sec = 1, .tv_usec = 0 };
        fd_set rd_set;
        FD_ZERO(&rd_set);
        FD_SET(fd_p[0], &rd_set);
        FD_SET(fd_f, &rd_set);
        int max_fd = max(fd_f, fd_p[0]) + 1;
        int nbits;
        if ((nbits = select(max_fd, &rd_set, 0, 0, &t)) < 0)
            err_sysrem("select() failed: ");
        else
        {
            int count = 0;
            for (int j = 0; j < max_fd; j++)
            {
                if (FD_ISSET(j, &rd_set))
                {
                    if (j == fd_p[0])
                    {
                        printf("%d: Pipe (%d) ready for reading\n", i, fd_p[0]);
                        count++;
                    }
                    else if (j == fd_f)
                    {
                        printf("%d: FIFO (%d) ready for reading\n", i, fd_f);
                        count++;
                    }
                }
            }
            if (count == 0)
                printf("%d: no file descriptors ready for reading\n", i);
        }
    }

    close(fd_p[0]);
    close(fd_p[1]);
    close(fd_f);
    unlink(fifoname);
    return 0;
}


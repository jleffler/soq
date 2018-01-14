/* SO 4825-2451 */
/*
** The question asks about epoll() which is a Linux-specific extension.
** This code was developed on a Mac running macOS High Sierra 10.13.2,
** where epoll() is not available.  However, it helps make a point, that
** once there are no processes with a FIFO open for writing, the reader
** continually gets 0 bytes returned until another process opens the
** FIFO for writing.
** The writer process currently writes a random amount of random
** upper-case alphabetic data to the reader on each of a random number
** of iterations.  It should have a random nap before writing on each
** iteration, and a random nap before closing the file descriptor.
*/
#include "fifo-tst-41.h"
#include "stderr.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static size_t wr_fifo(int fd, const char *name, size_t buflen, char buffer[buflen])
{
    err_remark("Write to FIFO '%s'\n", name);
    ssize_t nbytes = write(fd, buffer, buflen);
    if (nbytes < 0)
        err_syserr("Failed to write to FIFO '%s': ", name);
    err_remark("%zu bytes written to FIFO '%s'\n", (size_t)nbytes, name);
    return nbytes;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_usage("");

    struct stat sb;
    if (stat(FIFO, &sb) != 0 || !S_ISFIFO(sb.st_mode))
    {
        err_remark("Creating FIFO '%s'\n", FIFO);
        if (mkfifo(FIFO, 0644) != 0)
            err_syserr("failed to create FIFO '%s': ", FIFO);
    }
    err_setlogopts(ERR_PID|ERR_MILLI);

    err_remark("Open FIFO '%s' for writing\n", FIFO);
    int fd = open(FIFO, O_WRONLY);
    if (fd == -1)
        err_syserr("failed to open FIFO '%s' for writing: ", FIFO);
    err_remark("FIFO '%s' opened for writing\n", FIFO);
    srand(getpid());

    int limit = rand() % 4 + 1;
    for (int i = 0; i < limit; i++)
    {
        char buffer[1024];
        int count = rand() % 1024 + 1;
        for (int j  = 0; j < count; j++)
            buffer[j] = rand() % 26 + 'A';
        size_t nbytes;
        if ((nbytes = wr_fifo(fd, FIFO, count, buffer)) > 0)
            err_remark("Data: [%.*s]\n", (int)nbytes, buffer);
    }

    close(fd);
    return 0;
}

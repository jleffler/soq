/* SO 4825-2451 */
/*
** The question asks about epoll() which is a Linux-specific extension.
** This code was developed on a Mac running macOS High Sierra 10.13.2,
** where epoll() is not available.  However, it helps make a point, that
** once there are no processes with a FIFO open for writing, the reader
** continually gets 0 bytes returned until another process opens the
** FIFO for writing.  It goes into a busy loop unless you're careful.
** This code naps for a random time (between 0.250 and 0.750 seconds) to
** avoid busy waiting.  Another option is to close the FIFO on getting
** EOF and then reopening the FIFO; the open hangs until there is a
** process that has opened the FIFO for writing.  A third option is to
** have the reading process also open the file for writing (best to use
** a separate file descriptor for that; the result is undefined if you
** open a FIFO with O_RDWR *ccording to POSIX).  Of course, since
** open-for-reading blocks until there's a writer, and open-for-writing
** blocks until there's a reader, you can't open the writing file
** descriptor until after the reading open has succeeded.
*/
#include "fifo-tst-41.h"
#include "stderr.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

static size_t rd_fifo(int fd, const char *name, size_t buflen, char buffer[buflen])
{
    err_remark("Read from FIFO '%s'\n", name);
    ssize_t nbytes = read(fd, buffer, buflen);
    if (nbytes < 0)
        err_syserr("Failed to read from FIFO '%s': ", name);
    err_remark("%zu bytes read from FIFO '%s'\n", (size_t)nbytes, name);
    return nbytes;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_usage("");
    err_setlogopts(ERR_PID|ERR_MILLI);

    struct stat sb;
    if (stat(FIFO, &sb) != 0 || !S_ISFIFO(sb.st_mode))
    {
        err_remark("Creating FIFO '%s'\n", FIFO);
        if (mkfifo(FIFO, 0644) != 0)
            err_syserr("failed to create FIFO '%s': ", FIFO);
    }

    err_remark("Open FIFO '%s' for reading\n", FIFO);
    int fd = open(FIFO, O_RDONLY);
    if (fd == -1)
        err_syserr("failed to open FIFO '%s' for reading: ", FIFO);
    err_remark("FIFO '%s' opened for reading\n", FIFO);

    while (1)
    {
        char buffer[1024];
        size_t nbytes;
        while ((nbytes = rd_fifo(fd, FIFO, sizeof(buffer), buffer)) > 0)
            err_remark("Data: [%.*s]\n", (int)nbytes, buffer);
        random_milli_nap(250, 750);
    }
    /* Effectively not reached */

    close(fd);
    return 0;
}

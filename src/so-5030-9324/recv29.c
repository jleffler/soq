#include "request.h"
#include "stderr.h"     /* See https://github.com/jleffler/soq/tree/master/src/libsoq */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   /* mkfifo() */
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc > 0)               // Use argc - avoid unused argument warning
        err_setarg0(argv[0]);

    /* Maybe the other program already created it? */
    if (mkfifo(FIFO_NAME, 0666) != 0 && errno != EEXIST)
        err_syserr("failed to create FIFO %s: ", FIFO_NAME);

    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0)
        err_syserr("failed to open FIFO %s for reading: ", FIFO_NAME);

    printf("Recv: PID %d at work with FIFO %s open for reading\n", (int)getpid(), FIFO_NAME);

    struct request req;
    struct request *rp = 0;
    if (read(fd, &req, sizeof(req)) != sizeof(req))
    {
        /* Marginally dubious error reporting; if the return value is
        ** positive but small, errno has no useful information in it.
        */
        err_syserr("failed to read %zu bytes for head from FIFO %s: ", sizeof(req), FIFO_NAME);
    }
    size_t req_size = sizeof(*rp) + req.pref_seats_size * sizeof(rp->pref_seat_list[0]);
    rp = malloc(req_size);
    if (rp == 0)
        err_syserr("failed to allocate %zu bytes memory: ", req_size);

    *rp = req;

    int nbytes = rp->pref_seats_size * sizeof(rp->pref_seat_list[0]);
    //if (read(fd, &rp->pref_seat_list[0], nbytes) != nbytes)
    if (read(fd, rp->pref_seat_list, nbytes) != nbytes)
        err_syserr("failed to read %d bytes for body from FIFO %s: ", nbytes, FIFO_NAME);

    dump_request("Receiver", rp);

    free(rp);
    close(fd);
    unlink(FIFO_NAME);
    printf("Recv: PID %d finished reading request from FIFO %s\n", (int)getpid(), FIFO_NAME);
    return 0;
}

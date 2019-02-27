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

    FILE *fp = fopen(FIFO_NAME, "w");
    if (fp == NULL)
        err_syserr("failed to open FIFO %s for writing: ", FIFO_NAME);

    printf("Send: PID %d at work with FIFO %s open for writing\n", (int)getpid(), FIFO_NAME);

    struct request *rp = 0;
    int num_prefs = 10;
    size_t req_size = sizeof(*rp) + num_prefs * sizeof(rp->pref_seat_list[0]);
    rp = malloc(req_size);
    if (rp == 0)
        err_syserr("failed to allocate %zu bytes memory: ", req_size);

    rp->pid = getpid();
    rp->num_wanted_seats = 3;
    rp->pref_seats_size = num_prefs;
    for (int i = 0; i < num_prefs; i++)
        rp->pref_seat_list[i] = 123 + i;

    dump_request("Sender", rp);

    if (fwrite(rp, req_size, 1, fp) != 1)
        err_syserr("failed to write request (%zu bytes) to FIFO %s: ", req_size, FIFO_NAME);

    free(rp);
    fclose(fp);
    unlink(FIFO_NAME);
    printf("Send: PID %d finished writing %zu bytes to FIFO %s\n", (int)getpid(), req_size, FIFO_NAME);
    return 0;
}

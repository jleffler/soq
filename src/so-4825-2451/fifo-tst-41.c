/* SO 4825-2451 */
#include "posixver.h"
#include "fifo-tst-41.h"
#include "stderr.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define NS_PER_MS 1000000
#define MS_PER_S  1000

void random_milli_nap(int min_nap, int max_nap)
{
    int delta_ms = max_nap - min_nap;
    int naptm_ms = rand() % delta_ms + min_nap;
    struct timespec naptime = { .tv_sec = naptm_ms / MS_PER_S,
                                .tv_nsec = NS_PER_MS * (naptm_ms % MS_PER_S) };
    err_remark("Napping 0.%.3ld seconds\n", naptime.tv_nsec / NS_PER_MS);
    nanosleep(&naptime, 0);
    err_remark("Woke up 0.%.3ld seconds later\n", naptime.tv_nsec / NS_PER_MS);
}

void create_fifo(void)
{
    struct stat sb;
    if (stat(FIFO, &sb) != 0 || !S_ISFIFO(sb.st_mode))
    {
        err_remark("Creating FIFO '%s'\n", FIFO);
        if (mkfifo(FIFO, 0644) != 0)
            err_syserr("failed to create FIFO '%s': ", FIFO);
    }
}

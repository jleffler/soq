/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Chunk Reader for SO 5631-4784
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2019
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/*
** Problem specification from the Stack Overflow question
**
** In a bash script I am using a many-producer single-consumer pattern.
** Producers are background processes writing lines into a fifo (via GNU
** Parallel).  The consumer reads all lines from the fifo, then sorts,
** filters, and prints the formatted result to stdout.
**
** However, it could take a long time until the full result is
** available.  Producers are usually fast on the first few results but
** then would slow down.  Here I am more interested to see chunks of
** data every few seconds, each sorted and filtered individually.
**
**    mkfifo fifo
**    parallel ... >"$fifo" &
**    while chunk=$(read with timeout 5s and at most 10s <"$fifo"); do
**      process "$chunk"
**    done
**
** The loop would run until all producers are done and all input is
** read.  Each chunk is read until there has been no new data for 5s, or
** until 10s have passed since the chunk was started.  A chunk may also
** be empty if there was no new data for 10s.
*/

/*
** Analysis
**
** 1.  If no data arrives at all for 10 seconds, then the program should
**     terminate producing no output.  This timeout is controlled by the
**     value of time_chunk in the code.
** 2.  If data arrives more or less consistently, then the collection
**     should continue for 10s and then finish.  This timeout is also
**     controlled by the value of time_chunk in the code.
** 3.  If a line of data arrives before 5 seconds have elapsed, and no
**     more arrives for 5 seconds, then the collection should finish.
**     (If the first line arrives after 5 seconds and no more arrives
**     for more than 5 seconds, then the 10 second timeout cuts in.)
**     This timeout is controlled by the value of time_delay in the code.
** 4.  This means that we want two separate timers at work:
**     - Chunk timer (started when the program starts).
**     - Delay timer (started each time a line is read).
**
** It doesn't matter which timer goes off, but further timer signals
** should be ignored.  External signals will confuse things; tough!
**
** -- Using alarm(2) is tricky because it provides only one time, not two.
** -- Using getitimer(2), setitimer(2) uses obsolescent POSIX functions,
**    but these are available on macOS.
** -- Using timer_create(2), timer_destroy(2), timer_settime(2),
**    timer_gettime(2) uses current POSIX function but is not available
**    on macOS.
*/

#include "posixver.h"

#include "stderr.h"
#include "time_io.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef USE_SETITIMER
#include <sys/time.h>
#endif /* USE_SETITIMER */
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

static const char optstr[] = "hVc:d:f:";
static const char usestr[] = "[-hV][-c chunk][-d delay][-f file]";
static const char hlpstr[] =
    "  -c chunk  Maximum time to wait for data in a chunk (default 10)\n"
    "  -d delay  Maximum delay after line read (default: 5)\n"
    "  -f file   Read from file instead of standard input\n"
    "  -h        Print this help message and exit\n"
    "  -V        Print version information and exit\n"
    ;

static struct timespec time_delay = { .tv_sec =  5, .tv_nsec = 0 };
static struct timespec time_chunk = { .tv_sec = 10, .tv_nsec = 0 };
static struct timespec time_start;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_chunker79_c[];
const char jlss_id_chunker79_c[] = "@(#)$Id$";
#endif /* lint */

static void set_chunk_timeout(void);
static void set_delay_timeout(void);
static void cancel_timeout(void);
static void alarm_handler(int signum);

#if defined(USE_ALARM)

static void set_chunk_timeout(void)
{
    err_remark("In %s()\n", __func__);
    alarm(time_chunk.tv_sec);
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    //signal(SIGALRM, alarm_handler);
}

static void set_delay_timeout(void)
{
    err_remark("In %s()\n", __func__);
    unsigned time_left = alarm(0);
    if (time_left > time_delay.tv_sec)
        alarm(time_delay.tv_sec);
    else
        alarm(time_left);
}

static void cancel_timeout(void)
{
    err_remark("In %s()\n", __func__);
    alarm(0);
    signal(SIGALRM, SIG_IGN);
}

static void alarm_handler(int signum)
{
    assert(signum == SIGALRM);
    err_remark("In %s()\n", __func__);
}

#elif defined(USE_SETITIMER)

static void set_chunk_timeout(void);
static void set_delay_timeout(void);
static void cancel_timeout(void);
static void alarm_handler(int signum);

#else /* USE_TIMER_GETTIME */

static void set_chunk_timeout(void) { }
static void set_delay_timeout(void) { }
static void cancel_timeout(void) { }
static void alarm_handler(int signum) { assert(signum == SIGALRM); }

#endif /* Timing mode */

static void read_chunks(FILE *fp, const char *name)
{
    size_t num_data = 0;
    size_t max_data = 0;
    struct iovec *data = 0;
    size_t buflen = 0;
    char *buffer = 0;
    ssize_t length;
    size_t chunk_len = 0;

    printf("file:  %s\n", name);
    clock_gettime(CLOCK_REALTIME, &time_start);

    set_chunk_timeout();
    while ((length = getline(&buffer, &buflen, fp)) != -1)
    {
        if (num_data >= max_data)
        {
            size_t new_size = (num_data * 2) + 2;
            void *newspace = realloc(data, new_size * sizeof(data[0]));
            if (newspace == 0)
                err_syserr("failed to allocate %zu bytes data: ", new_size * sizeof(data[0]));
            data = newspace;
            max_data = new_size;
        }
        data[num_data].iov_base = buffer;
        data[num_data].iov_len = length;
        num_data++;
        err_remark("Received line %zu\n", num_data);
        chunk_len += length;
        buffer = 0;
        buflen = 0;
        set_delay_timeout();
    }
    cancel_timeout();

    if (chunk_len > 0)
    {
        if ((length = writev(STDOUT_FILENO, data, num_data)) < 0)
            err_syserr("failed to write %zu bytes to standard output: ", chunk_len);
        else if ((size_t)length != chunk_len)
            err_error("failed to write %zu bytes to standard output "
                      "(short write of %zu bytes)\n", chunk_len, (size_t)length);
    }

    err_remark("In %s(): data written\n", __func__);

    for (size_t i = 0; i < num_data; i++)
        free(data[i].iov_base);
    free(data);
    free(buffer);
}

int main(int argc, char **argv)
{
    const char *name = "(standard input)";
    FILE *fp = stdin;
    err_setarg0(argv[0]);
    err_setlogopts(ERR_MICRO);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            if (scn_timespec(optarg, &time_delay) != 0)
                err_error("Failed to convert '%s' into a time value\n", optarg);
            break;
        case 'e':
            if (scn_timespec(optarg, &time_chunk) != 0)
                err_error("Failed to convert '%s' into a time value\n", optarg);
            break;
        case 'f':
            if ((fp = fopen(optarg, "r")) == 0)
                err_syserr("Failed to open file '%s' for reading: ", optarg);
            name = optarg;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("CHUNKER79", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (optind != argc)
        err_usage(usestr);

#if 0
    printf("chunk: %3lld.%09ld\n", (long long)time_chunk.tv_sec, time_chunk.tv_nsec);
    printf("delay: %3lld.%09ld\n", (long long)time_delay.tv_sec, time_delay.tv_nsec);
    printf("file:  %s\n", name);
#endif /* 0 */

    read_chunks(fp, name);

    return 0;
}

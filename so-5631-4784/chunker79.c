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

#include "posixver.h"

#include "stderr.h"
#include "time_io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

static const char optstr[] = "hVd:e:f:s:";
static const char usestr[] = "[-hV][-d delay][-e empty][-s start][-f file]";
static const char hlpstr[] =
    "  -d delay  Delay after chunk read (default: 5)\n"
    "  -e empty  Delay for empty chunk (default: 10)\n"
    "  -f file   Read from file instead of standard input\n"
    "  -h        Print this help message and exit\n"
    "  -s start  Delay since chunk started (default: 10)\n"
    "  -V        Print version information and exit\n"
    ;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_chunker79_c[];
const char jlss_id_chunker79_c[] = "@(#)$Id$";
#endif /* lint */

static void read_chunks(FILE *fp, const char *name, struct timespec delay,
                        struct timespec empty, struct timespec start)
{
    size_t num_data = 0;
    size_t max_data = 0;
    struct iovec *data = 0;
    size_t buflen = 0;
    char *buffer = 0;
    ssize_t length;
    size_t chunk_len = 0;

    printf("delay: %3lld.%09ld\n", (long long)delay.tv_sec, delay.tv_nsec);
    printf("empty: %3lld.%09ld\n", (long long)empty.tv_sec, empty.tv_nsec);
    printf("start: %3lld.%09ld\n", (long long)start.tv_sec, start.tv_nsec);
    printf("file:  %s\n", name);

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
        chunk_len += length;
        buffer = 0;
        buflen = 0;
    }

    if (chunk_len > 0)
    {
        if ((length = writev(STDOUT_FILENO, data, num_data)) < 0)
            err_syserr("failed to write %zu bytes to standard output: ", chunk_len);
        else if ((size_t)length != chunk_len)
            err_error("failed to write %zu bytes to standard output "
                      "(short write of %zu bytes)\n", chunk_len, (size_t)length);
    }

    for (size_t i = 0; i < num_data; i++)
        free(data[i].iov_base);
    free(data);
    free(buffer);
};

int main(int argc, char **argv)
{
    struct timespec delay = { .tv_sec =  5, .tv_nsec = 0 };
    struct timespec start = { .tv_sec = 10, .tv_nsec = 0 };
    struct timespec empty = { .tv_sec = 10, .tv_nsec = 0 };
    const char *name = "(standard input)";
    FILE *fp = stdin;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            if (scn_timespec(optarg, &delay) != 0)
                err_error("Failed to convert '%s' into a time value\n", optarg);
            break;
        case 'e':
            if (scn_timespec(optarg, &empty) != 0)
                err_error("Failed to convert '%s' into a time value\n", optarg);
            break;
        case 'f':
            if ((fp = fopen(optarg, "r")) == 0)
                err_syserr("Failed to open file '%s' for reading: ", optarg);
            name = optarg;
            break;
        case 's':
            if (scn_timespec(optarg, &start) != 0)
                err_error("Failed to convert '%s' into a time value\n", optarg);
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
    printf("delay: %3lld.%09ld\n", (long long)delay.tv_sec, delay.tv_nsec);
    printf("empty: %3lld.%09ld\n", (long long)empty.tv_sec, empty.tv_nsec);
    printf("start: %3lld.%09ld\n", (long long)start.tv_sec, start.tv_nsec);
    printf("file:  %s\n", name);
#endif /* 0 */

    read_chunks(fp, name, delay, empty, start);

    return 0;
}

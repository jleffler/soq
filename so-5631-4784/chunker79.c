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

#include "time_io.h"
#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    printf("delay: %3lld.%09ld\n", (long long)delay.tv_sec, delay.tv_nsec);
    printf("empty: %3lld.%09ld\n", (long long)empty.tv_sec, empty.tv_nsec);
    printf("start: %3lld.%09ld\n", (long long)start.tv_sec, start.tv_nsec);
    printf("file:  %s\n", name);

    return 0;
}

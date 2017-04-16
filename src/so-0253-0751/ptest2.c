/*
@(#)File:           $RCSfile: ptest2.c,v $
@(#)Version:        $Revision: 1.1 $
@(#)Last changed:   $Date: 2010/03/28 00:35:15 $
@(#)Purpose:        Relative speed of KMP vs BM vs strstr()
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2010
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bm.h"
#include "kmp.h"
#include "stderr.h"
#include "timer.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_ptest_c[];
const char jlss_id_ptest_c[] = "@(#)$Id: ptest2.c,v 1.1 2010/03/28 00:35:15 jleffler Exp $";
#endif /* lint */

static void *memory_map(const char *fname, size_t *size)
{
    void *data;
    struct stat sb;
    int fd = open(fname, O_RDONLY);
    if (fd < 0)
        err_syserr("failed to open file %s for reading\n", fname);
    if (fstat(fd, &sb) != 0)
        err_syserr("failed to stat file %s\n", fname);
    if (!S_ISREG(sb.st_mode))
        err_error("file %s is not a regular file (%o)\n", fname, sb.st_mode);
    data = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED)
        err_error("failed to memory map file %s\n", fname);
    *size = sb.st_size;
    return(data);
}

int main(int argc, char **argv)
{
    char *source;
    size_t length;

    err_setarg0(argv[0]);

    source = memory_map(argv[1], &length);
    const char *end = source + length;
    printf("Data file: %s (size %zd)\n", argv[1], length);

    for (int i = 2; i < argc; i++)
    {
        const char *needle = argv[i];
        const char *str;
        char  clkbuff[32];
        Clock clk;

        clk_init(&clk);
        printf("Search for: %s\n", needle);

        clk_start(&clk);
        bm_control  *bp = bm_setsearch(needle, strlen(needle));
        clk_stop(&clk);
        printf("BM  prep-time: %s\n", clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

        clk_start(&clk);
        kmp_control *kp = kmp_setsearch(needle, strlen(needle));
        clk_stop(&clk);
        printf("KMP prep-time: %s\n", clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

        /* Warm up source data */
        clk_start(&clk);
        str = strchr(source, 0xFF);
        clk_stop(&clk);
        printf("Scan time (%" PRIuPTR "): %s\n", (uintptr_t)str, clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

        for (size_t j = 0; j < 10; j++)
        {
            size_t s_count = 0;
            size_t b_count = 0;
            size_t k_count = 0;

            clk_start(&clk);
            kmp_settarget(kp, source, length);
            clk_stop(&clk);
            printf("KMP reset-time: %s\n", clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

            clk_start(&clk);
            bm_settarget(bp, source, length);
            clk_stop(&clk);
            printf("BM  reset-time: %s\n", clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

            clk_start(&clk);
            str = source;
            while (str != 0 && str < end)
            {
                /* End condition works - but is hardly robust */
                str = strstr(str, needle);
                if (str != 0)
                {
                    str++;
                    s_count++;
                }
            }
            clk_stop(&clk);
            printf("STR%zd found %zd, search-time: %s\n", j, s_count, clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

            clk_start(&clk);
            while ((str = bm_search(bp)) != 0)
                b_count++;
            clk_stop(&clk);
            printf("BM%zd  found %zd, search-time: %s\n", j, b_count, clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

            clk_start(&clk);
            while ((str = kmp_search(kp)) != 0)
                k_count++;
            clk_stop(&clk);
            printf("KMP%zd found %zd, search-time: %s\n", j, k_count, clk_elapsed_us(&clk, clkbuff, sizeof(clkbuff)));

        }
        bm_release(bp);
        kmp_release(kp);
    }

    return(0);
}

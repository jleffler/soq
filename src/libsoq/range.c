/*
@(#)File:           range.c
@(#)Purpose:        Decode string into range of integers.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1991,1995,1997,2002,2005,2007-08,2015
@(#)Derivation:     range.c 1.17 2015/06/02 02:55:44
*/

/*TABSTOP=4*/

/*
**  Parse number ranges, dealing only with positive values.
**
**  Input:      Low     High
**  23          23      23
**  23-25       23      25
**  23-         23      0
**  -23         0       23
**  Any other delimiter after number (or before number) terminates input
*/

#include "posixver.h"
#include "range.h"
#include <stdlib.h>

static int base = 10;

int parse_setbase(int new_base)
{
    int old_base = base;
    base = new_base;
    return old_base;
}

const char *parse_range(const char *str, long *lo, long *hi)
{
    const char *s = str;
    char *t;
    long  l;

    l = strtol(s, &t, base);
    if (l < 0)
    {   /* -n => lo = 0, hi = n */
        *lo = 0;
        *hi = -l;
    }
    else if (t == s)
    {   /* No number found */
        *lo = *hi = 0;
        t = 0;
    }
    else if (*t == ',')
    {   /* n, => lo = hi = n */
        *lo = *hi = l;
    }
    else if (*t == '-')
    {   /* n-m => lo = n, hi = m */
        /* n-  => lo = n, hi = 0 */
        s = ++t;
        *lo = l;
        *hi = strtol(s, &t, base);
        if (*hi < *lo && *hi != 0)
        {
            /* l already equals *lo */
            *lo = *hi;
            *hi = l;
        }
    }
    else
    {   /* n => lo = hi = n */
        *lo = *hi = l;
    }
    if (t != 0 && *t != ',' && *t != '\0')
    {
        /* Improper range terminator - error now! */
        *lo = *hi = 0;
        t = 0;
    }
    /* Skip trailing commas */
    if (t != 0)
    {
        while (*t == ',')
            t++;
    }
    return(t);
}

#ifdef TEST
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stderr.h"

/*
** Example test (with plausible output):
** $ ./range -- -5,13-18,20,23,27- 27-,18-13,23,20,-5 23-23 x 23+4 43/9 -+5-+14 -5-+14 1,3-5 6
** Processing: -5,13-18,20,23,27-
** Parse: -5,13-18,20,23,27- (addr = 0xFFBEF144) Range:  0 ->  5 (addr = 0xFFBEF147; trailer = <<13-18,20,23,27->>)
** Parse: 13-18,20,23,27- (addr = 0xFFBEF147) Range: 13 -> 18 (addr = 0xFFBEF14D; trailer = <<20,23,27->>)
** Parse:       20,23,27- (addr = 0xFFBEF14D) Range: 20 -> 20 (addr = 0xFFBEF150; trailer = <<23,27->>)
** Parse:          23,27- (addr = 0xFFBEF150) Range: 23 -> 23 (addr = 0xFFBEF153; trailer = <<27->>)
** Parse:             27- (addr = 0xFFBEF153) Range: 27 ->  0 (addr = 0xFFBEF156; trailer = <<>>)
** Processing: 27-,18-13,23,20,-5
** Parse: 27-,18-13,23,20,-5 (addr = 0xFFBEF157) Range: 27 ->  0 (addr = 0xFFBEF15B; trailer = <<18-13,23,20,-5>>)
** Parse:  18-13,23,20,-5 (addr = 0xFFBEF15B) Range: 13 -> 18 (addr = 0xFFBEF161; trailer = <<23,20,-5>>)
** Parse:        23,20,-5 (addr = 0xFFBEF161) Range: 23 -> 23 (addr = 0xFFBEF164; trailer = <<20,-5>>)
** Parse:           20,-5 (addr = 0xFFBEF164) Range: 20 -> 20 (addr = 0xFFBEF167; trailer = <<-5>>)
** Parse:              -5 (addr = 0xFFBEF167) Range:  0 ->  5 (addr = 0xFFBEF169; trailer = <<>>)
** Processing: 23-23
** Parse:           23-23 (addr = 0xFFBEF16A) Range: 23 -> 23 (addr = 0xFFBEF16F; trailer = <<>>)
** Processing: x
** Parse:               x (addr = 0xFFBEF170) Range:  0 ->  0 (addr = 0x00000000; trailer = <<!!null pointer!!>>)
** Processing: 23+4
** Parse:            23+4 (addr = 0xFFBEF172) Range:  0 ->  0 (addr = 0x00000000; trailer = <<!!null pointer!!>>)
** Processing: 43/9
** Parse:            43/9 (addr = 0xFFBEF177) Range:  0 ->  0 (addr = 0x00000000; trailer = <<!!null pointer!!>>)
** Processing: -+5-+14
** Parse:         -+5-+14 (addr = 0xFFBEF17C) Range:  0 ->  0 (addr = 0x00000000; trailer = <<!!null pointer!!>>)
** Processing: -5-+14
** Parse:          -5-+14 (addr = 0xFFBEF184) Range:  0 ->  0 (addr = 0x00000000; trailer = <<!!null pointer!!>>)
** Processing: 1,3-5
** Parse:           1,3-5 (addr = 0xFFBEF18B) Range:  1 ->  1 (addr = 0xFFBEF18D; trailer = <<3-5>>)
** Parse:             3-5 (addr = 0xFFBEF18D) Range:  3 ->  5 (addr = 0xFFBEF190; trailer = <<>>)
** Processing: 6
** Parse:               6 (addr = 0xFFBEF191) Range:  6 ->  6 (addr = 0xFFBEF192; trailer = <<>>)
** $
*/

int main(int argc, char **argv)
{
    int         i;
    const char  usestr[] = "[-b base] range [...]";
    int         opt;

    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, "b:")) != -1)
    {
        switch (opt)
        {
        case 'b':
            parse_setbase(atoi(optarg));
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }
    if (optind >= argc)
        err_usage(usestr);

    for (i = optind; i < argc; i++)
    {
        long        lo;
        long        hi;
        const char *t = argv[i];
        printf("Processing: %s\n", t);
        while (t != 0 && *t != '\0')
        {
            printf("Parse: %15s (addr = 0x%08lX) ", t, (unsigned long)t);
            fflush(stdout);
            t = parse_range(t, &lo, &hi);
            printf("Range: %2ld -> %2ld (addr = 0x%08lX; trailer = <<%s>>)\n", lo, hi,
                        (unsigned long)t, (t != 0 ? t : "!!null pointer!!"));
            fflush(stdout);
        }
    }
    return(0);
}

#endif /* TEST */

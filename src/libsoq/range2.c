/*
@(#)File:           range2.c
@(#)Purpose:        Decode string into range of integers.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1997,2002,2005,2007-08,2015
@(#)Derivation:     range2.c 1.11 2015/06/19 06:52:09
*/

/*TABSTOP=4*/

/*
**  Parse number ranges, dealing with positive and negative values,
**  and ranges separated by either colon or double-dot.
**
**  Input:      Low     High
**  23          23      23
**  -23        -23     -23
**  23:25       23      25
**  23..25      23      25
**  -23..-25   -25     -23
**  -23..25    -23      25
**  23..-25    -25      23
**  -23..+25   -23      25
**  Any other delimiter after number (or before number) terminates
**  input.  NB: a leading colon (or dot) is not a valid range.  If
**  there is a format error, the returned pointer points to the
**  start of the string (and lo and hi are unchanged).  If there is
**  no error, then the returned pointer points to the ASCII NUL at
**  the end of the string.
*/

#include "posixver.h"
#include "range.h"
#include <stdlib.h>
#include <ctype.h>

static int base = 10;

int numeric_setbase(int new_base)
{
    int old_base = base;
    base = new_base;
    return old_base;
}

/*
** Parse numeric range.
** Return pointer to trailing '\0' if OK, else pointer to input string
*/
const char *numeric_range(const char *str, long *lo, long *hi)
{
    const char *s = str;
    char       *t;
    long        l;
    long        h;

    if (*s == '\0')
        return 0;

    l = strtol(s, &t, base);
    if (*t == '\0')
    {
        /* Just one number */
        *lo = *hi = l;
        return(t);
    }

    if (*t == ':')
        t += 1;
    else if (t[0] == '.' && t[1] == '.')
        t += 2;
    else
    {
        /* Format error */
        return(str);
    }

    h = strtol(t, &t, base);
    if (*t != '\0' && *t != ',')
    {
        /* Format error */
        return(str);
    }

    if (*t == ',')
    {
        t++;
        if (!isdigit((unsigned char)*t) && *t != '-' && *t != '+')
        {
            /* Format error */
            return(str);
        }
    }

    if (h < l)
    {
        long x = h;
        h = l;
        l = x;
    }

    *lo = l;
    *hi = h;

    return(t);
}

#if defined(TEST)
#include <stdio.h>
#include <unistd.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    static const char  usestr[] = "[-b base] range [...]";
    int         opt;

    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, "b:")) != -1)
    {
        switch (opt)
        {
        case 'b':
            numeric_setbase(atoi(optarg));
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }
    if (optind >= argc)
        err_usage(usestr);

    for (int i = optind; i < argc; i++)
    {
        const char *t = argv[i];
        while (t != 0 && *t != '\0')
        {
            printf("Parse: %15s (addr = 0x%08lX) ", t, (unsigned long)t);
            fflush(stdout);
            long lo = 0;
            long hi = 0;
            const char *s = numeric_range(t, &lo, &hi);
            printf("Range: %2ld -> %2ld (addr = 0x%08lX; trailer = <<%s>>)\n", lo, hi, (unsigned long)s, s);
            fflush(stdout);
            t = s;
        }
    }
    return(0);
}
#endif /* TEST */

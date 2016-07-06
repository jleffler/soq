/*
@(#)File:           range3.c
@(#)Purpose:        Decode string into range of integers.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Derivation:     range3.c 1.1 2015/06/04 02:46:01
*/

/*TABSTOP=4*/

/*
**  Parse floating-point number ranges, dealing with positive and
**  negative values, and ranges separated by either colon or double-dot
**  (but note that 13. is interpreted as a double number, so you need
**  three dots to make a double dot range after integers: 12.0..13 is
**  fine, and so is 12...13, and they designate the same range.
**
**  Future change: handle 12..13 sanely too.
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
**
**  Any other delimiter after a number (or before a number) terminates
**  the input.  NB: a leading colon is not a valid range.  If there is a
**  format error, the returned pointer points to the start of the string
**  (and lo and hi are unchanged).  If there is no error, then the
**  returned pointer points to the ASCII NUL at the end of the string.
**  If there is nothing to process (the input string is empty) then a
**  null pointer is returned.
**
**  This code also allows multiple ranges separated by commas, as
**  indicated in the recommended usage in the header.  This is achieved
**  by allowing and ignoring a single comma at the start of the
**  argument, and permitting comma or EOS after the end of a range.
**  Single-value 'ranges' don't make a lot of sense with floating point
**  numbers, but are allowed even so.
*/

#include "posixver.h"
#include "range.h"
#include <stdlib.h>

/*
** Parse numeric range for floating point values.
*/
const char *double_range(const char *str, double *lo, double *hi)
{
    const char *s = str;
    char       *t;
    double      l;
    double      h;

    if (*s == '\0')
        return 0;

    l = strtod(s, &t);
    if (t == s)
    {
        /* Failed to convert a number */
        return 0;
    }

    if (*t == '\0' || *t == ',')
    {
        /* Just one number in range */
        *lo = *hi = l;
        while (*t == ',')   // Skip commas
            t++;
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

    h = strtod(t, &t);

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

    if (h < l)
    {
        double x = h;
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
#include <inttypes.h>
#include "stderr.h"

int main(int argc, char **argv)
{
    err_setarg0(argv[argc-argc]);

    for (int i = optind; i < argc; i++)
    {
        const char *ptr = argv[i];
        if (ptr != 0 && *ptr != '\0')
        {
            printf("Parse: 0x%08" PRIXPTR " = <<%s>>\n", (uintptr_t)ptr, ptr);
            fflush(stdout);
            const char *nxt;
            double      lo = 0.0;
            double      hi = 0.0;
            while ((nxt = double_range(ptr, &lo, &hi)) != 0)
            {
                if (nxt == ptr)
                    err_error("invalid range string (%s)\n", argv[i]);
                printf("Range: %2g -> %2g (0x%08" PRIXPTR "; trailer = <<%s>>)\n",
                   lo, hi, (uintptr_t)nxt, nxt);
                ptr = nxt;
            }
        }
    }

    return(0);
}
#endif /* TEST */

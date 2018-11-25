/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Generate numbers with no repeated base 10 digits
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/
/* SO 4103-2621 */

#undef TEST         /* Temporary */
#define TEST        /* Temporary */

#include "posixver.h"
#include "udn.h"
#include <assert.h>
#include <stdio.h>

enum { MAX_ITERATION = 999999999 };
enum { DEF_MAX_ITERATION = 999999 };

/*
** UDN = Unique Digit Number (a base 10 number with no leading zeros and
**       no repeated digit).
** Assume 32-bit int type.  A 32-bit integer is big enough for up to
** 9-digit numbers; it can't handle 10-digit numbers.
** UDN is not an opaque type so the functions do not need to handle
** memory allocation.
*/

static inline void udn_validate(UDN *udn)
{
    if (udn->max_value > MAX_ITERATION)
        udn->max_value = MAX_ITERATION;
    if (udn->max_value <= 0)
        udn->max_value = DEF_MAX_ITERATION;
    if (udn->next_value < 0 || udn->next_value >= udn->max_value)
        udn->next_value = 0;
}

void udn_initialize(UDN *udn, int next, int max)
{
    assert(udn != 0);
    udn->next_value = next;
    udn->max_value = max;
    udn_validate(udn);
}

void udn_set_next(UDN *udn, int next)
{
    assert(udn != 0);
    udn->next_value = next;
    udn_validate(udn);
}

static bool has_duplicate_digits(int value)
{
    char digits[10] = { 0 };
    while (value > 0)
    {
        if (++digits[value % 10] > 1)
            return true;
        value /= 10;
    }
    return false;
}

bool udn_gen_next(UDN *udn, size_t buflen, char buffer[buflen])
{
    if (udn->next_value >= udn->max_value)
        udn->next_value = 0;
    while (has_duplicate_digits(udn->next_value))
    {
        if (++udn->next_value >= udn->max_value)
        {
            udn->next_value = 0;
            return false;
        }
    }
    int rc = snprintf(buffer, buflen, "%d", udn->next_value++);
    if (rc < 0 || (size_t)rc >= buflen)
        return false;
    return true;
}

#ifdef TEST

#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char optstr[] = "hm:V";
static const char usestr[] = "[-hV][-m max]";
static const char hlpstr[] =
    "  -h      Print this help message and exit\n"
    "  -m max  Maximum value for range (default 1,000,000)\n"
    "  -V      Print version information and exit\n"
    ;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_udn_c[];
const char jlss_id_udn_c[] = "@(#)$Id$";
#endif /* lint */

int main(int argc, char **argv)
{
    int max_val = DEF_MAX_ITERATION;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'm':
            max_val = atoi(optarg);
            break;
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (optind != argc)
        err_usage(usestr);

    int linelen = 0;
    const char *pad = "";
    char buffer[12];
    UDN udn;
    udn_initialize(&udn, 0, max_val);
    while (udn_gen_next(&udn, sizeof(buffer), buffer))
    {
        linelen += printf("%s%s", pad, buffer);
        pad = " ";
        if (linelen > 72)
        {
            putchar('\n');
            linelen = 0;
            pad = "";
        }
    }
    putchar('\n');

    return 0;
}

#endif /* TEST */

/*
@(#)File:           strtoi.c
@(#)Purpose:        Analogues of strtol() for int and unsigned int
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-2018
@(#)Derivation:     strtoi.c 1.7 2018/06/11 00:58:06
*/

/*TABSTOP=4*/

/*
** Observation: with a 64-bit compilation, strtoul(-012345) yields
** 18446744073709546267.  This was rejected by strtoui() as too big;
** it means a different conversion technique is needed.
** If sizeof(int) < sizeof(long):
** -- Convert with strtol()
** -- Reject if result less than INT_MIN or larger than UINT_MAX.
** -- Convert negative to UINT_MAX + result
** If sizeof(int) == sizeof(long):
** -- Use strtoul() directly.
** Note that strtoi() isn't affected by this; it already uses strtol()
** and works correctly both when sizeof(int) == sizeof(long) and when it
** is not.
*/

#include "posixver.h"
#include "strtoint.h"
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int strtoi(const char *data, char **endptr, int base)
{
    int old_errno = errno;
    errno = 0;
    long lval = strtol(data, endptr, base);
    if (lval > INT_MAX)
    {
        errno = ERANGE;
        lval = INT_MAX;
    }
    else if (lval < INT_MIN)
    {
        errno = ERANGE;
        lval = INT_MIN;
    }
    if (errno == 0)
        errno = old_errno;
    return (int)lval;
}

unsigned int strtoui(const char *data, char **endptr, int base)
{
    int old_errno = errno;
    errno = 0;
    unsigned int result;
    if (sizeof(unsigned int) == sizeof(unsigned long))
    {
        /* conversion to 'unsigned int' from 'long unsigned int' may alter its value */
        /* It won't because sizeof(unsigned int) == sizeof(unsigned long), but ... */
        result = (unsigned int)strtoul(data, endptr, base);
    }
    else
    {
        long val = strtol(data, endptr, base);
        if (val > (long)UINT_MAX || val < INT_MIN)
        {
            errno = ERANGE;
            result = UINT_MAX;
        }
        else
            result = (unsigned int)val;
    }
    if (errno == 0)
        errno = old_errno;
    return result;
}

#if defined(TEST)

#include <assert.h>
#include <stddef.h>
#include "phasedtest.h"

/* -- PHASE 1 TESTING -- */

/* -- Test conversions for strtoi() -- */
typedef struct p1_test_case
{
    const char *input;      /* String */
    int         i_base;     /* Base */
    ptrdiff_t   offset;     /* Offset in endptr */
    int         retval;     /* Returned value */
    int         errnum;     /* Value in errno */
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { "0",           10,  1, 0,           0      },
    { "1000",        10,  4, 1000,        0      },
    { "+2147483647", 10, 11, +2147483647, 0      },
    { "+2147483648", 10, 11, INT_MAX,     ERANGE },
    { "-2147483647", 10, 11, -2147483647, 0      },
    { "-2147483648", 10, 11, -2147483648, 0      },
    { "-2147483649", 10, 11, INT_MIN,     ERANGE },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;
    char *end;
    errno = 0;
    int retval = strtoi(test->input, &end, test->i_base);
    ptrdiff_t offset = end - test->input;
    int errnum = errno;

    if (retval != test->retval)
        pt_fail("<<%s>> unexpected return value (actual %d wanted %d)\n",
                 test->input, retval, test->retval);
    else if (errnum != test->errnum)
        pt_fail("<<%s>> - unexpected errno (actual %d instead of %d)\n",
                test->input, errnum, test->errnum);
    else if (offset != test->offset)
        pt_fail("<<%s>> - unexpected offset (actual %td instead of %td)\n",
                test->input, offset, test->offset);
    else if ((test->retval == INT_MIN || test->retval == INT_MAX) &&
             errnum != 0)
        pt_pass("<<%s>> out of range (%d errno %d)\n",
                test->input, test->retval, test->errnum);
    else
        pt_pass("<<%s>>\n", test->input);
}

/* -- PHASE 2 TESTING -- */

/* -- Test conversions for strtoui() -- */
typedef struct p2_test_case
{
    const char   *input;      /* String */
    int           i_base;     /* Base */
    ptrdiff_t     offset;     /* Offset in endptr */
    unsigned int  retval;     /* Returned value */
    int           errnum;     /* Value in errno */
} p2_test_case;

static const p2_test_case p2_tests[] =
{
    { "0",           10,  1, 0,           0      },
    { "1000",        10,  4, 1000,        0      },
    { "+4294967295", 10, 11, +4294967295, 0      },
    { "+4294967296", 10, 11, UINT_MAX,    ERANGE },
    { "-012345",      0,  7, UINT_MAX - 012345 + 1,  0   },
    { "-012345",     10,  7, UINT_MAX -  12345 + 1,  0   },
    { "-12345",       8,  6, UINT_MAX - 012345 + 1,  0   },
};

static void p2_tester(const void *data)
{
    const p2_test_case *test = (const p2_test_case *)data;
    char *end;
    errno = 0;
    unsigned int retval = strtoui(test->input, &end, test->i_base);
    ptrdiff_t offset = end - test->input;
    int errnum = errno;

    if (retval != test->retval)
        pt_fail("<<%s>> unexpected return value (actual %u wanted %u)\n",
                 test->input, retval, test->retval);
    else if (errnum != test->errnum)
        pt_fail("<<%s>> - unexpected errno (actual %d instead of %d)\n",
                test->input, errnum, test->errnum);
    else if (offset != test->offset)
        pt_fail("<<%s>> - unexpected offset (actual %td instead of %td)\n",
                test->input, offset, test->offset);
    else if (test->retval == UINT_MAX && errnum != 0)
        pt_pass("<<%s>> out of range (%u errno %d)\n",
                test->input, test->retval, test->errnum);
    else
        pt_pass("<<%s base %2d yields %u>>\n", test->input, test->i_base, test->retval);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "Test conversions for strtoi()" },
    { p2_tester, PT_ARRAYINFO(p2_tests), 0, "Test conversions for strtoui()" },
};

int main(int argc, char **argv)
{
    assert(sizeof(int) == 4);
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

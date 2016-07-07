/*
@(#)File:           strtosize.c
@(#)Purpose:        Analogue of strtol() for size_t
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     strtosize.c 1.4 2016/06/07 06:20:44
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "jlss.h"
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

size_t strtosize(const char *data, char **endptr, int base)
{
    int old_errno = errno;
    errno = 0;
    uintmax_t lval = strtoumax(data, endptr, base);
    if (lval > SIZE_MAX)
    {
        errno = ERANGE;
        lval = SIZE_MAX;
    }
    if (errno == 0)
        errno = old_errno;
    return (size_t)lval;
}

#ifdef TEST

#include <assert.h>
#include <stddef.h>
#include "phasedtest.h"

/* -- PHASE 1 TESTING -- */

/* -- Test conversions for strtosize() -- */
typedef struct p1_test_case
{
    const char   *input;      /* String */
    int           i_base;     /* Base */
    ptrdiff_t     offset;     /* Offset in endptr */
    size_t        retval;     /* Returned value */
    int           errnum;     /* Value in errno */
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { "0",           10,  1, 0,           0      },
    { "1000",        10,  4, 1000,        0      },
    { "+4294967295", 10, 11, +4294967295, 0      },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;
    char *end;
    errno = 0;
    size_t retval = strtosize(test->input, &end, test->i_base);
    ptrdiff_t offset = end - test->input;
    int errnum = errno;

    if (retval != test->retval)
        pt_fail("<<%s>> unexpected return value (actual %zu wanted %zu)\n",
                 test->input, retval, test->retval);
    else if (errnum != test->errnum)
        pt_fail("<<%s>> - unexpected errno (actual %d instead of %d)\n",
                test->input, errnum, test->errnum);
    else if (offset != test->offset)
        pt_fail("<<%s>> - unexpected offset (actual %td instead of %td)\n",
                test->input, offset, test->offset);
    else if (test->retval == SIZE_MAX && errnum != 0)
        pt_pass("<<%s>> out of range (%zu errno %d)\n",
                test->input, test->retval, test->errnum);
    else
        pt_pass("<<%s>>\n", test->input);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "Test conversions for strtosize()" },
};

int main(int argc, char **argv)
{
    assert(sizeof(int) == 4);
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

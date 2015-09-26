#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <stddef.h>     // size_t

typedef struct RationalInt
{
    int     numerator;
    int     denominator;
} RationalInt;

extern RationalInt ri_new(int numerator, int denominator);
extern RationalInt ri_add(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_sub(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_mul(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_div(RationalInt lhs, RationalInt rhs);
extern char *ri_fmt(RationalInt val, char *buffer, size_t buflen);
extern int ri_cmp(RationalInt lhs, RationalInt rhs);

#endif /* RATIONAL_H_INCLUDED */

/*
** Storage rules:
** 1. Denominator is never zero.
** 2. Denominator stores the sign and is not INT_MIN (2's complement assumed).
** 3. Numerator is never negative.
** 4. gcd(numerator, denominator) == 1 unless numerator == 0.
*/

#include "gcd.h"        // add gcd_ll?
#include <assert.h>
#include <limits.h>
#include <stdio.h>

static inline int iabs(int x) { return (x < 0) ? -x : x; }
static inline int signum(int x) { return (x > 0) ? +1 : (x < 0) ? -1 : 0; }

static void ri_chk(RationalInt val)
{
    assert(val.denominator != 0 && val.denominator != INT_MIN);
    assert(val.numerator >= 0);
    assert(val.numerator == 0 || gcd(iabs(val.numerator), iabs(val.denominator)) == 1);
}

static long long gcd_ll(long long x, long long y)
{
    long long r;

    if (x == 0 || y == 0)
        return(0);

    while ((r = x % y) != 0)
    {
        x = y;
        y = r;
    }
    return(y);
}

RationalInt ri_new(int numerator, int denominator)
{
    assert(denominator != 0);
    RationalInt ri;
    if (numerator == 0)
    {
        ri.numerator = 0;
        ri.denominator = 1;
    }
    else
    {
        int sign = 1 - 2 * ((numerator < 0 && denominator > 0) || (numerator > 0 && denominator < 0));
        assert(sign == +1 || sign == -1);
        int dv = gcd(iabs(numerator), iabs(denominator));
        assert(dv != 0);
        ri.numerator = iabs(numerator) / dv;
        ri.denominator = sign * iabs(denominator) / dv;
    }
    return ri;
}

RationalInt ri_add(RationalInt lhs, RationalInt rhs)
{
    long long rn = lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_sub(RationalInt lhs, RationalInt rhs)
{
    long long rn = lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_mul(RationalInt lhs, RationalInt rhs)
{
    long long rn = lhs.numerator * rhs.numerator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_div(RationalInt lhs, RationalInt rhs)
{
    assert(rhs.numerator != 0);
    if (lhs.numerator == 0)
        return ri_new(0, 1);
    long long rn = lhs.numerator * rhs.denominator;
    long long rd = lhs.denominator * rhs.numerator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

char *ri_fmt(RationalInt val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    if (buflen > 0 && buffer != 0)
    {
        char sign = (val.denominator < 0) ? '-' : '+';
        int len = snprintf(buffer, buflen, "[%c%d/%d]",
                           sign, iabs(val.numerator), iabs(val.denominator));
        if (len < 5 || (size_t)len >= buflen)  // 5 = strlen("[1/1]")
            *buffer = '\0';
    }
    return buffer;
}

int ri_cmp(RationalInt lhs, RationalInt rhs)
{
    if (lhs.denominator == rhs.denominator &&
        lhs.numerator == rhs.numerator)
        return 0;
    if (signum(lhs.denominator) != signum(rhs.denominator))
    {
        /* Different signs - but one could be zero */
        if (signum(lhs.denominator) < signum(rhs.denominator))
            return -1;
        else
            return +1;
    }
    long long v1 = lhs.numerator * iabs(rhs.denominator);
    long long v2 = rhs.numerator * iabs(lhs.denominator);
    assert(v1 != v2);
    if (v1 < v2)
        return -1;
    else
        return +1;
}

#define TEST    // Temporary
#if defined(TEST)

#include "phasedtest.h"

/* -- PHASE 1 TESTING -- */

/* -- ri_new -- */
typedef struct p1_test_case
{
    int i_num;
    int i_den;
    RationalInt res;
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { .i_num =  1, .i_den =  1, .res = {  1,   1 } },
    { .i_num =  0, .i_den =  1, .res = {  0,   1 } },
    { .i_num =  2, .i_den =  2, .res = {  1,   1 } },
    { .i_num =  1, .i_den =  2, .res = {  1,   2 } },
    { .i_num = 15, .i_den =  3, .res = {  5,   1 } },
    { .i_num = 28, .i_den =  6, .res = { 14,   3 } },
    { .i_num =  6, .i_den = 28, .res = {  3,  14 } },
    { .i_num = +6, .i_den = +8, .res = {  3,  +4 } },
    { .i_num = +6, .i_den = -8, .res = {  3,  -4 } },
    { .i_num = -6, .i_den = +8, .res = {  3,  -4 } },
    { .i_num = -6, .i_den = -8, .res = {  3,  +4 } },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;
    char buffer1[32];
    char buffer2[32];

    RationalInt ri = ri_new(test->i_num, test->i_den);

    if (ri.denominator != test->res.denominator ||
        ri.numerator != test->res.numerator)
        pt_fail("ri_new(%d, %d) - unexpected result %s (instead of %s)\n",
                test->i_num, test->i_den, ri_fmt(ri, buffer1, sizeof(buffer1)),
                ri_fmt(test->res, buffer2, sizeof(buffer2)));
    else
        pt_pass("ri_new(%d, %d) - %s\n", test->i_num, test->i_den,
                ri_fmt(test->res, buffer2, sizeof(buffer2)));
}

/* -- PHASE 2 TESTING -- */

/* -- ri_cmp -- */
typedef struct p2_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    int         res;
} p2_test_case;

static const p2_test_case p2_tests[] =
{
    { {  0,  +1 }, {  0,  +1 },  0 },
    { {  1,  +1 }, {  0,  +1 }, +1 },
    { {  0,  +1 }, {  1,  +1 }, -1 },
    { {  0,  +1 }, {  1,  -1 }, +1 },
    { {  1,  -1 }, {  1,  +1 }, -1 },
    { {  1,  +1 }, {  1,  -1 }, +1 },
    { {  9, +10 }, {  1,  +1 }, -1 },
    { { 11, +10 }, {  1,  +1 }, +1 },
    { {  9, +10 }, { 19, +20 }, -1 },
    { {  9, +10 }, { 17, +20 }, +1 },
};

static void p2_tester(const void *data)
{
    const p2_test_case *test = (const p2_test_case *)data;
    char buffer1[32];
    char buffer2[32];

    int rc = ri_cmp(test->lhs, test->rhs);
    if (rc != test->res)
        pt_fail("unexpected result (%s <=> %s) gave %+d instead of %+d\n",
                 ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                 ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                 rc, test->res);
    else
        pt_pass("(%s <=> %s) = %+d\n",
                 ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                 ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                 test->res);
}

/* -- PHASE 3 TESTING -- */

/* -- ri_add -- */
typedef struct p3_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    RationalInt res;
} p3_test_case;

static const p3_test_case p3_tests[] =
{
    { {  0,  1 }, {  0,  1 }, {    0,   1 } },
    { {  1,  1 }, {  0,  1 }, {    1,   1 } },
    { {  1,  1 }, {  1,  1 }, {    2,   1 } },
    { {  1,  1 }, {  1, -1 }, {    0,   1 } },
    { { 23, 31 }, { 37, 19 }, { 1584, 589 } },
    { { 14, -9 }, { 12, -7 }, {  206, -63 } },
    { { 14, -9 }, { 12, +7 }, {   10, +63 } },
    { { 14, +9 }, { 12, -7 }, {   10, -63 } },
    { { 14, +9 }, { 12, +7 }, {  206, +63 } },
};

static void p3_tester(const void *data)
{
    const p3_test_case *test = (const p3_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];

    RationalInt res = ri_add(test->lhs, test->rhs);
    int rc = ri_cmp(test->res, res);
    if (rc != 0)
        pt_fail("unexpected result for %s + %s (actual %s vs wanted %s: %d)\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(res,       buffer3, sizeof(buffer3)),
                ri_fmt(test->res, buffer4, sizeof(buffer4)),
                rc);
    else
        pt_pass("%s + %s = %s\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(test->res, buffer3, sizeof(buffer3)));
}

/* -- PHASE 4 TESTING -- */

/* -- ri_sub -- */
typedef struct p4_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    RationalInt res;
} p4_test_case;

static const p4_test_case p4_tests[] =
{
    { {  0,  1 }, {  0,  1 }, {    0,    1 } },
    { {  1,  1 }, {  0,  1 }, {    1,    1 } },
    { {  1,  1 }, {  1,  1 }, {    0,    1 } },
    { {  1, -1 }, {  1,  1 }, {    2,   -1 } },
    { {  1, -1 }, {  2, -1 }, {    1,    1 } },
    { {  1,  1 }, {  1, -1 }, {    2,    1 } },
    { { 23, 31 }, { 37, 19 }, {  710, -589 } },
    { { 14, -9 }, { 12, -7 }, {   10,  +63 } },
    { { 14, -9 }, { 12, +7 }, {  206,  -63 } },
    { { 14, +9 }, { 12, -7 }, {  206,  +63 } },
    { { 14, +9 }, { 12, +7 }, {   10,  -63 } },
};

static void p4_tester(const void *data)
{
    const p4_test_case *test = (const p4_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];

    RationalInt res = ri_sub(test->lhs, test->rhs);
    int rc = ri_cmp(test->res, res);
    if (rc != 0)
        pt_fail("unexpected result for %s - %s (actual %s vs wanted %s: %d)\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(res,       buffer3, sizeof(buffer3)),
                ri_fmt(test->res, buffer4, sizeof(buffer4)),
                rc);
    else
        pt_pass("%s - %s = %s\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(test->res, buffer3, sizeof(buffer3)));
}

/* -- PHASE 5 TESTING -- */

/* -- ri_mul -- */
typedef struct p5_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    RationalInt res;
} p5_test_case;

static const p5_test_case p5_tests[] =
{
    { {  0,  1 }, {  0,  1 }, {    0,    1 } },
    { {  1,  1 }, {  0,  1 }, {    0,    1 } },
    { {  1,  1 }, {  1,  1 }, {    1,    1 } },
    { {  1, -1 }, {  1,  1 }, {    1,   -1 } },
    { {  1, -1 }, {  2, -1 }, {    2,    1 } },
    { {  1,  1 }, {  1, -1 }, {    1,   -1 } },
    { { 23, 31 }, { 37, 19 }, {  851,  589 } },
    { { 14, -9 }, { 12, -7 }, {    8,   +3 } },
    { { 14, -9 }, { 12, +7 }, {    8,   -3 } },
    { { 14, +9 }, { 12, -7 }, {    8,   -3 } },
    { { 14, +9 }, { 12, +7 }, {    8,   +3 } },
};

static void p5_tester(const void *data)
{
    const p5_test_case *test = (const p5_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];

    RationalInt res = ri_mul(test->lhs, test->rhs);
    int rc = ri_cmp(test->res, res);
    if (rc != 0)
        pt_fail("unexpected result for %s * %s (actual %s vs wanted %s: %d)\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(res,       buffer3, sizeof(buffer3)),
                ri_fmt(test->res, buffer4, sizeof(buffer4)),
                rc);
    else
        pt_pass("%s * %s = %s\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(test->res, buffer3, sizeof(buffer3)));
}

/* -- PHASE 6 TESTING -- */

/* -- ri_div -- */
typedef struct p6_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    RationalInt res;
} p6_test_case;

static const p6_test_case p6_tests[] =
{
    { {  0,  1 }, {  1,  1 }, {    0,    1 } },
    { {  1,  1 }, {  1,  1 }, {    1,    1 } },
    { {  1, -1 }, {  1,  1 }, {    1,   -1 } },
    { {  1, -1 }, {  2, -1 }, {    1,    2 } },
    { {  1,  1 }, {  1, -1 }, {    1,   -1 } },
    { { 23, 31 }, { 37, 19 }, {  437, 1147 } },
    { { 14, -9 }, { 12, -7 }, {   49,  +54 } },
    { { 14, -9 }, { 12, +7 }, {   49,  -54 } },
    { { 14, +9 }, { 12, -7 }, {   49,  -54 } },
    { { 14, +9 }, { 12, +7 }, {   49,  +54 } },
};

static void p6_tester(const void *data)
{
    const p6_test_case *test = (const p6_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];

    RationalInt res = ri_div(test->lhs, test->rhs);
    int rc = ri_cmp(test->res, res);
    if (rc != 0)
        pt_fail("unexpected result for %s / %s (actual %s vs wanted %s: %d)\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(res,       buffer3, sizeof(buffer3)),
                ri_fmt(test->res, buffer4, sizeof(buffer4)),
                rc);
    else
        pt_pass("%s / %s = %s\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(test->res, buffer3, sizeof(buffer3)));
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "ri_new" },
    { p2_tester, PT_ARRAYINFO(p2_tests), 0, "ri_cmp" },
    { p3_tester, PT_ARRAYINFO(p3_tests), 0, "ri_add" },
    { p4_tester, PT_ARRAYINFO(p4_tests), 0, "ri_sub" },
    { p5_tester, PT_ARRAYINFO(p5_tests), 0, "ri_mul" },
    { p6_tester, PT_ARRAYINFO(p6_tests), 0, "ri_div" },
};

int main(int argc, char **argv)
{
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

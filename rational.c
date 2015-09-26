#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

typedef struct RationalInt
{
    int     numerator;
    int     denominator;
} RationalInt;

extern RationalInt ri_new(int numerator, int denominator);
extern RationalInt ri_add(RationalInt v1, RationalInt v2);
extern RationalInt ri_sub(RationalInt v1, RationalInt v2);
extern RationalInt ri_mul(RationalInt v1, RationalInt v2);
extern RationalInt ri_div(RationalInt v1, RationalInt v2);

#endif /* RATIONAL_H_INCLUDED */

#include "gcd.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

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
        int dv = gcd(numerator, denominator);
        assert(numerator == 0 || dv != 0);
        ri.numerator = numerator / dv;
        ri.denominator = denominator / dv;
    }
    return ri;
}

RationalInt ri_add(RationalInt v1, RationalInt v2)
{
    long long rn = v1.numerator * v2.denominator + v2.numerator * v1.denominator;
    long long rd = v1.denominator * v2.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_sub(RationalInt v1, RationalInt v2)
{
    long long rn = v1.numerator * v2.denominator - v2.numerator * v1.denominator;
    long long rd = v1.denominator * v2.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_mul(RationalInt v1, RationalInt v2)
{
    long long rn = v1.numerator * v2.numerator;
    long long rd = v1.denominator * v2.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_div(RationalInt v1, RationalInt v2)
{
    assert(v2.numerator != 0);
    long long rn = v1.numerator * v2.denominator;
    long long rd = v1.denominator * v2.numerator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
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
    int o_num;
    int o_den;
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { .i_num =  1, .i_den =  1, .o_num =  1, .o_den =  1 },
    { .i_num =  0, .i_den =  1, .o_num =  0, .o_den =  1 },
    { .i_num =  2, .i_den =  2, .o_num =  1, .o_den =  1 },
    { .i_num =  1, .i_den =  2, .o_num =  1, .o_den =  2 },
    { .i_num = 15, .i_den =  3, .o_num =  5, .o_den =  1 },
    { .i_num = 28, .i_den =  6, .o_num = 14, .o_den =  3 },
    { .i_num =  6, .i_den = 28, .o_num =  3, .o_den = 14 },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;

    RationalInt ri = ri_new(test->i_num, test->i_den);

    if (ri.denominator != test->o_den ||
        ri.numerator != test->o_num)
        pt_fail("ri_new(%d, %d) - unexpected result [%d/%d] (instead of [%d/%d])\n",
                test->i_num, test->i_den, ri.numerator, ri.denominator,
                test->o_num, test->o_den);
    else
        pt_pass("ri_new(%d, %d) - [%d/%d]\n",
                test->i_num, test->i_den, test->o_num, test->o_den);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "ri_new" },
};

int main(int argc, char **argv)
{
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

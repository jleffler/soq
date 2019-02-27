/*
@(#)File:           gcd.c
@(#)Purpose:        Implement Greatest Common Divisor for two integers
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1993-2017
@(#)Derivation:     gcd.c 1.8 2017/08/25 22:50:04
*/

/*TABSTOP=4*/

#include "gcd.h"

DEFINE_GCD_FUNCTION(extern, int, gcd)
DEFINE_GCD_FUNCTION(extern, unsigned long long, gcd_ull)

#if defined(TEST)

#include <stdio.h>
#include <stdlib.h>

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

typedef struct gcd_test
{
    int     x;
    int     y;
    int     r;
} gcd_test;

static gcd_test gcd_list[] =
{
    { 0, 1, 0 },
    { 1, 1, 1 },
    { 2, 1, 1 },
    { 3, 1, 1 },
    { 3, 2, 1 },
    { 4, 2, 2 },
    { 8, 2, 2 },
    { 16, 3, 1 },
    { 16, 4, 4 },
    { 16, 6, 2 },
    { 16, 12, 4 },
    { 4795615, 2310, 55 },
};

typedef unsigned long long ULL;

static size_t test_gcd(int x, int y, int z)
{
    size_t f = 0;
    int r = gcd(x, y);

    if (r != z)
        f = 1;
    printf("%s GCD(%7d, %7d) = %7d (%7d expected)\n",
            (r == z) ? "PASS" : "FAIL", x, y, r, z);
    return(f);
}

static size_t test_gcd_ull(unsigned long long x, unsigned long long y, unsigned long long z)
{
    size_t f = 0;
    unsigned long long r = gcd_ull(x, y);

    if (r != z)
        f = 1;
    printf("%s GCD(%7lld, %7lld) = %7lld (%7lld expected)\n",
            (r == z) ? "PASS" : "FAIL", x, y, r, z);
    return(f);
}

int main(void)
{
    size_t i;
    size_t n = DIM(gcd_list);
    size_t f = 0;

    for (i = 0; i < n; i++)
    {
        f += test_gcd(gcd_list[i].x, gcd_list[i].y, gcd_list[i].r);
        f += test_gcd(gcd_list[i].y, gcd_list[i].x, gcd_list[i].r);
        f += test_gcd_ull((ULL)gcd_list[i].x, (ULL)gcd_list[i].y, (ULL)gcd_list[i].r);
        f += test_gcd_ull((ULL)gcd_list[i].y, (ULL)gcd_list[i].x, (ULL)gcd_list[i].r);
    }
    if (f != 0)
        printf("*** FAILED *** (%lu tests out of %lu)\n", (unsigned long)f, (unsigned long)(2 * n));
    else
        printf("=== PASSED === (%lu tests)\n", (unsigned long)(2 * n));
    return((f == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}

#endif /* TEST */

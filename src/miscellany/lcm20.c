/*
** LCM of numbers 1 to N - where N is currently 46 (using 64 bits).
** Going to 47 requires an extra factor of 47 and overflows.
*/
#include "gcd.h"
#include <stdio.h>

/* Divide by GCD before multiplying to delay onset of overflow */
static unsigned long long lcm(unsigned long long x, unsigned long long y)
{
    return x * (y / gcd_ull(x, y));
}

static void test(unsigned long long m)
{
    unsigned long long v = 1;

    for (unsigned long long i = 2; i <= m; i++)
        v = lcm(i, v);
    printf("For m = %2llu, v = %20llu\n", m, v);
}

int main(void)
{
    for (unsigned long long i = 1; i <= 46; i++)
        test(i);
    return 0;
}

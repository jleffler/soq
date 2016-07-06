#include <stdio.h>
#include <inttypes.h>

/*
** Using documented GCC type unsigned __int128 instead of undocumented
** obsolescent typedef name __uint128_t.  Works with GCC 4.7.1 but not
** GCC 4.1.2 (but __uint128_t works with GCC 4.1.2) on Mac OS X 10.7.4.
*/
typedef unsigned __int128 uint128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

static int print_u128_u(uint128_t u128)
{
    int rc;
    if (u128 > UINT64_MAX)
    {
        uint128_t leading  = u128 / P10_UINT64;
        uint64_t  trailing = u128 % P10_UINT64;
        rc = print_u128_u(leading);
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc;
}

int main(void)
{
    uint128_t u128a = ((uint128_t)UINT64_MAX + 1) * 0x1234567890ABCDEFULL + 0xFEDCBA9876543210ULL;
    uint128_t u128b = ((uint128_t)UINT64_MAX + 1) * 0xF234567890ABCDEFULL + 0x1EDCBA987654320FULL;
    int ndigits = print_u128_u(u128a);
    printf("\n%d digits\n", ndigits);
    ndigits = print_u128_u(u128b);
    printf("\n%d digits\n", ndigits);
    return(0);
}

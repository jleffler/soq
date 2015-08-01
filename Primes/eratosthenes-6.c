/* Segmented Sieve of Eratosthenes */
/* See SO 10249378 */

/*
** For a given range of primes L..H, determine N = sqrt(H) and the set
** of odd primes P between 3 and N (we know about 2 as a prime and can
** ignore even numbers from here on).
** Then, for convenient sub-sections of the range L..H, P..Q, repeat the process:
**  - Mark all odd numbers in the range P..Q as possibly prime
**  - For each element E in P
**    - Establish the minimum value in P..Q that is an odd multiple of E
**    - Mark multiples of that E from there onwards as non-prime (composite)
**  - Any numbers not marked composite are primes.
** This code continues the count and sum (and optional printing)
** tradition, but formalizes it.
*/

#include "isqrt.h"
#include "stderr.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIME 1000000ULL

static uint64_t min_u64(uint64_t x, uint64_t y) { return (x < y) ? x : y; }

static void set_mark(uint64_t *sieve, uint64_t i)
{
    uint64_t x = 1ULL << (i % 64);
    uint64_t y = i / 64;
    sieve[y] |= x;
}

static int is_marked(uint64_t *sieve, uint64_t i)
{
    uint64_t x = 1ULL << (i % 64);
    uint64_t y = i / 64;
    return (sieve[y] & x) == 0;
}

static void set_range_mark(uint64_t *sieve, uint64_t b, uint64_t i)
{
    assert(sieve != 0);
    assert(b <= i);
    assert(i % 2 == 1);
    uint64_t x = 1ULL << ((i - b) % 64);
    uint64_t y = (i - b) / 64;
    sieve[y] |= x;
}

static int is_range_marked(uint64_t *sieve, uint64_t b, uint64_t i)
{
    assert(sieve != 0);
    assert(b <= i);
    //assert(i % 2 == 1);
    uint64_t x = 1ULL << ((i - b) % 64);
    uint64_t y = (i - b) / 64;
    return (sieve[y] & x) == 0;
}

static uint64_t first_multiple_in_range(uint64_t base, uint64_t val)
{
    assert(val % 2 == 1);
    uint64_t begin = base / val;
    if (begin % 2 == 0)
        begin++;
    return begin * val;
}

static void mark_odd_multiples(uint64_t *range, uint64_t base, uint64_t limit, uint64_t val)
{
    for (uint64_t j = first_multiple_in_range(base, val); j < limit; j += 2 * val)
        set_range_mark(range, base, j);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    uint64_t max = MAX_PRIME;

    if (argc > 1)
        max = strtoull(argv[1], 0, 0);
    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %" PRIu64 "\n", max);
    }

    uint64_t sqrt_max = isqrt_64(max);
    printf("Max %" PRIu64 "; Sqrt %" PRIu64 "\n", max, sqrt_max);

    //if ((sieve = calloc(MAX_PRIME / (64 * 2), sizeof(uint64_t))) == 0)
    size_t    space = (sqrt_max + 127) / 128;
    uint64_t *sieve = calloc(space, sizeof(uint64_t));
    if (sieve == 0)
    {
        fprintf(stderr, "Failed to allocate enough space (%zu bytes)\n", space * sizeof(uint64_t));
        exit(1);
    }

    printf("P 2\n");
    printf("P 3\n");
    for (uint64_t j = 3 * (3); j < sqrt_max; j += 2 * (3))
        set_mark(sieve, j / 2);

    for (uint64_t i = 6; i <= sqrt_max; i += 6)
    {
        if (!is_marked(sieve, (i - 1) / 2) == 0)
        {
            printf("P %" PRIu64 "\n", i - 1);
            for (uint64_t j = 3 * (i - 1); j < sqrt_max; j += 2 * (i - 1))
                set_mark(sieve, j / 2);
        }
        if (!is_marked(sieve, (i + 1) / 2) == 0)
        {
            printf("P %" PRIu64 "\n", i + 1);
            for (uint64_t j = 3 * (i + 1); j < sqrt_max; j += 2 * (i + 1))
                set_mark(sieve, j / 2);
        }
    }
    putchar('\n');

    if (argc > 1)
    {
        free(sieve);
        return(0);
    }

    /*
    ** Basic set of primes up to (square root of maximum)  + 1 established.
    ** Now, for convenient sized chunks between that and the actual maximum:
    ** Zero all the values.  Mark the non-primes.  Then deal with the primes.
    */
    enum { MAX_CHUNK = 10000 };  // Chunk size is somewhat arbitrary, but less than MAX_PRIME
    uint64_t sum = 5;
    uint64_t cnt = 2;
    size_t   rsize = min_u64(MAX_CHUNK, max / 4) / (64 * 2);
    uint64_t *range = malloc(rsize * sizeof(uint64_t));

    for (uint64_t base = 0; base < max; base += rsize)
    {
        printf("Range: %" PRIu64 "-%zu\n", base, rsize);
        /* Zero all the values */
        memset(range, '\0', rsize * sizeof(uint64_t));
        uint64_t limit = min_u64(base + MAX_CHUNK, max);

        /* Mark the non-primes */
        /* Mark multiples of 3 as non-prime */
        for (uint64_t begin = first_multiple_in_range(base, 3); begin < limit; begin += 2 * 3)
            set_range_mark(range, base, begin);

        /* Mark multiples of bigger primes as non-prime */
        uint64_t i;
        for (i = 6; i <= sqrt_max; i += 6)
        {
            if (!is_marked(sieve, (i - 1)/2))
                mark_odd_multiples(range, base, limit, i - 1);
            if (!is_marked(sieve, (i + 1)/2))
                mark_odd_multiples(range, base, limit, i + 1);
        }

        /* Process the primes */
        for ( ; i < max; i += 6)
        {
            if (!is_range_marked(range, base, (i - 1) / 2) == 0)
            {
                sum += i - 1;
                cnt++;
                printf("P %" PRIu64 "\n", i - 1);
            }
            if (!is_range_marked(range, base, (i + 1) / 2) == 0)
            {
                sum += i + 1;
                cnt++;
                printf("P %" PRIu64 "\n", i + 1);
            }
        }
    }

    printf("Sum   of primes to %" PRIu64 " = %" PRIu64 "\n", max, sum);
    printf("Count of primes to %" PRIu64 " = %" PRIu64 "\n", max, cnt);

    free(range);
    free(sieve);
    return 0;
}

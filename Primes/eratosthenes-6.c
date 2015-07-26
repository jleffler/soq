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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include "isqrt.h"

#define MAX_PRIME 1000000ULL

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

int main(int argc, char **argv)
{
    uint64_t max = MAX_PRIME;

    if (argc > 1)
        max = atoi(argv[1]);
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

    //printf("2\n");
    //printf("3\n");
    for (uint64_t j = 3 * (3); j < sqrt_max; j += 2 * (3))
        set_mark(sieve, j / 2);

    uint64_t i;
    uint64_t sum = 5;
    uint64_t cnt = 2;
    for (i = 6; i <= sqrt_max; i += 6)
    {
        if (!is_marked(sieve, (i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            //printf("%" PRIu64 "\n", i - 1);
            for (uint64_t j = 3 * (i - 1); j < sqrt_max; j += 2 * (i - 1))
                set_mark(sieve, j / 2);
        }
        if (!is_marked(sieve, (i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            //printf("%" PRIu64 "\n", i + 1);
            for (uint64_t j = 3 * (i + 1); j < sqrt_max; j += 2 * (i + 1))
                set_mark(sieve, j / 2);
        }
    }

    /*
    ** Basic set of primes up to square root of maximum established.
    ** Now, for convenient sized chunks between that and the actual maximum:
    ** Zero all the values.  Mark the non-primes.  Then deal with the primes.
    */
    if (0)
    {

    for ( ; i < max; i += 6)
    {
        if (!is_marked(sieve, (i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            //printf("%" PRIu64 "\n", i - 1);
        }
        if (!is_marked(sieve, (i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            //printf("%" PRIu64 "\n", i + 1);
        }
    }
    }

    printf("Sum   of primes to %" PRIu64 " = %" PRIu64 "\n", max, sum);
    printf("Count of primes to %" PRIu64 " = %" PRIu64 "\n", max, cnt);

    free(sieve);
    return 0;
}

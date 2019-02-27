/* Segmented Sieve of Eratosthenes */
/* See SO 1024-9378 */

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

/*
** Currently, this is mostly a piece of spaghetti.
*/

#include "posixver.h"
//#include "debug.h"
#define WRAPPED_HEADER "debug.h"
#include "wraphead.h"

#define WRAPPED_HEADER "stderr.h"
#include "wraphead.h"
//#include "stderr.h"

#include "isqrt.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(DEBUG)
#define DEBUG_OPT "d:"
#define DEBUG_USE " [-d level]"
#define DEBUG_HLP "  -d level    Enable debugging at level (0-4)\n"
#else
#define DEBUG_OPT ""
#define DEBUG_USE ""
#define DEBUG_HLP ""
#endif /* DEBUG */

static const char optstr[] = "hVs:u:" DEBUG_OPT;
static const char usestr[] = "[-hV]" DEBUG_USE " [-s segsize] [-u] upper";
static const char hlpstr[] =
    DEBUG_HLP
    "  -h          Print this help message and exit\n"
    "  -s segsize  Set segment size\n"
    "  -u upper    Upper bound on range\n"
    "  -V          Print version information and exit\n"
    ;

//#define MAX_PRIME 1000_000_000_000ULL
#define MAX_PRIME (1000000ULL * 1000000ULL)

static uint64_t min_u64(uint64_t x, uint64_t y) { return (x < y) ? x : y; }

static void set_mark(uint64_t *sieve, uint64_t i)
{
    assert((i & 1) == 1);
    uint64_t x = 1ULL << ((i >>= 1) % 64);
    uint64_t y = i / 64;
    sieve[y] |= x;
}

static int is_marked(uint64_t *sieve, uint64_t i)
{
    assert((i & 1) == 1);
    uint64_t x = 1ULL << ((i >>= 1) % 64);
    uint64_t y = i / 64;
    return (sieve[y] & x) == 0;
}

static void set_range_mark(uint64_t *sieve, uint64_t b, uint64_t i)
{
    assert(sieve != 0);
    DB_TRACE(4, "SRM: b = %" PRIu64 ", i = %" PRIu64 "\n", b, i);
    assert(b <= i);
    assert(i % 2 == 1);
    uint64_t x = 1ULL << (((i - b) / 2) % 64);
    uint64_t y = (i - b) / (2 * 64);
    sieve[y] |= x;
}

static int is_range_marked(uint64_t *sieve, uint64_t b, uint64_t i)
{
    assert(sieve != 0);
    assert(b <= i);
    assert(i % 2 == 1);
    uint64_t x = 1ULL << (((i - b) / 2) % 64);
    uint64_t y = (i - b) / (2 * 64);
    return (sieve[y] & x) == 0;
}

static uint64_t first_multiple_in_range(uint64_t base, uint64_t val)
{
    DB_TRACE(3, "FMR: b = %" PRIu64 ", v = %" PRIu64, base, val);
    uint64_t begin = (base + val - 1) / val;
    if (begin == 0 && base == 0)    // Avoid treating 1 as a prime
        begin++;
    DB_TRACE(3, ", r = %" PRIu64 "\n", begin * val);
    return begin * val;
}

static uint64_t first_odd_multiple_in_range(uint64_t base, uint64_t val)
{
    assert(val % 2 == 1);
    DB_TRACE(3, "FOM: b = %" PRIu64 ", v = %" PRIu64, base, val);
    uint64_t begin = base / val + 1;
    if (begin == 1)
        begin = 3;
    else if (begin % 2 == 0)
        begin++;
    DB_TRACE(3, ", r = %" PRIu64 "\n", begin * val);
    return begin * val;
}

static void mark_odd_multiples(uint64_t *range, uint64_t base, uint64_t limit, uint64_t val)
{
    for (uint64_t j = first_odd_multiple_in_range(base, val); j <= limit; j += 2 * val)
        set_range_mark(range, base, j);
}

static uint64_t *basic_sieve(uint64_t sqrt_max)
{
    size_t    space = (sqrt_max + 127) / 128;
    uint64_t *sieve = (uint64_t *)calloc(space, sizeof(uint64_t));  /*=C++=*/

    if (sieve == 0)
    {
        fprintf(stderr, "Failed to allocate enough space (%zu bytes)\n", space * sizeof(uint64_t));
        exit(1);
    }

    DB_TRACE(2, "P 2\n");
    DB_TRACE(2, "P 3\n");
    for (uint64_t j = 3 * (3); j <= sqrt_max; j += 2 * (3))
        set_mark(sieve, j);

    for (uint64_t i = 6; i <= sqrt_max; i += 6)
    {
        if (!is_marked(sieve, (i - 1)) == 0)
        {
            DB_TRACE(2, "P %" PRIu64 "\n", i - 1);
            for (uint64_t j = 3 * (i - 1); j < sqrt_max; j += 2 * (i - 1))
                set_mark(sieve, j);
        }
        if ((i + 1) <= sqrt_max && !is_marked(sieve, (i + 1)) == 0)
        {
            DB_TRACE(2, "P %" PRIu64 "\n", i + 1);
            for (uint64_t j = 3 * (i + 1); j < sqrt_max; j += 2 * (i + 1))
                set_mark(sieve, j);
        }
    }
    DB_TRACE(2, "\n");
    return sieve;
}

struct prime_info
{
    uint64_t    sum0;
    uint64_t    sum1;
    uint64_t    count;
};

static void apply(uint64_t prime, struct prime_info *data)
{
    if (UINT64_MAX - data->sum0 < prime)
    {
        data->sum1++;
        data->sum0 = prime - (UINT64_MAX - data->sum0);
    }
    data->sum0 += prime;
    data->count++;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    uint64_t max = MAX_PRIME;
    uint64_t seg = 0;
    int opt;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'd':
            db_setdebug(atoi(optarg));
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("ERATOSTHENES-6", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        case 's':
            seg = strtoull(optarg, 0, 0);
            break;
        case 'u':
            max = strtoull(optarg, 0, 0);
            break;
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (argc > optind + 1)
        err_usage(usestr);
    else if (argc == optind + 1)
        max = strtoull(argv[optind], 0, 0);

    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %" PRIu64 "\n", max);
    }

    uint64_t sqrt_max = isqrt_64(max);
    DB_TRACE(1, "Max %" PRIu64 "; Sqrt %" PRIu64 "\n", max, sqrt_max);

    uint64_t *sieve = basic_sieve(sqrt_max);

    /*
    ** Basic set of primes up to (square root of maximum)  + 1 established.
    ** Now, for convenient sized segment between that and the actual maximum:
    ** Zero all the values.  Mark the non-primes.  Then deal with the primes.
    */
    enum { MAX_SEGMENT = 10000000 };  // Segment size is arbitrary, but less than MAX_PRIME
    //enum { MIN_SEGMENT = 10000 };     // Too small and it makes no sense to segment
    enum { MIN_SEGMENT = 100 };     // Too small and it makes no sense to segment
    /* NB: make sure that testing works both above and below MIN_SEGMENT */

    struct prime_info info = { .sum0 = 0, .sum1 = 0, .count = 0 };
    if (max >= 2)
        apply(2, &info);            // 2 is prime
    if (max >= 3)
        apply(3, &info);            // 3 is prime

    uint64_t csize = min_u64(MAX_SEGMENT, (max + 3) / 4);
    if (seg != 0)
        csize = seg;

    if (max < MIN_SEGMENT)
    {
        DB_TRACE(1, "Maximum number less than %d: just one segment\n", MIN_SEGMENT);
        csize = MIN_SEGMENT;
    }

    if ((csize & 1) == 1)
        csize++;
    size_t   rsize = (csize + (64*2 - 1)) / (64 * 2);
    size_t   msize = rsize * sizeof(uint64_t);
    uint64_t *range = (uint64_t *)malloc(msize);    /*=C++=*/
    DB_TRACE(1, "csize %" PRIu64 ", rsize = %zu, msize = %zu\n", csize, rsize, msize);

    for (uint64_t base = 0; base < max; base += csize)
    {
        uint64_t limit = min_u64(base + csize, max);
        DB_TRACE(1, "Range: %" PRIu64 "-%" PRIu64 "\n", base, limit);
        /* Zero all the values */
        memset(range, '\0', msize);

        /* Mark the non-primes */
        /* Mark multiples of 3 as non-prime */
        DB_TRACE(2, "M 3\n");
        for (uint64_t begin = first_odd_multiple_in_range(base, 3); begin < limit; begin += 2 * 3)
            set_range_mark(range, base, begin);

        /* Mark multiples of bigger primes as non-prime */
        for (uint64_t i = 6; (i - 1) <= sqrt_max; i += 6)
        {
            DB_TRACE(2, "T %" PRIu64 "\n", i-1);
            if (is_marked(sieve, i - 1))
            {
                DB_TRACE(2, "M %" PRIu64 "\n", i-1);
                mark_odd_multiples(range, base, limit, i - 1);
            }
            DB_TRACE(2, "T %" PRIu64 "\n", i+1);
            if ((i + 1) <= sqrt_max && is_marked(sieve, i + 1))
            {
                DB_TRACE(2, "M %" PRIu64 "\n", i+1);
                mark_odd_multiples(range, base, limit, i + 1);
            }
        }
        DB_TRACE(2, "F\n");

        /* Process the primes */
        uint64_t i = first_multiple_in_range(base, 6);
        if (i == base)
        {
            DB_TRACE(2, "I1 = %" PRIu64, i);
            if ((i + 1) <= limit &&!is_range_marked(range, base, i + 1) == 0)
            {
                apply(i + 1, &info);
                DB_TRACE(2, " P %" PRIu64, i + 1);
            }
            DB_TRACE(2, "\n");
            i += 6;
        }

        for ( ; (i - 1) <= limit; i += 6)
        {
            DB_TRACE(2, "I2 = %" PRIu64, i);
            if (!is_range_marked(range, base, i - 1) == 0)
            {
                apply(i - 1, &info);
                DB_TRACE(2, " P %" PRIu64, i - 1);
            }
            if ((i + 1) <= limit && !is_range_marked(range, base, i + 1) == 0)
            {
                apply(i + 1, &info);
                DB_TRACE(2, " P %" PRIu64, i + 1);
            }
            DB_TRACE(2, "\n");
        }

        if (i == limit)
        {
            DB_TRACE(2, "I3 = %" PRIu64, i);
            if (!is_range_marked(range, base, i - 1) == 0)
            {
                apply(i - 1, &info);
                DB_TRACE(2, " P %" PRIu64, i - 1);
            }
            DB_TRACE(2, "\n");
        }
    }

    if (info.sum1 > 0)
        printf("High order value of sum: %" PRIu64 "\n", info.sum1);
    printf("Sum   of primes to %" PRIu64 " = %" PRIu64 "\n", max, info.sum0);
    printf("Count of primes to %" PRIu64 " = %" PRIu64 "\n", max, info.count);

    free(range);
    free(sieve);
    return 0;
}

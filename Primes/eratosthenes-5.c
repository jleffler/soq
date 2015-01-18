#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#define MAX_PRIME 10000000000ULL
static uint64_t sieve[MAX_PRIME/(64 * 2)];

static void set_mark(uint64_t i)
{
    uint64_t x = 1ULL << (i % 64);
    uint64_t y = i / 64;
    sieve[y] |= x;
}

static int is_marked(uint64_t i)
{
    uint64_t x = 1ULL << (i % 64);
    uint64_t y = i / 64;
    return (sieve[y] & x) == 0;
}

int main(int argc, char **argv)
{
    uint64_t i;
    uint64_t max = MAX_PRIME;
    uint64_t sum = 5;
    uint64_t cnt = 2;

    if (argc > 1)
        max = atoi(argv[1]);
    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %" PRIu64 "\n", max);
    }

    //printf("2\n");
    //printf("3\n");
    for (uint64_t j = 3 * (3); j < max; j += 2 * (3))
        set_mark(j / 2);
    uint64_t sqrt_max = sqrt(max);

    for (i = 6; i <= sqrt_max; i += 6)
    {
        if (!is_marked((i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            //printf("%" PRIu64 "\n", i - 1);
            for (uint64_t j = 3 * (i - 1); j < max; j += 2 * (i - 1))
                set_mark(j / 2);
        }
        if (!is_marked((i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            //printf("%" PRIu64 "\n", i + 1);
            for (uint64_t j = 3 * (i + 1); j < max; j += 2 * (i + 1))
                set_mark(j / 2);
        }
    }

    for ( ; i < max; i += 6)
    {
        if (!is_marked((i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            //printf("%" PRIu64 "\n", i - 1);
        }
        if (!is_marked((i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            //printf("%" PRIu64 "\n", i + 1);
        }
    }

    printf("Sum   of primes to %" PRIu64 " = %" PRIu64 "\n", max, sum);
    printf("Count of primes to %" PRIu64 " = %" PRIu64 "\n", max, cnt);
    return 0;
}

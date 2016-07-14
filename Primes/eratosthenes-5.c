#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 1E10 ie OK; 1E12 is too much */
//#define MAX_PRIME 1000_000_000_000ULL
#define MAX_PRIME (100000ULL * 100000ULL)
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
    uint64_t sum = 0;
    uint64_t cnt = 0;
    int opt;
    int verbose = 0;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            verbose = 1;
            break;
        default:
            return EXIT_FAILURE;
        }
    }

    if (optind == argc - 1)
        max = atoi(argv[optind]);
    else if (optind < argc - 1)
    {
        fprintf(stderr, "%s: Too many arguments!\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %" PRIu64 "\n", max);
    }

    if (max >= 2)
    {
        if (verbose)
            printf("2\n");
        sum += 2;
        cnt++;
    }

    if (max >= 3)
    {
        if (verbose)
            printf("3\n");
        sum += 3;
        cnt++;
    }

    for (uint64_t j = 3 * (3); j <= max; j += 2 * (3))
        set_mark(j / 2);
    uint64_t sqrt_max = sqrt(max);

    for (i = 6; (i - 1) <= sqrt_max; i += 6)
    {
        if (!is_marked((i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            if (verbose)
                printf("%" PRIu64 "\n", i - 1);
            for (uint64_t j = 3 * (i - 1); j <= max; j += 2 * (i - 1))
                set_mark(j / 2);
        }
        if (!is_marked((i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            if (verbose)
                printf("%" PRIu64 "\n", i + 1);
            for (uint64_t j = 3 * (i + 1); j <= max; j += 2 * (i + 1))
                set_mark(j / 2);
        }
    }

    for ( ; (i - 1) <= max; i += 6)
    {
        if (!is_marked((i - 1) / 2) == 0)
        {
            sum += i - 1;
            cnt++;
            if (verbose)
                printf("%" PRIu64 "\n", i - 1);
        }
        if ((i + 1) <= max && !is_marked((i + 1) / 2) == 0)
        {
            sum += i + 1;
            cnt++;
            if (verbose)
                printf("%" PRIu64 "\n", i + 1);
        }
    }

    printf("Sum   of primes to %" PRIu64 " = %" PRIu64 "\n", max, sum);
    printf("Count of primes to %" PRIu64 " = %" PRIu64 "\n", max, cnt);
    return 0;
}

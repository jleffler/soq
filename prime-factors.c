#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64_t;

static size_t prime_factors(u64_t value, u64_t *array)
{
    size_t n_factors = 0;
    u64_t n = value;
    u64_t i;

    while (n % 2 == 0)
    {
        n /= 2;
        //printf("Factor: %llu (n = %llu)\n", 2ULL, n);
        array[n_factors++] = 2;
    }

    while (n % 3 == 0)
    {
        n /= 3;
        //printf("Factor: %llu (n = %llu)\n", 3ULL, n);
        array[n_factors++] = 3;
    }

    for (i = 6; (i - 1) * (i - 1) <= n; i += 6)
    {   
        while (n % (i-1) == 0)
        {
            n /= (i-1);
            //printf("Factor: %llu (n = %llu)\n", (i-1), n);
            array[n_factors++] = (i-1);
        }
        while (n % (i+1) == 0)
        {
            n /= (i+1);
            //printf("Factor: %llu (n = %llu)\n", (i+1), n);
            array[n_factors++] = (i+1);
        }
    }
    if (n != 1)
        array[n_factors++] = n;

    return n_factors;
}

static u64_t max_prime_factor(u64_t value)
{
    u64_t n = value;
    u64_t i;
    u64_t max = n;

    while (n % 2 == 0)
    {
        n /= 2;
        //printf("Factor: %llu (n = %llu)\n", 2ULL, n);
        max = 2;
    }

    while (n % 3 == 0)
    {
        n /= 3;
        //printf("Factor: %llu (n = %llu)\n", 3ULL, n);
        max = 3;
    }

    for (i = 6; (i - 1) * (i - 1) <= n; i += 6)
    {   
        while (n % (i-1) == 0)
        {
            n /= (i-1);
            //printf("Factor: %llu (n = %llu)\n", (i-1), n);
            max = (i-1);
        }
        while (n % (i+1) == 0)
        {
            n /= (i+1);
            //printf("Factor: %llu (n = %llu)\n", (i+1), n);
            max = (i+1);
        }
    }
    //printf("Max Factor = %llu\n", (n == 1) ? max : n);

    return (n == 1) ? max : n;
}

static void print_factors(u64_t value, size_t n_factors, u64_t *factors)
{
    printf("%20llu:", value);
    int len = 21;
    for (size_t i = 0; i < n_factors; i++)
    {
        if (len == 0)
            len = printf("%.21s", "");
        len += printf(" %llu", factors[i]);
        if (len >= 60)
        {
            putchar('\n');
            len = 0;
        }
    }
    if (len > 0)
        putchar('\n');
}

static void builtin_tests(void)
{
    u64_t tests[] =
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
        19, 20, 25, 49, 63, 69, 71, 73, 825, 829, 1000, 6857, 73112,
        731122, 7311229, 73112293, 731122935, 7311229357, 73112293571,
        600851475143, 731122935711, 7311229357111,
        18446744073709551610ULL, 18446744073709551611ULL,
        18446744073709551612ULL, 18446744073709551613ULL,
        18446744073709551614ULL, 18446744073709551615ULL,
    };
    u64_t factors[64];

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        u64_t max = max_prime_factor(tests[i]);
        printf("%20llu -> Max Prime Factor = %llu\n", tests[i], max);
        size_t n_factors = prime_factors(tests[i], factors);
        print_factors(tests[i], n_factors, factors);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
        builtin_tests();
    else
    {
        for (int i = 1; i < argc; i++)
        {
            u64_t factors[64];
            u64_t value = strtoull(argv[i], 0, 0);
            u64_t max = max_prime_factor(value);
            printf("%20llu -> Max Prime Factor = %llu\n", value, max);
            size_t n_factors = prime_factors(value, factors);
            print_factors(value, n_factors, factors);
        }
    }
    return 0;
}

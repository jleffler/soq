/* SO 1538644 - Determine if a number is prime */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WRAPPED_HEADER "timer.h"
#include "wraphead.h"

/* Original code - extremely slow */
static int IsPrime0(unsigned number)
{
    for (unsigned i = 2; i < number; i++)
    {
        if (number % i == 0 && i != number)
            return 0;
    }
    return 1;
}

/* First step up - radically better than IsPrime0() */
static int IsPrime1(unsigned number)
{
    if (number <= 1)
        return 0;
    unsigned i;
    for (i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

/* Second step up - noticeably better than IsPrime1() */
static int IsPrime2(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 5; i * i <= number; i += 2)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

/* Slight step back - marginally slower than IsPrime2() */
static int IsPrime3(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    unsigned max = sqrt(number);
    for (unsigned i = 5; i <= max; i += 2)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

/* Third step up - noticeably better than IsPrime2() */
static int isprime1(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    unsigned max = sqrt(number) + 1;
    for (unsigned i = 6; i <= max; i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

/* Fourth step up - marginally better than isprime1() */
static int isprime2(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 6; (i - 1) * (i - 1) <= number; i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

/* Fifth step up - marginally but measurably better than isprime2() */
static int isprime3(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    unsigned int small_primes[] =
    {
         5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79, 83, 87, 89, 91, 97
    };
    enum { NUM_SMALL_PRIMES = sizeof(small_primes) / sizeof(small_primes[0]) };
    for (unsigned i = 0; i < NUM_SMALL_PRIMES; i++)
    {
        if (number % small_primes[i] == 0)
            return 0;
    }
    for (unsigned i = 102; (i - 1) * (i - 1) <= number; i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

static void test_primality_tester(const char *tag, int seed, int (*prime)(unsigned), int count)
{
    srand(seed);
    Clock clk;
    int nprimes = 0;
    clk_init(&clk);

    clk_start(&clk);
    for (int i = 0; i < count; i++)
    {
        if (prime(rand()))
            nprimes++;
    }
    clk_stop(&clk);

    char buffer[32];
    printf("%9s: %d primes found (out of %d) in %s s\n", tag, nprimes,
           count, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
}

static void bake_off(int seed, int count)
{
    srand(seed);
    Clock clk;
    clk_init(&clk);

    clk_start(&clk);

    int failures = 0;
    for (int i = 0; i < count; i++)
    {
        unsigned v = rand();
        int p1 = IsPrime1(v);
        int p2 = IsPrime2(v);
        int p3 = IsPrime3(v);
        int p4 = isprime1(v);
        int p5 = isprime2(v);
        int p6 = isprime3(v);
        if (p1 != p2 || p1 != p3 || p1 != p4 || p1 != p5 || p1 != p6)
        {
            printf("!! FAIL !! %10u: IsPrime1() %d; isPrime2() %d;"
                   " IsPrime3() %d; isprime1() %d; isprime2() %d;"
                   " isprime3() %d\n",
                   v, p1, p2, p3, p4, p5, p6);
            failures++;
        }
    }
    clk_stop(&clk);
    if (failures == 0)
    {
        char buffer[32];
        printf("== PASS == %s s\n", clk_elapsed_us(&clk, buffer, sizeof(buffer)));
    }
}

static void one_test(int seed)
{
    printf("Seed; %d\n", seed);
    enum { COUNT = 10000000 };
    bake_off(seed, COUNT);
    assert(COUNT > 100000);
    test_primality_tester("IsPrime0", seed, IsPrime0, COUNT / 100000);
    test_primality_tester("IsPrime1", seed, IsPrime1, COUNT);
    test_primality_tester("IsPrime2", seed, IsPrime2, COUNT);
    test_primality_tester("IsPrime3", seed, IsPrime3, COUNT);
    test_primality_tester("isprime1", seed, isprime1, COUNT);
    test_primality_tester("isprime2", seed, isprime2, COUNT);
    test_primality_tester("isprime3", seed, isprime3, COUNT);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            one_test(atoi(argv[i]));
    }
    else
        one_test(time(0));
    return(0);
}

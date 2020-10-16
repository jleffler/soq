/* SO 6438-1942 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stderr.h"
#include "timer.h"

#define NANO_PER_SEC 1.0E9
enum { NUM_THREADS = 8 };
enum { MAX_NUMBER  = 10000000 };

static size_t counts[NUM_THREADS];

static const unsigned int small_primes[] =
{
     5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 87, 89, 91, 97
};
enum { NUM_SMALL_PRIMES = sizeof(small_primes) / sizeof(small_primes[0]) };

/* IsPrime3B() from isprime.c - renamed is_prime() */
static int is_prime(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 0; i < NUM_SMALL_PRIMES; i++)
    {
        if (number == small_primes[i])
            return 1;
        if (number % small_primes[i] == 0)
            return 0;
    }
    /* After 97, the next prime numbers are 101, 103, 107, 109 */
    /*
    ** It would be feasible to start this loop from:
    ** i = (((small_primes[NUM_SMALL_PRIMES - 1] + 1) / 6) + 1) * 6
    */
    for (unsigned i = 102; (i - 1) <= number / (i - 1); i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

typedef struct prime_finder_vars
{
    unsigned from;
    unsigned to;
    unsigned increment;   /* Number of threads */
    unsigned idx;
} PrimeFinderVars;

static void *prime_finder(void *pf)
{
    PrimeFinderVars *pf_vars = (PrimeFinderVars *) pf;
    printf("Thread %u: from = %u, to = %u, inc = %u\n",
           pf_vars->idx, pf_vars->from, pf_vars->to, pf_vars->increment);

    unsigned next = pf_vars->from;
    while (next < pf_vars->to) {
        unsigned six_n = 6 * next;
        if (is_prime(six_n - 1))
            ++counts[pf_vars->idx];
        if (is_prime(six_n + 1))
            ++counts[pf_vars->idx];
        next += pf_vars->increment;
    }
    printf("Thread %u: done\n", pf_vars->idx);
    return pf;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1)
        err_usage("");
    struct timespec start;
    struct timespec end;
    double start_sec, end_sec, elapsed_sec;
    int sum = 0;
    Clock clk;

    clk_init(&clk);

    clk_start(&clk);
    clock_gettime(CLOCK_REALTIME, &start);

    pthread_t threads[NUM_THREADS];
    PrimeFinderVars vars[NUM_THREADS];

    int max_n = (MAX_NUMBER + 5) / 6;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        vars[i].from = i + 1;
        vars[i].to = max_n;
        vars[i].idx = i;
        vars[i].increment = NUM_THREADS;

        int rc;
        if ((rc = pthread_create(&threads[i], NULL, prime_finder, &vars[i])) != 0)
            err_syserr("failed to create thread %d: ", i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
        sum += counts[i];
    }

    clock_gettime(CLOCK_REALTIME, &end);
    clk_stop(&clk);

    start_sec = start.tv_sec + start.tv_nsec / NANO_PER_SEC;
    end_sec = end.tv_sec + end.tv_nsec / NANO_PER_SEC;
    elapsed_sec = end_sec - start_sec;
    printf("Time 1: %.6f\n", elapsed_sec);
    char buffer[32];
    printf("Time 2: %s\n", clk_elapsed_us(&clk, buffer, sizeof(buffer)));

    /* Because 2 and 3 are primes but are not analyzed */
    size_t t_count = 2;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        t_count += counts[i];
        printf("%d: %7zu primes found\n", i, counts[i]);
    }
    printf("Total primes found up to %d = %zu\n", MAX_NUMBER, t_count);

    return 0;
}


/* SO 0153-8644 - Determine if a number is prime */
#include "posixver.h"
#include "stderr.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
** NB: setitimer() is marked obsolescent in POSIX 2008.  However, the
** replacement (timer_create(), timer_delete(), timer_settime()) is not
** available in Mac OS X 10.11.5 so using the obsolescent is more
** portable than using the replacement.
*/
#ifndef NO_PROGRESS_REPORTING
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#define PROGRESS_REPORT(x)  (x)
#else
#define PROGRESS_REPORT(x)  ((void)0)
#endif

#define WRAPPED_HEADER "timer.h"
#include "wraphead.h"

static const unsigned int small_primes[] =
{
     5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 87, 89, 91, 97
};
enum { NUM_SMALL_PRIMES = sizeof(small_primes) / sizeof(small_primes[0]) };

static const unsigned int medium_primes[] =
{
    /*2,   3,*/ 5,   7,  11,  13,  17,  19,  23,  29,  31,  37,
     41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
    439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593,
    599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
    751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
    829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
    919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997,
};
enum { NUM_MEDIUM_PRIMES = sizeof(medium_primes) / sizeof(medium_primes[0]) };

/* Original code - extremely slow */
static int IsPrime0A(unsigned number)
{
    for (unsigned i = 2; i < number; i++)
    {
        if (number % i == 0)
        //if (number % i == 0 && i != number)
            return 0;
    }
    return 1;
}

/* First step up - radically better than IsPrime0A() */
static int IsPrime1A(unsigned number)
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

/* First step up - radically better than IsPrime0A() */
static int IsPrime1B(unsigned number)
{
    if (number <= 1)
        return 0;
    unsigned i;
    for (i = 2; i <= number / i; i++)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

/* Second step up - noticeably better than IsPrime1A() */
static int IsPrime2A(unsigned number)
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

/* Second step up - noticeably better than IsPrime1A() */
static int IsPrime2B(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 5; i <= number / i; i += 2)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

/* Slight step back - marginally slower than IsPrime2A() */
static int IsPrime3A(unsigned number)
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

/* Third step up - noticeably better than IsPrime2A() */
static int isprime1A(unsigned number)
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

/* Fourth step up - marginally worse than isprime1A() */
static int isprime2A(unsigned number)
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

/* Fourth step up - marginally worse than isprime1A() */
static int isprime2B(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 6; (i - 1) <= number / (i - 1); i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

/* Fifth step up - usually marginally but measurably better than isprime1A() */
static int isprime3A(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 0; i < NUM_SMALL_PRIMES && small_primes[i] * small_primes[i] <= number; i++)
    {
        if (number == small_primes[i])
            return 1;
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

/* Fifth step up - usually marginally but measurably better than isprime1A() */
static int isprime3B(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 0; i < NUM_SMALL_PRIMES && small_primes[i] <= number / small_primes[i]; i++)
    {
        if (number == small_primes[i])
            return 1;
        if (number % small_primes[i] == 0)
            return 0;
    }
    for (unsigned i = 102; (i - 1) <= number / (i - 1); i += 6)
    {
        if (number % (i - 1) == 0 || number % (i + 1) == 0)
            return 0;
    }
    return 1;
}

/*
** Late-comer.  One test showed it slightly slower than isprime3A() - but
** the same test showed isprime2A() faster than both isprime3A() and
** isprime4A()
*/
static int isprime4A(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned x = 5; x * x <= number; x += 6)
    {
        if (number % x == 0 || number % (x + 2) == 0)
            return 0;
    }
    return 1;
}

/*
** Late-comer.  One test showed it slightly slower than isprime3A() - but
** the same test showed isprime2A() faster than both isprime3A() and
** isprime4A()
*/
static int isprime4B(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned x = 5; x <= number / x; x += 6)
    {
        if (number % x == 0 || number % (x + 2) == 0)
            return 0;
    }
    return 1;
}

/* Another trial - this seems to be a little faster than either isprime3A() or isprime4A() */
static int isprime5A(unsigned number)
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
    for (unsigned i = 101; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return 0;
    }
    return 1;
}

/* Another trial - this seems to be a little faster than either isprime3A() or isprime4A() */
static int isprime5B(unsigned number)
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
    for (unsigned i = 101; i <= number / i; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return 0;
    }
    return 1;
}

/* Another trial - a little faster than isprime5A() but slower than isprime5B() */
static int isprime6A(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 0; i < NUM_MEDIUM_PRIMES; i++)
    {
        if (number == medium_primes[i])
            return 1;
        if (number % medium_primes[i] == 0)
            return 0;
    }
    for (unsigned i = 1001; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return 0;
    }
    return 1;
}

/* Another trial - somewhat faster than isprime5B() */
static int isprime6B(unsigned number)
{
    if (number <= 1)
        return 0;
    if (number == 2 || number == 3)
        return 1;
    if (number % 2 == 0 || number % 3 == 0)
        return 0;
    for (unsigned i = 0; i < NUM_MEDIUM_PRIMES; i++)
    {
        if (number == medium_primes[i])
            return 1;
        if (number % medium_primes[i] == 0)
            return 0;
    }
    for (unsigned i = 1001; i <= number / i; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
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

/* XXX: probably time to use an array! */
static int check_number(unsigned v)
{
    int p1a = IsPrime1A(v);
    int p2a = IsPrime2A(v);
    int p2b = IsPrime2B(v);
    int p3a = IsPrime3A(v);
    int p4a = isprime1A(v);
    int p5a = isprime2A(v);
    int p6a = isprime3A(v);
    int p6b = isprime3B(v);
    int p7a = isprime4A(v);
    int p7b = isprime4B(v);
    int p8a = isprime5A(v);
    int p8b = isprime5B(v);
    int p9a = isprime6A(v);
    int p9b = isprime6B(v);
    if (p1a != p2a || p1a != p2b || p1a != p3a || p1a != p4a || p1a != p5a ||
        p1a != p6a || p1a != p6b || p1a != p7a || p1a != p7b || p1a != p8a ||
        p1a != p8b || p1a != p9a || p1a != p9b)
    {
        PROGRESS_REPORT(putchar('\n'));
        printf("!! FAIL !! %10u: IsPrime1A() %d; isPrime2A() %d; "
                "IsPrime2B() %d; IsPrime3A() %d; isprime1A() %d; "
                "isprime2A() %d; isprime3A() %d; isprime3B() %d; "
                "isprime4A() %d; isprime4B() %d; isprime5A() %d; "
                "isprime5B() %d; isprime6B() %d; isprime6B() %d\n",
                v,   p1a, p2a,
                p2b, p3a, p4a,
                p5a, p6a, p6b,
                p7a, p7b, p8a,
                p8b, p9a, p9b);
        return 1;
    }
    return 0;
}

#ifndef NO_PROGRESS_REPORTING
static volatile sig_atomic_t icounter = 0;
static void alarm_handler(int signum)
{
    assert(signum == SIGALRM);
    if (write(STDOUT_FILENO, ".", 1) != 1)
        exit(1);
    if (++icounter % 60 == 0)
    {
        if (write(STDOUT_FILENO, "\n", 1) != 1)
            exit(1);
    }
}

static void set_interval_timer(int interval)
{
    struct itimerval iv = { { .tv_sec = interval, .tv_usec = 0 },
                            { .tv_sec = interval, .tv_usec = 0 } };
    struct sigaction sa;
    (void)sigemptyset(&sa.sa_mask);     /* Putrescence! */
    sa.sa_handler = alarm_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, 0);
    setitimer(ITIMER_REAL, &iv, 0);
}
#endif

static void print_utc(void)
{
    time_t now = time(0);
    struct tm *utc = gmtime(&now);
    char buffer[32];
    strftime(buffer, sizeof(buffer), "Time: %Y-%m-%d %H:%M:%SZ", utc);
    printf("%s\n", buffer);
}

static void bake_off(int seed, int count)
{
    srand(seed);
    Clock clk;
    clk_init(&clk);
    printf("Seed: %d\n", seed);
    printf("Bake-off...warning this can take more than four minutes.\n");
    printf("        ...(60 dots per line, 1 dot per second, more or less).\n");
    print_utc();
    PROGRESS_REPORT(set_interval_timer(1));

    clk_start(&clk);

    int failures = 0;

    /* Check numbers to 1000 */
    for (unsigned v = 1; v < 1000; v++)
    {
        if (check_number(v))
            failures++;
    }

    /* Check random numbers */
    for (int i = 0; i < count; i++)
    {
        unsigned v = rand();
        if (check_number(v))
            failures++;
    }

    clk_stop(&clk);
    PROGRESS_REPORT(set_interval_timer(0));

    PROGRESS_REPORT(putchar('\n'));
    char buffer[32];
    (void)clk_elapsed_us(&clk, buffer, sizeof(buffer));
    if (failures == 0)
        printf("== PASS == %s s\n", buffer);
    else
        printf("!! FAIL !! %d failures in %s s\n", failures, buffer);
    print_utc();
}

enum { COUNT = 10000000 };

static void one_test(int seed, bool do_IsPrimeX)
{
    printf("Seed: %d\n", seed);
    assert(COUNT > 100000);
    if (do_IsPrimeX)
    {
        test_primality_tester("IsPrime0A", seed, IsPrime0A, COUNT / 100000);
        test_primality_tester("IsPrime1A", seed, IsPrime1A, COUNT);
        test_primality_tester("IsPrime1B", seed, IsPrime1B, COUNT);
        test_primality_tester("IsPrime2A", seed, IsPrime2A, COUNT);
        test_primality_tester("IsPrime2B", seed, IsPrime2B, COUNT);
        test_primality_tester("IsPrime3A", seed, IsPrime3A, COUNT);
    }
    test_primality_tester("isprime1A", seed, isprime1A, COUNT);
    test_primality_tester("isprime2A", seed, isprime2A, COUNT);
    test_primality_tester("isprime2B", seed, isprime2B, COUNT);
    test_primality_tester("isprime3A", seed, isprime3A, COUNT);
    test_primality_tester("isprime3B", seed, isprime3B, COUNT);
    test_primality_tester("isprime4A", seed, isprime4A, COUNT);
    test_primality_tester("isprime4B", seed, isprime4B, COUNT);
    test_primality_tester("isprime5A", seed, isprime5A, COUNT);
    test_primality_tester("isprime5B", seed, isprime5B, COUNT);
    test_primality_tester("isprime6A", seed, isprime6A, COUNT);
    test_primality_tester("isprime6B", seed, isprime6B, COUNT);
}

static const char optstr[] = "bhz";
static const char usestr[] = "[-bhz] [seed ...]";
static const char hlpstr[] =
    "  -b  Suppress the bake-off check\n"
    "  -h  Print this help message and exit\n"
    "  -z  Test speed of IsPrime0A..IsPrime3A too\n"
    ;

int main(int argc, char **argv)
{
    int opt;
    bool do_bake_off = true;
    bool do_IsPrimeX = false;

    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
            case 'b':
                do_bake_off = false;
                break;
            case 'h':
                err_help(usestr, hlpstr);
                /*NOTREACHED*/
            case 'z':
                do_IsPrimeX = true;
                break;
            default:
                err_usage(usestr);
                /*NOTREACHED*/
        }
    }

    int seed = time(0);
    if (do_bake_off)
    {
        bake_off(seed, COUNT);
    }

    if (optind != argc)
    {
        for (int i = optind; i < argc; i++)
            one_test(strtol(argv[i], NULL, 0), do_IsPrimeX);
    }
    else
        one_test(seed, do_IsPrimeX);

    return(0);
}

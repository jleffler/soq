/* SO 3442-6734 */
/*
** A zero indexed array A consisting of N different integers is given.
** The array contains all integers in the range [0.. N-1].  Sets S[K]
** for 0 <= K < N are defined as follows:
**
**     S[K] = {A[k], A[A[k]], A[A[A[k]]], …}
**
** The sets S[K] are finite for each k.
**
** The task is to write a function that, when given an array A
** consisting of N integers, returns the size of the largest set S[K]
** for this array.  The function should return 0 if input is empty;
**
**     A[0] = 5
**     A[1] = 4
**     A[2] = 0
**     A[3] = 3
**     A[4] = 1
**     A[5] = 6
**     A[6] = 2
**
** For this data, the function should return 4 because set S[2] equals
** {0,5,6,2} and has four elements.  No other set S[K] has more than
** four elements.  Assume elements in A are all distinct.  Each element
** of array A is an integer within the range [0..N-1].
*/

#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "stderr.h"

static int verbose = 0;
static int all = 0;

struct pair_int { int a; int b; };

/* sum(0..N) = n * (n - 1) / 2 */
static void chk_set_a(const int *a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        assert(a[i] >= 0 && a[i] < n);
        sum += a[i];
    }
    assert(sum == n * (n - 1) / 2);
}

static int size_of_set_k(const int *a, int n, int i)
{
    int len = 1;
    int k = a[i];
    assert(k >= 0 && k < n);
    while (a[k] != a[i])
    {
        len++;
        k = a[k];
        assert(k >= 0 && k < n);
    }
    return len;
}

static void print_cycle_a(const int *a, int n, int i)
{
    int k = a[i];
    assert(k >= 0 && k < n);
    printf("  Cycle = { %d", k);
    while (a[k] != a[i])
    {
        printf(", %d", a[k]);
        k = a[k];
        assert(k >= 0 && k < n);
    }
    printf(" }; length = %d\n", size_of_set_k(a, n, i));
}

static int found_before(const int *a, int n, int i)
{
    for (int x = 0; x < i; x++)
    {
        if (a[x] == i)
            return 1;
        int k = a[x];
        assert(k >= 0 && k < n);
        while (a[k] != x)
        {
            if (a[k] == i)
                return 1;
            k = a[k];
            assert(k >= 0 && k < n);
        }
    }
    return 0;
}

static struct pair_int max_size_of_set_k(const int *a, int n)
{
    int s_max = 0;
    int s_bgn = 0;
    chk_set_a(a, n);
    for (int i = 0; i < n && ((all && s_max != n) || s_max * 2 < n); i++)
    {
        if (verbose && !found_before(a, n, i))
            print_cycle_a(a, n, i);
        int n_max = size_of_set_k(a, n, i);
        if (n_max > s_max)
        {
            s_max = n_max;
            s_bgn = i;
        }
    }
    struct pair_int s = { s_max, s_bgn };
    return s;
}

static void print_set_a(const int *a, int n)
{
    printf("A[%d] = {", n);
    const char *pad = " ";
    for (int i = 0; i < n; i++)
    {
        printf("%s%d", pad, a[i]);
        pad = ", ";
    }
    puts(" }");
}

static void test_set_a(const int *a, int n)
{
    struct pair_int s;
    print_set_a(a, n);
    s = max_size_of_set_k(a, n);
    printf("  Max S[k] = %d beginning at %d\n", s.a, s.b);
    print_cycle_a(a, n, s.b);
}

/*
** Unbiassed value in the range [0..n), assuming an unbiassed
** random number generator of values in the range [0..RAND_MAX].
*/
static int rand_int(int n)
{
    assert(n > 0);
    int x = rand();
    while (x >= RAND_MAX - RAND_MAX % (n + 1))
        x = rand();
    return x % (n + 1);
}

/*
** Fisher-Yates shuffle: from Wikipedia
** https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
**
** To shuffle an array a of n elements (indices 0..n-1):
**   for i from n − 1 downto 1 do
**       j ← random integer such that 0 ≤ j ≤ i
**       exchange a[j] and a[i]
*/
static void fisher_yates_shuffle(int *a, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand_int(i);
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

static const char optstr[] = "ahH:L:r:s:v";
static const char usestr[] = "[-ahv][-s seed][-L low][-H high][-r repeats]";
static const char hlpstr[] =
    "  -a         Print all distinct cycles\n"
    "  -h         Print this help message and exit\n"
    "  -H hi      Longest array length (default 15)\n"
    "  -L lo      Shortest array length (default 5)\n"
    "  -r repeat  Number of times to shuffle each array (default 1)\n"
    "  -s seed    Use the given number as the random seed\n"
    "  -v         Verbose mode\n"
    ;

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    int seed = (int)time(0);
    int lo = 5;
    int hi = 15;
    int repeats = 1;
    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            all = 1;
            verbose = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'H':
            hi = atoi(optarg);
            if (hi < 1 || hi > 1000)
                err_error("High limit %s (%d) out of range [1..1000]\n", optarg, hi);
            break;
        case 'L':
            lo = atoi(optarg);
            if (lo < 1 || lo > 1000)
                err_error("Low limit %s (%d) out of range [1..1000]\n", optarg, lo);
            break;
        case 'r':
            repeats = atoi(optarg);
            if (repeats < 1 || repeats > 1000)
                err_error("Number of repeats %s (%d) out of range [1..1000]\n", optarg, repeats);
            break;
        case 's':
            seed = atoi(optarg);
            break;
        case 'v':
            verbose = 1;
            break;
        default:
            err_usage(usestr);
        }
    }

    if (optind != argc)
        err_usage(usestr);
    if (lo > hi)
        err_error("Low limit %d bigger than high limit %d\n", lo, hi);

    /* Base case from question */
    int A[] = { 5, 4, 0, 3, 1, 6, 2, };
    enum { A_SIZE = sizeof(A) / sizeof(A[0]) };
    test_set_a(A, A_SIZE);

    /* Random tests of different sizes */
    printf("Seed: %d\n", seed);
    srand(seed);
    for (int n = lo; n <= hi; n++)
    {
        for (int r = 0; r < repeats; r++)
        {
            int b[n];
            for (int i = 0; i < n; i++)
                b[i] = i;
            fisher_yates_shuffle(b, n);
            test_set_a(b, n);
        }
    }

    return 0;
}

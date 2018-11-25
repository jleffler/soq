/* SO 5308-6674 */
/* Inspired by the deleted SO question */
/* Determine the next prime after a given number */

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST
#ifdef TEST
static unsigned primes[] = { 2, 3, 5, 7, 11 };
#else
static unsigned primes[] =
{
       2,    3,    5,    7,   11,   13,   17,   19,   23,   29,
      31,   37,   41,   43,   47,   53,   59,   61,   67,   71,
      73,   79,   83,   89,   97,  101,  103,  107,  109,  113,
     127,  131,  137,  139,  149,  151,  157,  163,  167,  173,
     179,  181,  191,  193,  197,  199,  211,  223,  227,  229,
     233,  239,  241,  251,  257,  263,  269,  271,  277,  281,
     283,  293,  307,  311,  313,  317,  331,  337,  347,  349,
     353,  359,  367,  373,  379,  383,  389,  397,  401,  409,
     419,  421,  431,  433,  439,  443,  449,  457,  461,  463,
     467,  479,  487,  491,  499,  503,  509,  521,  523,  541,
     547,  557,  563,  569,  571,  577,  587,  593,  599,  601,
     607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
     661,  673,  677,  683,  691,  701,  709,  719,  727,  733,
     739,  743,  751,  757,  761,  769,  773,  787,  797,  809,
     811,  821,  823,  827,  829,  839,  853,  857,  859,  863,
     877,  881,  883,  887,  907,  911,  919,  929,  937,  941,
     947,  953,  967,  971,  977,  983,  991,  997, 1009, 1013,
};
#endif /* TEST */

enum { N_PRIMES = sizeof(primes) / sizeof(primes[0]) };

static bool is_prime(unsigned p)
{
    for (int i = 0; i < N_PRIMES; i++)
    {
        if (p % primes[i] == 0)
            return false;
    }
    for (unsigned t = primes[N_PRIMES - 1]; t * t <= p; t += 6)
    {
        if (p % t == 0)
            return false;
        if (p % (t + 2) == 0)
            return false;
    }
    return true;
}

static unsigned next_prime_after(unsigned start)
{
    for (int i = 0; i < N_PRIMES; i++)
    {
        if (start < primes[i])
            return primes[i];
    }
    for (unsigned x = (start + 1) / 6; x < UINT_MAX / 6; x++)
    {
        unsigned t = 6 * x - 1;
        if (t > start && is_prime(t))
            return(t);
        t += 2;
        if (t > start && is_prime(t))
            return(t);
    }
    return 0;
}

static inline int min(int x, int y) { return (x < y) ? x : y; }

static void print_prime_rhombus(int size)
{
    int np = 0;

    /* Width for size determined empirically */
    int width = 3;
    if (size < 9)
        width = 2;
    if (size > 17)
        width = 4;
    if (size > 49)
        width = 5;

    int vcount = 0;
    printf("size = %d\n", size);
    for (int i = 0; i < size; i++)
    {
        int n_size = min(i, size - i - 1);
        int n_fill = (size - 1) / 2 - n_size;
        int n_vals = 2 * n_size + 1;
        //printf("i = %d, n_vals = %d, n_fill = %d, n_size = %d\n",
        //       i, n_vals, n_fill, n_size);
        for (int j = 0; j < n_fill; j++)
            printf(" %*s", width, "");
        for (int j = 0; j < n_vals; j++)
        {
            np = next_prime_after(np);
            printf(" %*d", width, np);
            vcount++;
        }
        putchar('\n');
    }
    printf("%d primes printed\n", vcount);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int size = atoi(argv[i]);
            if (size <= 0 || size > 99 || size % 2 != 1)
            {
                fprintf(stderr, "%s: size %s is not an odd number between 1 and 99\n",
                        argv[0], argv[i]);
                return 1;
            }
            print_prime_rhombus(size);
        }
    }
    else
        print_prime_rhombus(7);
    return 0;
}


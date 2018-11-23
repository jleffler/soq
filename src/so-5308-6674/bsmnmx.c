#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

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

enum { N_PRIMES = sizeof(primes) / sizeof(primes[0]) };

/*
** Find largest value in array primes less than the value to be found.
*/
static int bs_lessthan(unsigned find)
{
    assert(find >= primes[0] && find < primes[N_PRIMES - 1]);
    /* Find x such that primes[x+0] < find && primes[x+1] >= find */
    int lo = 0;
    int hi = N_PRIMES - 1;
    while (lo <= hi)
    {
        //printf("F %d: lo:hi = %d:%d [%d:%d]  ", find, lo, hi, primes[lo], primes[hi]);
        int mid = (lo + hi) / 2;
        //printf("m = %d: [%d:%d]\n", mid, primes[mid], primes[mid+1]);
        if (primes[mid] < find && primes[mid + 1] >= find)
            return primes[mid];
        else if (primes[mid] >= find)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return -1;
}

/*
** Find smallest value in array primes more than the value to be found.
*/
static int bs_morethan(unsigned find)
{
    assert(find >= primes[0] && find < primes[N_PRIMES - 1]);
    /* Find x such that primes[x-1] <= find && primes[x+0] > find */
    int lo = 1;
    int hi = N_PRIMES - 1;
    while (lo <= hi)
    {
        //printf("F %d: lo:hi = %d:%d [%d:%d]  ", find, lo, hi, primes[lo], primes[hi]);
        int mid = (lo + hi) / 2;
        //printf("m = %d: [%d:%d]\n", mid, primes[mid], primes[mid+1]);
        if (primes[mid-1] <= find && primes[mid] > find)
            return primes[mid];
        else if (primes[mid] > find)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return -1;
}

int main(void)
{
    assert((primes[N_PRIMES-1]+1) % 6 == 0);
    for (unsigned curr = primes[0] + 1; curr < primes[N_PRIMES - 1]; curr++)
    {
        unsigned prev = bs_lessthan(curr);
        unsigned next = bs_morethan(curr);
        printf("%3u < %3u < %3u\n", prev, curr, next);
    }
    return 0;
}

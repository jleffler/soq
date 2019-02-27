/* SO 4545-9691 */
#include <stdio.h>

/* Find prime pairs */
/*
** All prime pairs after {3, 5} have the form 6N±1.
** Further, for those values of N = 5M±1 for M>0, one of the pair is a multiple of 5.
** Hence, you can look for interesting prime pairs for N = 1, 2, 3 (all prime pairs),
** and thence for M = 1 .. max and value 5M+0, 5M+2, 5M+3, and the smallest possible
** factor is 7.
*/

static int small_primes[] =
{
    /* primes 1000 | commalist -b '    ' -W 3 -n 10 */
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
     31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
     73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
    877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997,
};
enum { NUM_SMALL = sizeof(small_primes) / sizeof(small_primes[0]) };

/* By construction, the values in p are not multiples of 2, 3 or 5 */
static int check_small_prime(int p)
{
    for (int i = 3; i < NUM_SMALL; i++)
    {
        if (small_primes[i] * small_primes[i] > p)
            return 1;
        if (p % small_primes[i] == 0)
            return 0;
    }
    return 1;
}

static int check_prime_pair(int n)
{
    //const char *pp = "Not a prime pair";
    //if (check_small_prime(n-1) && check_small_prime(n+1))
    //    pp = "Prime pair";
    //printf("{ %d, %d } = %s\n", n-1, n+1, pp);
    int rc = 0;
    if (check_small_prime(n-1) && check_small_prime(n+1))
    {
        printf("%d %d\n", n-1, n+1);
        rc = 1;
    }
    return rc;
}

int main(void)
{
    int count = 0;
    /* Special cases */
    count += check_prime_pair(4);    /* prime pair { 3, 5 } - ultra-special case */
    count += check_prime_pair(6);    /* V = 6N, N = 1 */
    count += check_prime_pair(12);   /* V = 6N, N = 2 */
    count += check_prime_pair(18);   /* V = 6N, N = 3 */

    /* General cases */
    /*   333 - up to    10,000 =  205 prime pairs */
    /* 33333 - up to 1,000,000 = 8169 prime pairs */
    /* List of small primes is good for finding prime pairs up to 1,000,000 */
    for (int m = 1; m < 33333; m++)
    {
        count += check_prime_pair(6 * (5 * m + 0));
        count += check_prime_pair(6 * (5 * m + 2));
        count += check_prime_pair(6 * (5 * m + 3));
    }
    printf("%d prime pairs found\n", count);
    return 0;
}

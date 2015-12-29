/* https://projecteuler.net/problem=87 */
/*
** The smallest number expressible as the sum of a prime square, prime
** cube, and prime fourth power is 28.  In fact, there are exactly four
** numbers below fifty that can be expressed in such a way:
**
**      28 = 2^2 + 2^3 + 2^4
**      33 = 3^2 + 2^3 + 2^4
**      49 = 5^2 + 2^3 + 2^4
**      47 = 2^2 + 3^3 + 2^4
**
** How many numbers below fifty million can be expressed as the sum of a
** prime square, prime cube, and prime fourth power?
**
** NB: Some numbers can be expressed as different sums.  For example:
**
** 5501^2 +   241^3 +    17^4 = 44342043
** 2437^2 +   337^3 +    19^4 = 44342043
** 5189^2 +   241^3 +    43^4 = 44342043
** 2221^2 +   241^3 +    71^4 = 44342043
** 3877^2 +    97^3 +    73^4 = 44342043
*/

/* Rudimentary Sieve of Eratosthenes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

enum { MAX_PRIME = 8000 };  /* 8000 squared is 64M, so that's plenty big enough */
static char sieve[MAX_PRIME];
//enum { MAX_SUM = 50 };
//enum { MAX_SUM = 50000 };
enum { MAX_SUM = 50000000 };

int main(int argc, char **argv)
{
    int i;
    int max = MAX_PRIME;

    if (argc > 1)
        max = atoi(argv[1]);
    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %d\n", max);
    }
    if (max < 2)
        return 1;

    int sqrt_max = sqrt(max);
    sieve[0] = 1;
    sieve[1] = 1;
    //printf("2\n");
    for (i = 2 * 2; i <= max; i += 2)
        sieve[i] = 1;

    for (i = 3; i <= sqrt_max; i += 2)
    {
        if (sieve[i] == 0)
        {
            //printf("%d\n", i);
            for (int j = i + i; j <= max; j += i)
                sieve[j] = 1;
        }
    }

    int count = 0;
    for (int i4 = 2; i4 < max; i4++)
    {
        if (sieve[i4] == 1)
            continue;
        int p4 = i4 * i4 * i4 * i4;
        //printf("i4 = %d; p4 = %d\n", i4, p4);
        if (p4 > MAX_SUM)
            break;
        for (int i3 = 2; i3 < max; i3++)
        {
            if (sieve[i3] == 1)
                continue;
            int p3 = i3 * i3 * i3;
            //printf("i3 = %d; p3 = %d\n", i3, p3);
            //printf("p4 + p3 = %d\n", p4 + p3);
            if (p4 + p3 > MAX_SUM)
                break;
            for (int i2 = 2; i2 < max; i2++)
            {
                if (sieve[i2] == 1)
                    continue;
                int p2 = i2 * i2;
                //printf("i2 = %d; p2 = %d\n", i2, p2);
                //printf("p4 + p3 + p2 = %d\n", p4 + p3 + p2);
                if (p2 + p3 + p4 <= MAX_SUM)
                {
                    printf("%5d^2 + %5d^3 + %5d^4 = %d\n", i2, i3, i4, p2 + p3 + p4);
                    count++;
                }
                else
                    break;
            }
        }
    }
    printf("%d values\n", count);

    return 0;
}

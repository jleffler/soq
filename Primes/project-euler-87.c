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
** NB: Some numbers can be expressed as different sums.  For example,
**     145 is the smallest such number, 44342043 can be expressed
**     as 5 different sums, and 49998811 is the largest number smaller
**     than 50M that can be expressed as 2 or more different sums.
**
**    11^2 +     2^3 +     2^4 = 145
**     2^2 +     5^3 +     2^4 = 145
**
**  5501^2 +   241^3 +    17^4 = 44342043
**  2437^2 +   337^3 +    19^4 = 44342043
**  5189^2 +   241^3 +    43^4 = 44342043
**  2221^2 +   241^3 +    71^4 = 44342043
**  3877^2 +    97^3 +    73^4 = 44342043
**
**  7001^2 +    89^3 +    23^4 = 49998811
**  6007^2 +    41^3 +    61^4 = 49998811
**
** There are 1118424 unique numbers; 1139575 distinct sums
*/

/*
** Rudimentary Sieve of Eratosthenes.
**
** No space compression (records all even numbers; uses one byte per number).
** No time compression (after dealing with multiples of 2, steps through all
** odd numbers, rather than 6N±1).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <limits.h>

enum { MAX_PRIME = 8000 };  /* 8000 squared is 64M, plenty big enough for MAX_SUM of 50M */
static char sieve[MAX_PRIME];
//enum { MAX_SUM = 50 };
//enum { MAX_SUM = 50000 };
enum { MAX_SUM = 50000000 };

enum { NBITS = sizeof(uint64_t) * CHAR_BIT };  // Must be 64!
static uint64_t seen[MAX_SUM / NBITS];

static inline int is_bit_set(int bitnum)
{
    int index = bitnum / NBITS;
    int shift = bitnum % NBITS;
    return seen[index] & (UINT64_C(1) << shift);
}

static inline void set_bit(int bitnum)
{
    int index = bitnum / NBITS;
    int shift = bitnum % NBITS;
    seen[index] |= (UINT64_C(1) << shift);
}

int main(void)
{
    int max = MAX_PRIME;

    /* Generate prime numbers up to MAX_SUM */
    int sqrt_max = sqrt(max);
    sieve[0] = 1;
    sieve[1] = 1;
    //printf("2\n");
    for (int i = 2 * 2; i <= max; i += 2)
        sieve[i] = 1;

    for (int i = 3; i <= sqrt_max; i += 2)
    {
        if (sieve[i] == 0)
        {
            //printf("%d\n", i);
            for (int j = i + i; j <= max; j += i)
                sieve[j] = 1;
        }
    }

    int u_count = 0;
    int d_count = 0;
    for (int i4 = 2; i4 < max; i4++)
    {
        if (sieve[i4] == 1) /* Skip composites */
            continue;
        int p4 = i4 * i4 * i4 * i4;
        //printf("i4 = %d; p4 = %d\n", i4, p4);
        if (p4 >= MAX_SUM)
            break;
        for (int i3 = 2; i3 < max; i3++)
        {
            if (sieve[i3] == 1) /* Skip composites */
                continue;
            int p3 = i3 * i3 * i3;
            //printf("i3 = %d; p3 = %d\n", i3, p3);
            //printf("p4 + p3 = %d\n", p4 + p3);
            if (p4 + p3 >= MAX_SUM)
                break;
            for (int i2 = 2; i2 < max; i2++)
            {
                if (sieve[i2] == 1) /* Skip composites */
                    continue;
                int p2 = i2 * i2;
                //printf("i2 = %d; p2 = %d\n", i2, p2);
                //printf("p4 + p3 + p2 = %d\n", p4 + p3 + p2);
                int sum = p4 + p3 + p2;
                if (sum >= MAX_SUM)
                    break;
                const char *flag = " *";
                d_count++;
                if (!is_bit_set(sum))
                {
                    u_count++;
                    set_bit(sum);
                    flag = "";
                }
                printf("%5d^2 + %5d^3 + %5d^4 = %d%s\n", i2, i3, i4, sum, flag);
            }
        }
    }

    printf("%d unique numbers; %d distinct sums\n", u_count, d_count);

    return 0;
}

/* SO 19200574 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int numberDivisors(int n)
{
    int lim = (int)floor(sqrt((double)n));
    int *primes = (int *)calloc(n, sizeof(int));
    int *divisors = (int *)calloc(n, sizeof(int));
    int i, j, ctr;
    ctr = 0;

    if (primes && divisors)
    {
        printf("Processing %d\n", n);
        for (i = 0; i < n; i++)
        {
            primes[i] = 1;
            divisors[i] = 0;
        }

        for (i = 2; i < lim; i++)
        {
            if (primes[i])
            {
                for (j = i; i * j < n; j++)
                {
                    primes[i * j] = 0;
                }
            }
        }

        for (i = 2; i < n; i++)
        {
            if (primes[i])
            {
                if (n % i == 0)
                    divisors[i] = 1;
                for (j = i; j < n / i; j++)
                {
                    int result = n % (i * j);
                    if (result == 0)
                    {
                        //printf("n = %6d; i = %6d; j = %d\n", n, i, j);
                        divisors[i * j] = 1;
                    }
                }
            }
        }

        printf("  Divisor: %d\n", 1);
        for (i = 2; i < n; i++)
        {
            if (divisors[i])
            {
                printf("  Divisor: %d\n", i);
                ctr++;
            }
        }
        printf("  Divisor: %d\n", n);
        ctr += 2;   /* For 1 and n, of course */
    }
    else
    {
        fprintf(stderr, "Allocation failed.\n");
    }
    free(primes);
    free(divisors);
    return ctr;
}

int main(int argc, char * *argv)
{
    int min = 1;
    int max = 65535;
    if (argc == 2)
    {
        max = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        min = atoi(argv[1]);
        max = atoi(argv[2]);
    }
    else if (argc != 1)
    {
        fprintf(stderr, "Usage: %s [[min] max]\n", argv[0]);
        return 1;
    }
    printf("Range = %d:%d\n", min, max);
    for (int i = min; i <= max; i++)
    {
        int ctr = numberDivisors(i);
        printf("Number %6d has %3d divisors\n", i, ctr);
    }
    return 0;
}


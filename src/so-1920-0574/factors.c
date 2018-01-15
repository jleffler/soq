/* SO 1920-0574 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int *set_primes(int n)
{
    int *primes = (int *)calloc(n, sizeof(int));

    if (primes == 0)
    {
        fprintf(stderr, "Memory allocation failed (%zu bytes)\n", n * sizeof(int));
        exit(1);
    }

    for (int i = 0; i < n; i++)
        primes[i] = 1;

    int lim = (int)floor(sqrt((double)n));
    for (int i = 2; i < lim; i++)
    {
        if (primes[i])
        {
            for (int j = i; i *j < n; j++)
                primes[i * j] = 0;
        }
    }

    return primes;
}

static void list_divisors(int n, int *primes, int *divisors)
{
    int ctr = 0;

    for (int i = 0; i < n; i++)
        divisors[i] = 0;

    for (int i = 2; i <= n / 2; i++)
    {
        if (primes[i])
        {
            if (n % i == 0)
                divisors[i] = 1;
            for (int j = i; j < n / i; j++)
            {
                int result = n % (i * j);
                if (result == 0)
                {
                    // printf("n = %6d; i = %6d; j = %d\n", n, i, j);
                    divisors[i * j] = 1;
                }
            }
        }
    }

    printf("%d: 1", n);
    for (int i = 2; i <= n / 2; i++)
    {
        if (divisors[i])
        {
            printf(",%d", i);
            ctr++;
        }
    }
    ctr++;      // 1 is a factor
    if (n != 1)
    {
        ctr++;  // n is a factor
        printf(",%d", n);
    }
    printf(" (%d factors)\n", ctr);
}

int main(int argc, char **argv)
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
    if (min <= 0 || max <= 0 || min > max)
    {
        fprintf(stderr, "Arguments must be positive and"
                " min must not be greater than max\n");
        exit(1);
    }
    printf("Range = %d:%d\n", min, max);

    int *primes = set_primes(max);
    int *divisors = (int *)calloc(max, sizeof(int));

    if (divisors == 0)
    {
        fprintf(stderr, "Memory allocation failed (%zu bytes)\n", max * sizeof(int));
        exit(1);
    }

    for (int i = min; i <= max; i++)
        list_divisors(i, primes, divisors);

    free(primes);
    free(divisors);
    return 0;
}

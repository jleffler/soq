#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Primes less than 100 */
static int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
enum { NPRIMES = sizeof(primes) / sizeof(primes[0]) };

typedef int Factors[NPRIMES];

typedef struct Powers
{
    Factors factors;    /* Array of exponents of primes */
    int max_factor;     /* Index of largest non-zero factor */
} Powers;

static inline void print_powers(const Powers *powers)
{
    for (int i = 0; i <= powers->max_factor; i++)
    {
        if (powers->factors[i] == 1)
            printf("(%d)", primes[i]);
        else if (powers->factors[i] > 1)
            printf("(%d^%d)", primes[i], powers->factors[i]);
    }
    putchar('\n');
}

static void prime_factorization(int value, Powers *powers)
{
    //printf("%s(): %d\n", __func__, value);
    //printf("%s(): %d = ", __func__, value);
    for (int i = 0; i < NPRIMES && value > 1; i++)
    {
        while (value > 1 && value % primes[i] == 0)
        {
            //printf("%s(): value = %d, prime = %d, residual = %d\n", __func__, value, primes[i], value / primes[i]);
            powers->factors[i]++;
            value /= primes[i];
            powers->max_factor = i;
        }
    }
    assert(value == 1);
    //print_powers(powers);
}

static bool eq_powers(const Powers *p1, const Powers *p2)
{
    if (p1->max_factor != p2->max_factor)
        return false;
    for (int i = 0; i <= p1->max_factor; i++)
    {
        if (p1->factors[i] != p2->factors[i])
            return false;
    }
    return true;
}

static bool find_value(const Powers *value, int num_powers, const Powers *powers)
{
    //printf("%s(): find ", __func__);
    //print_powers(value);
    for (int i = 0; i < num_powers; i++)
    {
        //printf("%s(): cmp  ", __func__);
        //print_powers(&powers[i]);
        if (eq_powers(value, &powers[i]))
        {
            //printf("%s(): found\n", __func__);
            return true;
        }
    }
    //printf("%s(): not found\n", __func__);
    return false;
}

int main(void)
{
    int num_powers = 0;
    int max_powers = 0;
    Powers *powers = NULL;
    const int upper_bound = 100;

    for (int a = 2; a <= upper_bound; a++)
    {
        Powers base = { { 0 }, 0 };
        prime_factorization(a, &base);
        //printf("%d = ", a);
        //print_powers(&base);
        //fflush(0);
        for (int b = 2; b <= upper_bound; b++)
        {
            Powers value = base;
            for (int i = 0; i <= base.max_factor; i++)
                value.factors[i] *= b;
            if (!find_value(&value, num_powers, powers))
            {
                assert(num_powers <= max_powers);
                if (num_powers == max_powers)
                {
                    int new_max = max_powers * 2 + 2;
                    Powers *new_powers = realloc(powers, new_max * sizeof(powers[0]));
                    if (new_powers == NULL)
                    {
                        fprintf(stderr, "realloc failed on size %d * %zu = %zu\n", new_max, sizeof(powers[0]), new_max * sizeof(powers[0]));
                        exit(EXIT_FAILURE);
                    }
                    powers = new_powers;
                    max_powers = new_max;
                }
                powers[num_powers++] = value;
            }
        }
    }

    //for (int i = 0; i < num_powers; i++)
        //print_powers(&powers[i]);
    printf("%d\n", num_powers);
    free(powers);

    return 0;
}


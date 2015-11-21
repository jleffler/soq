/* SO 33838621: Minimal Primes */
/*
** Find the minimal primes less than 100,000.
**
** A minimal prime is a prime number for which no subsequence of the digits
** that make up the number is itself prime.
** The question gives two examples:
** = 881 is a minimal prime because none of { 8, 8, 1, 88, 81, 81 } are prime.
** = 109 is not a minimal prime because { 1, 0, 9, 10, 9, 19 } includes the prime 19.
** Clearly, the single digit primes are all trivially minimal.
**
** Additional wrinkle: the code may not build up a table of primes.
*/

/*
** There are two problems to solve:
** (1) Check for primality without using a table of primes.
** (2) Generate all subsequences of a number.
** The latter is modestly novel.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_prime(int n)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3 || n == 5 || n == 7)
        return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0)
        return false;
    for (int c = 12; (c - 1) * (c - 1) <= n; c += 6)
    {
        if (n % (c - 1) == 0 || n % (c + 1) == 0)
            return false;
    }
    return true;
}

static bool has_prime_1_digit_subset(const char *buffer, int n_digits)
{
    /* Single digits - 2, 3, 5, 7 prevent a number being a minimal prime */
    for (int i = 0; i < n_digits - 0; i++)
    {
        int p1 = buffer[i] - '0';
        //printf("C %d\n", p1);
        if (is_prime(p1))
            return true;
    }
    return false;
}

static bool has_prime_2_digit_subset(const char *buffer, int n_digits)
{
    /* Two digit subsequences */
    for (int i = 0; i < n_digits - 1; i++)
    {
        int p1 = buffer[i] - '0';
        for (int j = 0; j < n_digits - 0; j++)
        {
            int p2 = p1 * 10 + buffer[j] - '0';
            //printf("C %d\n", p2);
            if (is_prime(p2))
                return true;
        }
    }
    return false;
}

static bool has_prime_3_digit_subset(const char *buffer, int n_digits)
{
    /* Three digit subsequences */
    for (int i = 0; i < n_digits - 2; i++)
    {
        int p1 = buffer[i] - '0';
        for (int j = 0; j < n_digits - 1; j++)
        {
            int p2 = p1 * 10 + buffer[j] - '0';
            for (int k = 0; k < n_digits - 0; k++)
            {
                int p3 = p2 * 10 + buffer[k] - '0';
                //printf("C %d\n", p3);
                if (is_prime(p3))
                    return true;
            }
        }
    }
    return false;
}

static bool has_prime_4_digit_subset(const char *buffer, int n_digits)
{
    /* Four digit subsequences */
    for (int i = 0; i < n_digits - 3; i++)
    {
        int p1 = buffer[i] - '0';
        for (int j = 0; j < n_digits - 2; j++)
        {
            int p2 = p1 * 10 + buffer[j] - '0';
            for (int k = 0; k < n_digits - 1; k++)
            {
                int p3 = p2 * 10 + buffer[k] - '0';
                for (int l = 0; l < n_digits - 0; l++)
                {
                    int p4 = p3 * 10 + buffer[l] - '0';
                    //printf("C %d\n", p4);
                    if (is_prime(p4))
                        return true;
                }
            }
        }
    }
    return false;
}

static bool has_prime_5_digit_subset(const char *buffer, int n_digits)
{
    /* Five digit subsequences */
    for (int i = 0; i < n_digits - 4; i++)
    {
        int p1 = buffer[i] - '0';
        for (int j = 0; j < n_digits - 3; j++)
        {
            int p2 = p1 * 10 + buffer[j] - '0';
            for (int k = 0; k < n_digits - 2; k++)
            {
                int p3 = p2 * 10 + buffer[k] - '0';
                for (int l = 0; l < n_digits - 1; l++)
                {
                    int p4 = p3 * 10 + buffer[k] - '0';
                    for (int m = 0; m < n_digits - 0; m++)
                    {
                        int p5 = p4 * 10 + buffer[l] - '0';
                        //printf("C %d\n", p5);
                        if (is_prime(p5))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

static void check_minimal_prime(int n)
{
    assert(n < 1000000);
    if (is_prime(n))
    {
        //printf("P %d\n", n);
        char buffer[sizeof("999999")];
        sprintf(buffer, "%d", n);
        char n_digits = strlen(buffer);

        if (n_digits > 1 && has_prime_1_digit_subset(buffer, n_digits))
            return;
        if (n_digits > 2 && has_prime_2_digit_subset(buffer, n_digits))
            return;
        if (n_digits > 3 && has_prime_3_digit_subset(buffer, n_digits))
            return;
        if (n_digits > 4 && has_prime_4_digit_subset(buffer, n_digits))
            return;
        if (n_digits > 5 && has_prime_5_digit_subset(buffer, n_digits))
            return;

        printf("== M == %d\n", n);  /* It's a minimal prime */
    }
}

int main(void)
{
    int max = 1000000 / 6;
    check_minimal_prime(2);
    check_minimal_prime(3);
    for (int c = 1; c < max; c++)
    {
        check_minimal_prime(6 * c - 1);
        check_minimal_prime(6 * c + 1);
    }
    return 0;
}

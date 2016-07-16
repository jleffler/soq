/* SO 33838621: Minimal Primes */
/*
** Find the minimal primes less than 100,000.
**
** A minimal prime is a prime number for which no subsequence of the digits
** that make up the number is itself prime.
** The question gives two examples:
** = 881 is prime and is a minimal prime because none of { 8, 8, 1, 88,
**       81, 81 } are prime.
** = 109 is prime but is not a minimal prime because { 1, 0, 9, 10, 9,
**       19 } includes the prime 19.
** Clearly, the single digit primes are all trivially minimal.
**
** Additional wrinkle: the code may not build up a table of primes.
**
** NB: All primes except 2 and 3 have the form 6N±1
*/

/*
** There are two problems to solve:
** (1) Check for primality without using a table of primes.
** (2) Generate all subsequences of a number.
** The latter problem is somewhat harder than the former.
** The surviving solution uses recursive string manipulation.
**
** NB: Command subsequences is derived from this, and helps check
**     the validity of the minimal primes.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

static bool has_prime_n_digit_subset(int p0, int n_digits, const char *buffer, int buflen)
{
    //printf("-->> p0 = %5d, n = %d (%s)\n", p0, n_digits, buffer);
    assert(buflen >= 0 && strlen(buffer) == (size_t)buflen);
    for (int i = 0; i < buflen; i++)
    {
        int p1 = 10 * p0 + buffer[i] - '0';
        if (n_digits > 1)
        {
            if (has_prime_n_digit_subset(p1, n_digits - 1, &buffer[i+1], buflen - i - 1))
            {
                //printf("<<-- true\n");
                return true;
            }
        }
        else
        {
            //printf("C %d\n", p1);
            if (is_prime(p1))
            {
                //printf("<<-- p1 = %d: true\n", p1);
                return true;
            }
        }
    }
    //printf("<<-- false\n");
    return false;
}

static void check_minimal_prime(int n)
{
    assert(n > 0);
    if (is_prime(n))
    {
        //printf("P %d\n", n);
        char buffer[20];
        sprintf(buffer, "%d", n);
        char n_digits = strlen(buffer);
        for (int i = 1; i < n_digits; i++)
        {
            if (has_prime_n_digit_subset(0, i, buffer, n_digits))
                return;
        }

        printf("%d\n", n);              /* It's a minimal prime */
    }
}

int main(int argc, char **argv)
{
    int max = 100000;
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [maximum]\n", argv[0]);
        exit(1);
    }
    else if (argc == 2)
    {
        max = atoi(argv[1]);
        if (max <= 0)
        {
            fprintf(stderr, "Invalid number (%d from %s)\n", max, argv[1]);
            exit(1);
        }
    }

    max /= 6;
    check_minimal_prime(2);
    check_minimal_prime(3);
    for (int c = 1; c < max; c++)
    {
        check_minimal_prime(6 * c - 1);
        check_minimal_prime(6 * c + 1);
    }

    return 0;
}

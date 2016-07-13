/* SO 33838621: Minimal Primes */
/*
** Author: unknown - the original formatting was not mine, but neither
** SO nor Git provides any clues.
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_prime(const int candidate)
{
    if (candidate <= 1)
        return false;

    if (candidate <= 3)
        return true;

    if (candidate % 2 == 0 || candidate % 3 == 0)
        return false;

    for (int64_t factor = 5; factor *factor <= candidate; factor += 6)
    {
        if (candidate % factor == 0 || candidate % (factor + 2) == 0)
            return false;
    }

    return true;
}

static int ipow(const int base, const int num)
{
    if (num == 0)
        return 1;

    int ret = base;

    for (int i = 1; i < num; i++)
    {
        ret *= base;
    }

    return ret;
}

static int extract_digit(const int num, const int digit)
{
    int factor = ipow(10, digit);
    int left  = num / (factor * 10);
    int right = num % factor;

    return (left * factor) + right;
}

static bool subsequence_find(const int num, bool (*checker)(int))
{
    for (int i = 0; ipow(10, i) <= num; i++)
    {
        int subsequence = extract_digit(num, i);

        if ( (*checker)(subsequence) )
            return true;

        if (subsequence_find(subsequence, checker) )
            return true;
    }

    return false;
}

static bool is_minimal_prime(const int candidate)
{
    if (!is_prime(candidate) )
        return false;

    return !subsequence_find(candidate, &is_prime);
}

int main(const int argc, const char *argv[])
{
    int upto = 1000000;

    if (argc >= 2)
    {
        upto = atoi(argv[1]);
    }

    for (int i = 0; i < upto; i++)
    {
        if (is_minimal_prime(i) )
        {
            printf("%d is minimal\n", i);
        }
    }

    return true;
}

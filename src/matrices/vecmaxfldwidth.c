/*
** Determine the maximum field width needed to print vector of N integers
*/

/*
** NB: Working out an appropriate size for floating-point values is a
** lot harder.  All else apart, you need to decide how many significant
** figure should be retained, and whether the format should be
** fixed-point or exponential notation.  And a small magnitude number
** (1.23456789E-123) might require more space than a large magnitude
** number (1234.0).
*/

/* Would be declared in a header */
#ifndef MAXFLDWIDTH_C_INCLUDED
#define MAXFLDWIDTH_C_INCLUDED

#include <stddef.h>     /* size_t */

extern int max_field_width(size_t n, const int vector[n]);

#endif /* MAXFLDWIDTH_C_INCLUDED */

#include <stdio.h>
#include <assert.h>

/*
** On two's complement machines, any positive number can be negated, but
** INT_MIN cannot be negated without overflow.
*/
static inline int num_digits(int value)
{
    int result = 1;     /* Acount for the sign of negative numbers */
    if (value > 0)
    {
        result = 0;     /* Positive numbers don't have a sign */
        value = -value;
    }
    do
    {
        result++;
    } while ((value /= 10) != 0);
    return result;
}

int max_field_width(size_t n, const int vector[n])
{
    int min_val = vector[0];
    int max_val = vector[0];
    for (size_t i = 0; i < n; i++)
    {
        if (vector[i] < min_val)
            min_val = vector[i];
        if (vector[i] > max_val)
            max_val = vector[i];
    }
    int fld_width = num_digits(max_val);
    if (min_val < 0)
    {
        int min_width = num_digits(min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
    return fld_width;
}


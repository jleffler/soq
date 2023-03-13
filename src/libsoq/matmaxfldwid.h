/*
@(#)File:           matmaxfldwid.h
@(#)Purpose:        Determine the maximum field width of values in NxM matrix of integers
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Derivation:     matmaxfldwid.h 1.3 2022/08/15 20:24:56
*/

/*TABSTOP=4*/

/*
** Define macro MFW_MATRIX_TYPE for the type of the matrix (the default
** type is int).  Call function max_field_width() with the number of
** elements in the matrix and the matrix address.  You will probably
** never explicitly call mfw_num_digits().
**
** Life is more complex if you need to handle different types in a
** single source file.
**
** NB: Working out an appropriate size for floating-point values is a
** lot harder.  All else apart, you need to decide how many significant
** figure should be retained, and whether the format should be
** fixed-point or exponential notation.  And a small magnitude number
** (1.23456789E-123) might require more space than a large magnitude
** number (1234.0).
**
** Configuration:
** #define MFW_CONST const to const-qualify matrices.
** -- See also: SO 7335-6925 (https://stackoverflow.com/q/73356925).
** #define MFW_UNSIGNED if the type is an unsigned type
*/

#ifndef JLSS_ID_MATMAXFLDWID_H
#define JLSS_ID_MATMAXFLDWID_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MFW_MATRIX_TYPE)
#define MFW_MATRIX_TYPE int
#endif

#if !defined(MFW_CONST)
#define MFW_CONST /* Nothing */
#endif

#define MFW_CONCAT3(a, b, c)        a ## b ## c
#define MFW_CONCAT2(a, b)           a ## b
#define MFW_MAX_FIELD_WIDTH(type)   MFW_CONCAT3(matrix_, type, _max_field_width)
#define MFW_NUM_DIGITS(type)        MFW_CONCAT2(mfw_num_digits_, type)

#include <stddef.h>     /* size_t */

#ifndef max_field_width
#define max_field_width MFW_MAX_FIELD_WIDTH(MFW_MATRIX_TYPE)
#endif /* max_field_width */
#ifndef mfw_num_digits
#define mfw_num_digits MFW_NUM_DIGITS(MFW_MATRIX_TYPE)
#endif /* mfw_num_digits */

/*
** On two's complement machines, any positive integer of a given type
** can be negated, but the minimum negative integer cannot be negated
** without overflow.
*/
static inline int MFW_NUM_DIGITS(MFW_MATRIX_TYPE)(MFW_MATRIX_TYPE value)
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

static inline int MFW_MAX_FIELD_WIDTH(MFW_MATRIX_TYPE)(size_t n, size_t m, MFW_CONST MFW_MATRIX_TYPE matrix[n][m])
{
    MFW_MATRIX_TYPE min_val = matrix[0][0];
    MFW_MATRIX_TYPE max_val = matrix[0][0];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (matrix[i][j] < min_val)
                min_val = matrix[i][j];
            if (matrix[i][j] > max_val)
                max_val = matrix[i][j];
        }
    }
    int fld_width = MFW_NUM_DIGITS(MFW_MATRIX_TYPE)(max_val);
#if !defined(MFW_UNSIGNED)
    if (min_val < 0)
    {
        int min_width = MFW_NUM_DIGITS(MFW_MATRIX_TYPE)(min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
#endif /* MFW_UNSIGNED */
    return fld_width;
}

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_MATMAXFLDWID_H */

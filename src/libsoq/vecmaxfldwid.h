/*
@(#)File:           vecmaxfldwid.h
@(#)Purpose:        Determine the maximum field width of values in vector of N integers
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Derivation:     vecmaxfldwid.h 1.1 2022/06/25 20:02:29
*/

/*TABSTOP=4*/

/*
** Define macro MFW_VECTOR_TYPE for the type of the vector (the default
** type is int).  Call function max_field_width() with the number of
** elements in the vector and the vector address.  You will probably
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
*/

#ifndef JLSS_ID_VECMAXFLDWID_H
#define JLSS_ID_VECMAXFLDWID_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MFW_VECTOR_TYPE)
#define MFW_VECTOR_TYPE int
#endif

#define MFW_CONCAT3(a, b, c)        a ## b ## c
#define MFW_CONCAT2(a, b)           a ## b
#define MFW_MAX_FIELD_WIDTH(type)   MFW_CONCAT3(vector_, type, _max_field_width)
#define MFW_NUM_DIGITS(type)        MFW_CONCAT2(mfw_num_digits_, type)

#include <stddef.h>     /* size_t */

#ifndef max_field_width
#define max_field_width MFW_MAX_FIELD_WIDTH(MFW_VECTOR_TYPE)
#endif /* max_field_width */
#ifndef mfw_num_digits
#define mfw_num_digits MFW_NUM_DIGITS(MFW_VECTOR_TYPE)
#endif /* mfw_num_digits */

/*
** On two's complement machines, any positive integer of a given type
** can be negated, but the minimum negative integer cannot be negated
** without overflow.
*/
static inline int MFW_NUM_DIGITS(MFW_VECTOR_TYPE)(MFW_VECTOR_TYPE value)
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

static inline int MFW_MAX_FIELD_WIDTH(MFW_VECTOR_TYPE)(size_t n, const MFW_VECTOR_TYPE vector[n])
{
    MFW_VECTOR_TYPE min_val = vector[0];
    MFW_VECTOR_TYPE max_val = vector[0];
    for (size_t i = 0; i < n; i++)
    {
        if (vector[i] < min_val)
            min_val = vector[i];
        if (vector[i] > max_val)
            max_val = vector[i];
    }
    int fld_width = MFW_NUM_DIGITS(MFW_VECTOR_TYPE)(max_val);
    if (min_val < 0)
    {
        int min_width = MFW_NUM_DIGITS(MFW_VECTOR_TYPE)(min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
    return fld_width;
}

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_VECMAXFLDWID_H */

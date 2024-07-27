/*
@(#)File:           gcd.h
@(#)Purpose:        GCD - Greatest Common Denominator
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005-2024
@(#)Derivation:     gcd.h 1.6 2024/02/08 05:19:55
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_GCD_H
#define JLSS_ID_GCD_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
** Generic GCD function macros - pick the
**  - the function storage class (static or extern),
**  - the type (e.g. uintptr_t, intmax_t, ...),
**  - the function name (e.g. gcd_ptr, gcd_max)
** and create declarations and definitions of the function.
**
** DECLARE_GCD_FUNCTION(extern, uintptr_t, gcd_ptr);
** DEFINE_GCD_FUNCTION(extern, uintptr_t, gcd_ptr)          // no trailing semicolon!
** DEFINE_GCD_FUNCTION(static, uintptr_t, gcd_ptr)          // no trailing semicolon!
** DEFINE_GCD_FUNCTION(static inline, intmax_t, gcd_max)    // no trailing semicolon!
**
** (A trailing semicolon creates an empty declaration after the
** function; it isn't the end of the world, but it isn't right.)
**
** A recursive GCD function looks like:
**      int gcd_recursive(int x, int y)
**      {
**          if (y == 0)
**              return x;
**          return gcd_recursive(y, x % y);
**      }
** There is no good reason to use recursion; the iterative
** solution is more sensible.
*/

#define DECLARE_GCD_FUNCTION(storage_class, type, name) \
    storage_class type name(type x, type y)

#define DEFINE_GCD_FUNCTION(storage_class, type, name) \
    storage_class type name(type x, type y) \
    { \
        if (x <= 0 || y <= 0) \
            return(0); \
        type r; \
        while ((r = x % y) != 0) \
        { \
            x = y; \
            y = r; \
        } \
        return(y); \
    }

DECLARE_GCD_FUNCTION(extern, int, gcd);
DECLARE_GCD_FUNCTION(extern, unsigned long long, gcd_ull);

#ifdef  __cplusplus
}
#endif

#endif /* JLSS_ID_GCD_H */

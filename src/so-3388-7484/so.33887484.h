#ifndef SO_33887484_H_INCLUDED
#define SO_33887484_H_INCLUDED

#include <stddef.h>     // size_t

typedef struct Fraction
{
    int     numer;
    int     denom;
} Fraction;

extern void ri_add(const Fraction *lhs, const Fraction *rhs, Fraction *res);
extern void ri_sub(const Fraction *lhs, const Fraction *rhs, Fraction *res);
extern void ri_mul(const Fraction *lhs, const Fraction *rhs, Fraction *res);
extern void ri_div(const Fraction *lhs, const Fraction *rhs, Fraction *res);
extern void ri_mod(const Fraction *lhs, const Fraction *rhs, Fraction *res);

/*
** All values returned by the functions are already normalized, so
** ri_gcd() returns 1 for any value not created by the user, and
** ri_normalize() does nothing to any value not created by the user.
** If the user manually, explicitly initializes an improper
** Fraction, then these may do something more interesting.
*/
extern int  ri_gcd(const Fraction *val);    /* Exercise in futility */
extern void ri_normalize(Fraction *val);    /* Exercise in futility */

extern char *ri_fmt(Fraction val, char *buffer, size_t buflen);
extern char *ri_fmtproper(Fraction val, char *buffer, size_t buflen);
extern int   ri_scn(const char *str, const char **eor, Fraction *result);

#endif /* SO_33887484_H_INCLUDED */

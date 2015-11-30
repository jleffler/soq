#ifndef SO_33887484_H_INCLUDED
#define SO_33887484_H_INCLUDED

#include <stddef.h>     // size_t

typedef struct RationalInt
{
    int     numerator;
    int     denominator;
} RationalInt;

extern RationalInt ri_new(int numerator, int denominator);

extern void ri_add(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res);
extern void ri_sub(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res);
extern void ri_mul(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res);
extern void ri_div(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res);
extern void ri_mod(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res);

/*
** All values returned by the functions are already normalized, so
** ri_gcd() returns 1 for any value not created by the user, and
** ri_normalize() does nothing to any value not created by the user.
** If the user manually, explicitly initializes a RationalInt, then
** these may report something more interesting.
*/
extern int ri_gcd(const RationalInt *val);      /* Exercise in futility */
extern void ri_normalize(RationalInt *val);     /* Exercise in futility */

extern void ri_integer(const RationalInt *val, RationalInt *res);         // Integer part
extern void ri_fraction(const RationalInt *val, RationalInt *res);        // Fractional part

extern char *ri_fmt(RationalInt val, char *buffer, size_t buflen);
extern char *ri_fmtproper(RationalInt val, char *buffer, size_t buflen);
extern int ri_scn(const char *str, char **eor, RationalInt *result);

#endif /* SO_33887484_H_INCLUDED */

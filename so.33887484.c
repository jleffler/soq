/* SO 33887484 */
/*
** Storage rules:
** 1. Denominator is never zero.
** 2. Denominator stores the sign and is not INT_MIN (2's complement assumed).
** 3. Numerator is never negative.
** 4. gcd(numerator, denominator) == 1 unless numerator == 0.
*/

/* The code is not reliable if assertions are disabled. */
/* At least it reliably crashes if they are enabled. */
#undef NDEBUG

#include "so.33887484.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ENOERROR
#define ENOERROR 0
#endif

/* -- Generic Functions -- */

static inline int iabs(int x) { return (x < 0) ? -x : x; }  /* Or abs() from <stdlib.h> */
static inline int signum(int x) { return (x > 0) ? +1 : (x < 0) ? -1 : 0; }

static int gcd(int x, int y)
{
    int r;

    if (x == 0 || y == 0)
        return(0);

    while ((r = x % y) != 0)
    {
        x = y;
        y = r;
    }
    return(y);
}

static long long gcd_ll(long long x, long long y)
{
    long long r;

    if (x == 0 || y == 0)
        return(0);

    while ((r = x % y) != 0)
    {
        x = y;
        y = r;
    }
    return(y);
}

static int strtoi(const char *data, const char **endptr, int base)
{
    char *end;
    int old_errno = errno;
    errno = 0;
    long lval = strtol(data, &end, base);
    if (endptr != 0)
        *endptr = end;
    if (lval > INT_MAX)
    {
        errno = ERANGE;
        lval = INT_MAX;
    }
    else if (lval < INT_MIN)
    {
        errno = ERANGE;
        lval = INT_MIN;
    }
    if (errno == 0)
        errno = old_errno;
    return (int)lval;
}

static bool chk_strtoi(const char *data, const char **eon, int base, int *result)
{
    const char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoi(data, &end, base);
    if (end == data || (errno == ERANGE && (*result == INT_MIN || *result == INT_MAX)))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

/* -- RationalInt Functions -- */

static void ri_chk(RationalInt val)
{
    assert(val.denominator != 0 && val.denominator != INT_MIN);
    assert(val.numerator >= 0);
    assert(val.numerator == 0 || gcd(iabs(val.numerator), iabs(val.denominator)) == 1);
}

/* Unimportant - because all functions already normalize RationalInt values, so GCD = 1 */
int ri_gcd(const RationalInt *val)
{
    assert(val->denominator != 0 && val->denominator != INT_MIN);
    return gcd(iabs(val->numerator), iabs(val->denominator));
}

static RationalInt ri_new(int numerator, int denominator)
{
    assert(denominator != 0 && denominator != INT_MIN);
    RationalInt ri;
    if (numerator == 0)
    {
        ri.numerator = 0;
        ri.denominator = 1;
    }
    else
    {
        int sign = signum(numerator) * signum(denominator);
        assert(sign == +1 || sign == -1);
        int dv = gcd(iabs(numerator), iabs(denominator));
        assert(dv != 0);
        ri.numerator = iabs(numerator) / dv;
        ri.denominator = sign * iabs(denominator) / dv;
    }
    return ri;
}

/* Unimportant - because all functions already normalize RationalInt values */
void ri_normalize(RationalInt *val)
{
    *val = ri_new(val->numerator, val->denominator);
}

void ri_add(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res)
{
    long long rn = (long long)lhs->numerator * rhs->denominator +
                   (long long)rhs->numerator * lhs->denominator;
    if (rn == 0)
        *res = ri_new(0, 1);
    else
    {
        long long rd = (long long)lhs->denominator * rhs->denominator;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_sub(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res)
{
    long long rn = (long long)lhs->numerator * rhs->denominator -
                   (long long)rhs->numerator * lhs->denominator;
    if (rn == 0)
        *res = ri_new(0, 1);
    else
    {
        long long rd = (long long)lhs->denominator * rhs->denominator;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_mul(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res)
{
    long long rn = (long long)lhs->numerator * rhs->numerator;
    if (rn == 0)
    {
        *res = ri_new(0, 1);
    }
    else
    {
        long long rd = (long long)lhs->denominator * rhs->denominator;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_div(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res)
{
    assert(rhs->numerator != 0);
    if (lhs->numerator == 0)     // Zero divided by anything is zero
        *res = ri_new(0, 1);
    else
    {
        long long rn = (long long)lhs->numerator * rhs->denominator;
        long long rd = (long long)lhs->denominator * rhs->numerator;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

static void ri_integer(const RationalInt *val, RationalInt *res)
{
    *res = ri_new(val->numerator / val->denominator, 1);
}

static void ri_fraction(const RationalInt *val, RationalInt *res)
{
    *res = ri_new(val->numerator % val->denominator, val->denominator);
}

void ri_mod(const RationalInt *lhs, const RationalInt *rhs, RationalInt *res)
{
    assert(rhs->numerator != 0);
    RationalInt rd;
    ri_div(lhs, rhs, &rd);
    RationalInt ri;
    ri_integer(&rd, &ri);
    RationalInt rm;
    ri_mul(&ri, rhs, &rm);
    ri_sub(lhs, &rm, res);
}

/* -- Format functions -- */

char *ri_fmt(RationalInt val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    if (buflen > 0 && buffer != 0)
    {
        char sign = (val.denominator < 0) ? '-' : '+';
        int len;
        if (iabs(val.denominator) == 1)
            len = snprintf(buffer, buflen, "[%c%d]", sign, val.numerator);
        else
            len = snprintf(buffer, buflen, "[%c%d/%d]",
                           sign, iabs(val.numerator), iabs(val.denominator));
        if (len <= 0 || (size_t)len >= buflen)
            *buffer = '\0';
    }
    return buffer;
}

char *ri_fmtproper(RationalInt val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    RationalInt in;
    ri_integer(&val, &in);
    RationalInt fr;
    ri_fraction(&val, &fr);
    char sign = (val.denominator < 0) ? '-' : '+';
    int len;
    assert(in.denominator == +1 || in.denominator == -1);
    if (in.numerator != 0 && fr.numerator != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d %d/%d]", sign,
                       iabs(in.numerator), iabs(fr.numerator), iabs(fr.denominator));
    }
    else if (in.numerator != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d]", sign, iabs(in.numerator));
    }
    else if (fr.numerator != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d/%d]",
                       sign, iabs(val.numerator), iabs(val.denominator));
    }
    else
    {
        len = snprintf(buffer, buflen, "[0]");
    }
    if (len <= 0 || (size_t)len >= buflen)
        *buffer = '\0';
    return buffer;
}

/* -- Scan Functions -- */

static inline int seteor_return(const char **eor, const char *eoc, int rv, int errnum)
{
    if (eor != 0)
        *eor = eoc;
    if (errnum != ENOERROR)
        errno = errnum;
    return rv;
}

static inline const char *skip_space(const char *str) { while (isspace(*str)) str++; return str; }
static inline int opt_sign(const char **str)
{
    int sign = +1;
    if (**str == '+')
        (*str)++;
    else if (**str == '-')
    {
        sign = -1;
        (*str)++;
    }
    return sign;
}

/* Scan fraction number: [I] or [N/D] or [I N/D] */
static int ri_scnfrc(const char *str, const char **eor, RationalInt *res)
{
    assert(*str == '[');
    const char *eos = strchr(str, ']');
    if (eos == 0)
        return seteor_return(eor, str, -1, EINVAL);
    const char *ptr = skip_space(str + 1);
    int sign = opt_sign(&ptr);
    if (!isdigit(*ptr))
        return seteor_return(eor, eos+1, -1, EINVAL);
    int i;
    if (!chk_strtoi(ptr, &ptr, 10, &i))
        return seteor_return(eor, eos+1, -1, ERANGE);
    ptr = skip_space(ptr);
    if (ptr == eos)
    {
        /* [I] */
        *res = ri_new(i, sign);
        return seteor_return(eor, eos+1, 0, ENOERROR);
    }
    if (*ptr == '/')
    {
        /* [N/D] */
        ptr = skip_space(ptr + 1);
        if (!isdigit(*ptr))
            return seteor_return(eor, eos+1, -1, EINVAL);
        int d;
        if (!chk_strtoi(ptr, &ptr, 10, &d))
            return seteor_return(eor, eos+1, -1, ERANGE);
        ptr = skip_space(ptr);
        if (ptr != eos)
            return seteor_return(eor, eos+1, -1, EINVAL);
        *res = ri_new(i, sign * d);
        return seteor_return(eor, eos+1, 0, ENOERROR);
    }
    else if (isdigit(*ptr))
    {
        /* [I N/D] */
        int n;
        if (!chk_strtoi(ptr, &ptr, 10, &n))
            return seteor_return(eor, eos+1, -1, ERANGE);
        ptr = skip_space(ptr);
        if (*ptr != '/')
            return seteor_return(eor, eos+1, -1, EINVAL);
        ptr = skip_space(ptr + 1);
        int d;
        if (!chk_strtoi(ptr, &ptr, 10, &d))
            return seteor_return(eor, eos+1, -1, ERANGE);
        ptr = skip_space(ptr);
        if (ptr != eos)
            return seteor_return(eor, eos+1, -1, EINVAL);
        /* i, n, d are all valid integers, but can i + n/d be represented? */
        if (i > (INT_MAX - d) / n)
            return seteor_return(eor, eos+1, -1, ERANGE);
        *res = ri_new(d * i + n, sign * d);
        return seteor_return(eor, eos+1, 0, ENOERROR);
    }
    else
        return seteor_return(eor, eos+1, -1, EINVAL);
}

/* Scan decimal number (no square brackets) */
static int ri_scndec(const char *str, const char **eor, RationalInt *res)
{
    const char *ptr = str;
    int sign = opt_sign(&ptr);
    int val = 0;
    int num_i_digits = 0;
    int num_z_digits = 0;
    while (*ptr == '0')         /* Skip leading zeroes */
    {
        num_z_digits++;
        ptr++;
    }
    while (isdigit(*ptr))
    {
        char c = *ptr++ - '0';
        num_i_digits++;
        if (val > INT_MAX / 10 || (val == INT_MAX / 10 && c > INT_MAX % 10))
            return seteor_return(eor, ptr-1, -1, ERANGE);
        val = val * 10 + c;
    }
    if (*ptr != '.')
    {
        if (num_i_digits + num_z_digits == 0)
            return seteor_return(eor, str, -1, EINVAL);
        *res = ri_new(val, sign);
        return seteor_return(eor, ptr, 0, ENOERROR);
    }
    ptr++;
    int i_pow10 = 1;
    while (isdigit(*ptr))
    {
        char c = *ptr++ - '0';

        if (c == 0)
        {
            /* Trailing zeros are ignored! */
            /* Modestly slow for 1.000001 as it scans over the zeros on each iteration */
            const char *trz = ptr;
            while (*trz == '0')
                trz++;
            if (!isdigit(*trz))
            {
                *res = ri_new(val, i_pow10 * sign);
                return seteor_return(eor, trz, 0, ENOERROR);
            }
        }

        if (val > INT_MAX / 10 || (val == INT_MAX / 10 && c > INT_MAX % 10))
            return seteor_return(eor, ptr, -1, ERANGE);

        val = val * 10 + c;
        i_pow10 *= 10;
    }
    if (i_pow10 == 1 && num_i_digits + num_z_digits == 0)
        return seteor_return(eor, str, -1, EINVAL);
    *res = ri_new(val, i_pow10 * sign);
    return seteor_return(eor, ptr, 0, ENOERROR);
}

int ri_scn(const char *str, const char **eor, RationalInt *res)
{
    const char *ptr = str;
    while (isspace((unsigned char)*ptr))
        ptr++;
    int rv;
    if (*ptr == '[')
        rv =  ri_scnfrc(ptr, eor, res);
    else
        rv =  ri_scndec(ptr, eor, res);
    /* If the string was not converted, *eor points to ptr but needs to point to str */
    if (eor != 0 && *eor == ptr)
        *eor = str;
    return rv;
}


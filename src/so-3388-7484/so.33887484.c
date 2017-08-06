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

/* -- Fraction Functions -- */

static void ri_chk(Fraction val)
{
    assert(val.denom != 0 && val.denom != INT_MIN);
    assert(val.numer >= 0);
    assert(val.numer == 0 || gcd(iabs(val.numer), iabs(val.denom)) == 1);
}

/* Unimportant - because all functions already normalize Fraction values, so GCD = 1 */
int ri_gcd(const Fraction *val)
{
    assert(val->denom != 0 && val->denom != INT_MIN);
    return gcd(iabs(val->numer), iabs(val->denom));
}

static Fraction ri_new(int numer, int denom)
{
    assert(denom != 0);
    assert(denom != INT_MIN && denom != INT_MIN);
    Fraction ri;
    /* Handle invalid inputs as 0 if assertions are not enabled */
    if (numer   == 0 || numer   == INT_MIN ||
        denom == 0 || denom == INT_MIN)
    {
        ri.numer = 0;
        ri.denom = 1;
    }
    else
    {
        int sign = signum(numer) * signum(denom);
        assert(sign == +1 || sign == -1);
        int dv = gcd(iabs(numer), iabs(denom));
        assert(dv != 0);
        ri.numer = iabs(numer) / dv;
        ri.denom = sign * iabs(denom) / dv;
    }
    return ri;
}

/* Unimportant - because all functions already normalize Fraction values */
void ri_normalize(Fraction *val)
{
    *val = ri_new(val->numer, val->denom);
}

void ri_add(const Fraction *lhs, const Fraction *rhs, Fraction *res)
{
    long long rn = (long long)lhs->numer * rhs->denom +
                   (long long)rhs->numer * lhs->denom;
    if (rn == 0)
        *res = ri_new(0, 1);
    else
    {
        long long rd = (long long)lhs->denom * rhs->denom;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_sub(const Fraction *lhs, const Fraction *rhs, Fraction *res)
{
    long long rn = (long long)lhs->numer * rhs->denom -
                   (long long)rhs->numer * lhs->denom;
    if (rn == 0)
        *res = ri_new(0, 1);
    else
    {
        long long rd = (long long)lhs->denom * rhs->denom;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_mul(const Fraction *lhs, const Fraction *rhs, Fraction *res)
{
    long long rn = (long long)lhs->numer * rhs->numer;
    if (rn == 0)
    {
        *res = ri_new(0, 1);
    }
    else
    {
        long long rd = (long long)lhs->denom * rhs->denom;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

void ri_div(const Fraction *lhs, const Fraction *rhs, Fraction *res)
{
    assert(rhs->numer != 0);
    if (lhs->numer == 0)     // Zero divided by anything is zero
        *res = ri_new(0, 1);
    else
    {
        long long rn = (long long)lhs->numer * rhs->denom;
        long long rd = (long long)lhs->denom * rhs->numer;
        long long dv = gcd_ll(rn, rd);
        long long nr = rn / dv;
        long long dr = rd / dv;
        assert(nr <= INT_MAX && nr >= INT_MIN);
        assert(dr <= INT_MAX && dr >= INT_MIN);
        *res = ri_new(nr, dr);
    }
}

static void ri_integer(const Fraction *val, Fraction *res)
{
    *res = ri_new(val->numer / val->denom, 1);
}

static void ri_fraction(const Fraction *val, Fraction *res)
{
    *res = ri_new(val->numer % val->denom, val->denom);
}

void ri_mod(const Fraction *lhs, const Fraction *rhs, Fraction *res)
{
    assert(rhs->numer != 0);
    Fraction rd;
    ri_div(lhs, rhs, &rd);
    Fraction ri;
    ri_integer(&rd, &ri);
    Fraction rm;
    ri_mul(&ri, rhs, &rm);
    ri_sub(lhs, &rm, res);
}

/* -- Format functions -- */

char *ri_fmt(Fraction val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    if (buflen > 0 && buffer != 0)
    {
        char sign = (val.denom < 0) ? '-' : '+';
        int len;
        if (iabs(val.denom) == 1)
            len = snprintf(buffer, buflen, "[%c%d]", sign, val.numer);
        else
            len = snprintf(buffer, buflen, "[%c%d/%d]",
                           sign, iabs(val.numer), iabs(val.denom));
        if (len <= 0 || (size_t)len >= buflen)
            *buffer = '\0';
    }
    return buffer;
}

char *ri_fmtproper(Fraction val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    Fraction in;
    ri_integer(&val, &in);
    Fraction fr;
    ri_fraction(&val, &fr);
    char sign = (val.denom < 0) ? '-' : '+';
    int len;
    assert(in.denom == +1 || in.denom == -1);
    if (in.numer != 0 && fr.numer != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d %d/%d]", sign,
                       iabs(in.numer), iabs(fr.numer), iabs(fr.denom));
    }
    else if (in.numer != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d]", sign, iabs(in.numer));
    }
    else if (fr.numer != 0)
    {
        len = snprintf(buffer, buflen, "[%c%d/%d]",
                       sign, iabs(val.numer), iabs(val.denom));
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
static int ri_scnfrc(const char *str, const char **eor, Fraction *res)
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
static int ri_scndec(const char *str, const char **eor, Fraction *res)
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

int ri_scn(const char *str, const char **eor, Fraction *res)
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


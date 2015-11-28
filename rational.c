#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <stddef.h>     // size_t

typedef struct RationalInt
{
    int     numerator;
    int     denominator;
} RationalInt;

extern RationalInt ri_new(int numerator, int denominator);

extern RationalInt ri_add(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_sub(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_mul(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_div(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_mod(RationalInt lhs, RationalInt rhs);
extern RationalInt ri_pow(RationalInt base, RationalInt power);

extern RationalInt ri_rec(RationalInt val);             // Reciprocal
extern RationalInt ri_integer(RationalInt val);         // Integer part
extern RationalInt ri_fraction(RationalInt val);        // Fractional part

extern int ri_cmp(RationalInt lhs, RationalInt rhs);    // Comparison (-1, 0, +1)

extern char *ri_fmt(RationalInt val, char *buffer, size_t buflen);
extern char *ri_fmtproper(RationalInt val, char *buffer, size_t buflen);
extern int ri_scn(const char *str, char **eor, RationalInt *result);

#endif /* RATIONAL_H_INCLUDED */

/*
** Storage rules:
** 1. Denominator is never zero.
** 2. Denominator stores the sign and is not INT_MIN (2's complement assumed).
** 3. Numerator is never negative.
** 4. gcd(numerator, denominator) == 1 unless numerator == 0.
*/

//#include "rational.h"
//#include "chkstrint.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef ENOERROR
#define ENOERROR 0
#endif

#if defined(__cplusplus)
#define CONST_CAST(type, value) const_cast<type>(value)
#else
#define CONST_CAST(type, value) ((type)(value))
#endif

static inline int iabs(int x) { return (x < 0) ? -x : x; }
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

static void ri_chk(RationalInt val)
{
    assert(val.denominator != 0 && val.denominator != INT_MIN);
    assert(val.numerator >= 0);
    assert(val.numerator == 0 || gcd(iabs(val.numerator), iabs(val.denominator)) == 1);
}

RationalInt ri_new(int numerator, int denominator)
{
    assert(denominator != 0);
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

RationalInt ri_add(RationalInt lhs, RationalInt rhs)
{
    long long rn = (long long)lhs.numerator * rhs.denominator +
                   (long long)rhs.numerator * lhs.denominator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = (long long)lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_sub(RationalInt lhs, RationalInt rhs)
{
    long long rn = (long long)lhs.numerator * rhs.denominator -
                   (long long)rhs.numerator * lhs.denominator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = (long long)lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_mul(RationalInt lhs, RationalInt rhs)
{
    long long rn = (long long)lhs.numerator * rhs.numerator;
    if (rn == 0)
        return ri_new(0, 1);
    long long rd = (long long)lhs.denominator * rhs.denominator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

RationalInt ri_div(RationalInt lhs, RationalInt rhs)
{
    assert(rhs.numerator != 0);
    if (lhs.numerator == 0)     // Zero divided by anything is zero
        return ri_new(0, 1);
    long long rn = (long long)lhs.numerator * rhs.denominator;
    long long rd = (long long)lhs.denominator * rhs.numerator;
    long long dv = gcd_ll(rn, rd);
    long long nr = rn / dv;
    long long dr = rd / dv;
    assert(nr <= INT_MAX && nr >= INT_MIN);
    assert(dr <= INT_MAX && dr >= INT_MIN);
    return ri_new(nr, dr);
}

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

int ri_cmp(RationalInt lhs, RationalInt rhs)
{
    if (lhs.denominator == rhs.denominator &&
        lhs.numerator == rhs.numerator)
        return 0;
    if (signum(lhs.denominator) != signum(rhs.denominator))
    {
        /* Different signs - but one could be zero */
        if (signum(lhs.denominator) < signum(rhs.denominator))
            return -1;
        else
            return +1;
    }
    long long v1 = (long long)lhs.numerator * iabs(rhs.denominator);
    long long v2 = (long long)rhs.numerator * iabs(lhs.denominator);
    assert(v1 != v2);
    if (v1 < v2)
        return -1;
    else
        return +1;
}

char *ri_fmtproper(RationalInt val, char *buffer, size_t buflen)
{
    assert(buflen > 0 && buffer != 0);
    ri_chk(val);
    RationalInt in = ri_integer(val);
    RationalInt fr = ri_fraction(val);
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

RationalInt ri_integer(RationalInt val)
{
    RationalInt ri = ri_new(val.numerator / val.denominator, 1);
    return ri;
}

RationalInt ri_fraction(RationalInt val)
{
    RationalInt ri = ri_new(val.numerator % val.denominator, val.denominator);
    return ri;
}

RationalInt ri_mod(RationalInt lhs, RationalInt rhs)
{
    assert(rhs.numerator != 0);
    RationalInt rd = ri_div(lhs, rhs);
    RationalInt ri = ri_integer(rd);
    RationalInt rm = ri_mul(ri, rhs);
    RationalInt rv = ri_sub(lhs, rm);
    return rv;
}

RationalInt ri_rec(RationalInt val)
{
    assert(val.numerator != 0);
    return ri_new(val.denominator, val.numerator);
}

RationalInt ri_pow(RationalInt base, RationalInt power)
{
    assert(power.denominator == +1 || power.denominator == -1);
    if (base.numerator == 0)
        return ri_new(0, 1);
    if (power.numerator == 0)
        return ri_new(1, 1);
    //char buffer[32];
    //printf("-->> %s", ri_fmtproper(base, buffer, sizeof(buffer)));
    //printf(" ^ %s\n", ri_fmtproper(power, buffer, sizeof(buffer)));
    RationalInt factor = base;
    RationalInt result = ri_new(1, 1);
    for (int i = power.numerator; i != 0; i >>= 1)
    {
        //printf("i = %d", i);
        if (i & 1)
        {
            result = ri_mul(result, factor);
            //printf("; result so far: %s\n", ri_fmtproper(result, buffer, sizeof(buffer)));
        }
        /* How much of a kludge is this test? */
        if (i > 1)
        {
            factor = ri_mul(factor, factor);
            //printf("factor: %s\n", ri_fmtproper(factor, buffer, sizeof(buffer)));
        }
    }

    if (power.denominator < 0)
    {
        result = ri_rec(result);
        //printf("reciprocal: %s\n", ri_fmtproper(result, buffer, sizeof(buffer)));
    }


    //printf("<<-- result: %s\n", ri_fmtproper(result, buffer, sizeof(buffer)));
    return result;
}

/* -- Scan Functions -- */

static inline int seteor_return(char **eor, char *eoc, int rv, int errnum)
{
    if (eor != 0)
        *eor = eoc;
    if (errnum != ENOERROR)
        errno = errnum;
    return rv;
}

/* Scan fraction number (in square brackets) */
static int ri_scnfrc(const char *str, char **eor, RationalInt *res)
{
    *res = ri_new(0, 1);
    if (eor != 0)
        *eor = CONST_CAST(char *, str);
    return -1;
}

/* Scan decimal number (no square brackets) */
static int ri_scndec(char *str, char **eor, RationalInt *res)
{
    int sign = +1;
    char *ptr = str;
    while (isspace(*ptr))
        ptr++;
    if (*ptr == '+')
        ptr++;
    else if (*ptr == '-')
    {
        sign = -1;
        ptr++;
    }
    int val = 0;
    int num_i_digits = 0;
    int num_z_digits = 0;
    res->numerator = 0;         /* In case of doubt, the answer is zero */
    res->denominator = 1;
    while (*ptr == '0') /* Skip leading zeroes */
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
            char *trz = ptr;
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

int ri_scn(const char *str, char **eor, RationalInt *res)
{
    /*
    ** The called code doesn't change the string pointed at by str, but
    ** having it passed as a const char *is a pain.  CONST_CAST once to
    ** avoid the pain.
    */
    char *ptr = CONST_CAST(char *, str);
    while (isspace((unsigned char)*ptr))
        ptr++;
    int rv;
    if (*ptr == '[')
        rv =  ri_scnfrc(ptr, eor, res);
    else
        rv =  ri_scndec(ptr, eor, res);
    /* If the string was not converted, *eor points to ptr but needs to point to str */
    if (eor != 0 && *eor == ptr)
        *eor = CONST_CAST(char *, str);
    return rv;
}

#define TEST    // Temporary
#if defined(TEST)

#include "phasedtest.h"

/* -- PHASE 1 TESTING -- */

/* -- ri_new -- */
typedef struct p1_test_case
{
    int i_num;
    int i_den;
    RationalInt res;
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { .i_num =  1, .i_den =  1, .res = {  1,   1 } },
    { .i_num =  0, .i_den =  1, .res = {  0,   1 } },
    { .i_num =  2, .i_den =  2, .res = {  1,   1 } },
    { .i_num =  1, .i_den =  2, .res = {  1,   2 } },
    { .i_num = 15, .i_den =  3, .res = {  5,   1 } },
    { .i_num = 28, .i_den =  6, .res = { 14,   3 } },
    { .i_num =  6, .i_den = 28, .res = {  3,  14 } },
    { .i_num = +6, .i_den = +8, .res = {  3,  +4 } },
    { .i_num = +6, .i_den = -8, .res = {  3,  -4 } },
    { .i_num = -6, .i_den = +8, .res = {  3,  -4 } },
    { .i_num = -6, .i_den = -8, .res = {  3,  +4 } },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    ri_chk(test->res);

    RationalInt ri = ri_new(test->i_num, test->i_den);

    if (ri.denominator != test->res.denominator ||
        ri.numerator != test->res.numerator)
        pt_fail("ri_new(%d, %d) - unexpected result %s (instead of %s)\n",
                test->i_num, test->i_den, ri_fmt(ri, buffer1, sizeof(buffer1)),
                ri_fmt(test->res, buffer2, sizeof(buffer2)));
    else
        pt_pass("ri_new(%d, %d) - %s\n", test->i_num, test->i_den,
                ri_fmt(test->res, buffer2, sizeof(buffer2)));
}

/* -- PHASE 2 TESTING -- */

/* -- ri_cmp -- */
typedef struct p2_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    int         res;
} p2_test_case;

static const p2_test_case p2_tests[] =
{
    { {  0,  +1 }, {  0,  +1 },  0 },
    { {  1,  +1 }, {  0,  +1 }, +1 },
    { {  0,  +1 }, {  1,  +1 }, -1 },
    { {  0,  +1 }, {  1,  -1 }, +1 },
    { {  1,  -1 }, {  1,  +1 }, -1 },
    { {  1,  +1 }, {  1,  -1 }, +1 },
    { {  9, +10 }, {  1,  +1 }, -1 },
    { { 11, +10 }, {  1,  +1 }, +1 },
    { {  9, +10 }, { 19, +20 }, -1 },
    { {  9, +10 }, { 17, +20 }, +1 },
};

static void p2_tester(const void *data)
{
    const p2_test_case *test = (const p2_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    ri_chk(test->lhs);
    ri_chk(test->rhs);

    int rc = ri_cmp(test->lhs, test->rhs);
    if (rc != test->res)
        pt_fail("unexpected result (%s <=> %s) gave %+d instead of %+d\n",
                 ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                 ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                 rc, test->res);
    else
        pt_pass("(%s <=> %s) = %+d\n",
                 ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                 ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                 test->res);
}

/* -- PHASE 3 TESTING -- */

/* -- Rational Binary Operators -- */
typedef struct BinaryOp
{
    RationalInt (*op_func)(RationalInt lhs, RationalInt rhs);
    char         *op_name;
} BinaryOp;

enum { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD };

static const BinaryOp ri_ops[] =
{
    [OP_ADD] = { ri_add, "+" },
    [OP_SUB] = { ri_sub, "-" },
    [OP_MUL] = { ri_mul, "*" },
    [OP_DIV] = { ri_div, "/" },
    [OP_MOD] = { ri_mod, "%" },
};

typedef struct p3_test_case
{
    const BinaryOp *op;
    RationalInt lhs;
    RationalInt rhs;
    RationalInt res;
} p3_test_case;

static const p3_test_case p3_tests[] =
{

    { &ri_ops[OP_ADD], {  0,  1 }, {  0,  1 }, {    0,   1 } },
    { &ri_ops[OP_ADD], {  1,  1 }, {  0,  1 }, {    1,   1 } },
    { &ri_ops[OP_ADD], {  1,  1 }, {  1,  1 }, {    2,   1 } },
    { &ri_ops[OP_ADD], {  1,  1 }, {  1, -1 }, {    0,   1 } },
    { &ri_ops[OP_ADD], { 23, 31 }, { 37, 19 }, { 1584, 589 } },
    { &ri_ops[OP_ADD], { 14, -9 }, { 12, -7 }, {  206, -63 } },
    { &ri_ops[OP_ADD], { 14, -9 }, { 12, +7 }, {   10, +63 } },
    { &ri_ops[OP_ADD], { 14, +9 }, { 12, -7 }, {   10, -63 } },
    { &ri_ops[OP_ADD], { 14, +9 }, { 12, +7 }, {  206, +63 } },

    { &ri_ops[OP_SUB], {  0,  1 }, {  0,  1 }, {    0,    1 } },
    { &ri_ops[OP_SUB], {  1,  1 }, {  0,  1 }, {    1,    1 } },
    { &ri_ops[OP_SUB], {  1,  1 }, {  1,  1 }, {    0,    1 } },
    { &ri_ops[OP_SUB], {  1, -1 }, {  1,  1 }, {    2,   -1 } },
    { &ri_ops[OP_SUB], {  1, -1 }, {  2, -1 }, {    1,    1 } },
    { &ri_ops[OP_SUB], {  1,  1 }, {  1, -1 }, {    2,    1 } },
    { &ri_ops[OP_SUB], { 23, 31 }, { 37, 19 }, {  710, -589 } },
    { &ri_ops[OP_SUB], { 14, -9 }, { 12, -7 }, {   10,  +63 } },
    { &ri_ops[OP_SUB], { 14, -9 }, { 12, +7 }, {  206,  -63 } },
    { &ri_ops[OP_SUB], { 14, +9 }, { 12, -7 }, {  206,  +63 } },
    { &ri_ops[OP_SUB], { 14, +9 }, { 12, +7 }, {   10,  -63 } },

    { &ri_ops[OP_MUL], {  0,  1 }, {  0,  1 }, {    0,    1 } },
    { &ri_ops[OP_MUL], {  1,  1 }, {  0,  1 }, {    0,    1 } },
    { &ri_ops[OP_MUL], {  1,  1 }, {  1,  1 }, {    1,    1 } },
    { &ri_ops[OP_MUL], {  1, -1 }, {  1,  1 }, {    1,   -1 } },
    { &ri_ops[OP_MUL], {  1, -1 }, {  2, -1 }, {    2,    1 } },
    { &ri_ops[OP_MUL], {  1,  1 }, {  1, -1 }, {    1,   -1 } },
    { &ri_ops[OP_MUL], { 23, 31 }, { 37, 19 }, {  851,  589 } },
    { &ri_ops[OP_MUL], { 14, -9 }, { 12, -7 }, {    8,   +3 } },
    { &ri_ops[OP_MUL], { 14, -9 }, { 12, +7 }, {    8,   -3 } },
    { &ri_ops[OP_MUL], { 14, +9 }, { 12, -7 }, {    8,   -3 } },
    { &ri_ops[OP_MUL], { 14, +9 }, { 12, +7 }, {    8,   +3 } },

    { &ri_ops[OP_DIV], {  0,  1 }, {  1,  1 }, {    0,    1 } },
    { &ri_ops[OP_DIV], {  1,  1 }, {  1,  1 }, {    1,    1 } },
    { &ri_ops[OP_DIV], {  1, -1 }, {  1,  1 }, {    1,   -1 } },
    { &ri_ops[OP_DIV], {  1, -1 }, {  2, -1 }, {    1,    2 } },
    { &ri_ops[OP_DIV], {  1,  1 }, {  1, -1 }, {    1,   -1 } },
    { &ri_ops[OP_DIV], { 23, 31 }, { 37, 19 }, {  437, 1147 } },
    { &ri_ops[OP_DIV], { 14, -9 }, { 12, -7 }, {   49,  +54 } },
    { &ri_ops[OP_DIV], { 14, -9 }, { 12, +7 }, {   49,  -54 } },
    { &ri_ops[OP_DIV], { 14, +9 }, { 12, -7 }, {   49,  -54 } },
    { &ri_ops[OP_DIV], { 14, +9 }, { 12, +7 }, {   49,  +54 } },

    { &ri_ops[OP_MOD], {  0,  +1 }, {  1,  +1 }, {    0,     1 } },
    { &ri_ops[OP_MOD], {  1,  +1 }, {  1,  +1 }, {    0,     1 } },
    { &ri_ops[OP_MOD], {  1,  -1 }, {  1,  +1 }, {    0,     1 } },
    { &ri_ops[OP_MOD], {  1,  -1 }, {  2,  -1 }, {    1,    -1 } },
    { &ri_ops[OP_MOD], {  1,  +1 }, {  1,  -1 }, {    0,     1 } },
    { &ri_ops[OP_MOD], { 23, +31 }, { 37, +19 }, {   23,   +31 } },
    { &ri_ops[OP_MOD], { 63, +31 }, { 37, +19 }, {   50,  +589 } },
    { &ri_ops[OP_MOD], { 91, +23 }, { 37, +19 }, {   27,  +437 } },
    { &ri_ops[OP_MOD], { 23, +31 }, { 19, +37 }, {  262, +1147 } },
    { &ri_ops[OP_MOD], { 14,  -9 }, { 10,  -7 }, {    8,   -63 } },
    { &ri_ops[OP_MOD], { 14,  -9 }, { 10,  +7 }, {    8,   -63 } },
    { &ri_ops[OP_MOD], { 14,  +9 }, { 10,  -7 }, {    8,   +63 } },
    { &ri_ops[OP_MOD], { 14,  +9 }, { 10,  +7 }, {    8,   +63 } },
    { &ri_ops[OP_MOD], {  9, -11 }, {  2,  -7 }, {   19,   -77 } },
    { &ri_ops[OP_MOD], {  9, -11 }, {  2,  +7 }, {   19,   -77 } },
    { &ri_ops[OP_MOD], {  9, +11 }, {  2,  -7 }, {   19,   +77 } },
    { &ri_ops[OP_MOD], {  9, +11 }, {  2,  +7 }, {   19,   +77 } },

};

static void p3_tester(const void *data)
{
    const p3_test_case *test = (const p3_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];
    ri_chk(test->lhs);
    ri_chk(test->rhs);
    ri_chk(test->res);

    RationalInt res = (*test->op->op_func)(test->lhs, test->rhs);
    int rc = ri_cmp(test->res, res);
    if (rc != 0)
        pt_fail("unexpected result for %s %s %s (actual %s vs wanted %s: %d)\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                test->op->op_name,
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(res,       buffer3, sizeof(buffer3)),
                ri_fmt(test->res, buffer4, sizeof(buffer4)),
                rc);
    else
        pt_pass("%s %s %s = %s\n",
                ri_fmt(test->lhs, buffer1, sizeof(buffer1)),
                test->op->op_name,
                ri_fmt(test->rhs, buffer2, sizeof(buffer2)),
                ri_fmt(test->res, buffer3, sizeof(buffer3)));
}

/* -- PHASE 4 TESTING -- */

/* -- Fraction and Integer -- */
typedef struct p4_test_case
{
    RationalInt input;
    RationalInt o_int;
    RationalInt o_frac;
} p4_test_case;

static const p4_test_case p4_tests[] =
{
    { {  0,   1 }, { 0,  1 }, {  0,   1 } },
    { {  1,   1 }, { 1,  1 }, {  0,   1 } },
    { {  1,   2 }, { 0,  1 }, {  1,   2 } },
    { {  3,   2 }, { 1,  1 }, {  1,   2 } },
    { { 23, +12 }, { 1, +1 }, { 11, +12 } },
    { { 23, -12 }, { 1, -1 }, { 11, -12 } },
    { { 12, +23 }, { 0, +1 }, { 12, +23 } },
    { { 12, -23 }, { 0, +1 }, { 12, -23 } },
};

static void p4_tester(const void *data)
{
    const p4_test_case *test = (const p4_test_case *)data;
    ri_chk(test->input);
    ri_chk(test->o_int);
    ri_chk(test->o_frac);
    RationalInt ri = ri_integer(test->input);
    RationalInt rf = ri_fraction(test->input);
    char buffer0[32];
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];
    char buffer5[32];

    int rc1 = ri_cmp(ri, test->o_int);
    int rc2 = ri_cmp(rf, test->o_frac);
    if (rc1 != 0 || rc2 != 0)
        pt_fail("%s: unexpected result %s (%d: actual %s vs wanted %s)"
                "(%d: actual %s vs wanted %s)\n",
                ri_fmt(test->input,  buffer0, sizeof(buffer0)),
                ri_fmtproper(test->input,  buffer1, sizeof(buffer1)),
                rc1,
                ri_fmtproper(ri,           buffer2, sizeof(buffer2)),
                ri_fmtproper(test->o_int,  buffer3, sizeof(buffer3)),
                rc2,
                ri_fmtproper(rf,           buffer4, sizeof(buffer4)),
                ri_fmtproper(test->o_frac, buffer5, sizeof(buffer5)));
    else
        pt_pass("%s: %s becomes %s and %s\n",
                ri_fmt(test->input,  buffer0, sizeof(buffer0)),
                ri_fmtproper(test->input,  buffer1, sizeof(buffer1)),
                ri_fmtproper(ri,           buffer2, sizeof(buffer2)),
                ri_fmtproper(rf,           buffer4, sizeof(buffer4)));
}

/* -- PHASE 5 TESTING -- */

/* -- Check modulus -- */
typedef struct p5_test_case
{
    RationalInt lhs;
    RationalInt rhs;
    RationalInt mod;
} p5_test_case;

static const p5_test_case p5_tests[] =
{
    { { 23, +31 }, { 37, +19 }, {   23,   +31 } },
    { { 63, +31 }, { 37, +19 }, {   50,  +589 } },
    { { 91, +23 }, { 37, +19 }, {   27,  +437 } },
    { { 23, +31 }, { 19, +37 }, {  262, +1147 } },
    { { 14,  -9 }, { 10,  -7 }, {    8,   -63 } },
    { {  9, -11 }, {  2,  -7 }, {   19,   -77 } },
};

static void p5_tester(const void *data)
{
    const p5_test_case *test = (const p5_test_case *)data;
    ri_chk(test->lhs);
    ri_chk(test->rhs);
    ri_chk(test->mod);
    RationalInt dv = ri_div(test->lhs, test->rhs);
    RationalInt in = ri_integer(dv);
    RationalInt mv = ri_mod(test->lhs, test->rhs);
    RationalInt rv = ri_add(ri_mul(in, test->rhs), mv);
    char buffer[10][32];

    if (ri_cmp(mv, test->mod) != 0 || ri_cmp(rv, test->lhs) != 0)
    {
        pt_fail("%s %% %s = %s but %s / %s = %s and %s * %s + %s != %s\n",
                ri_fmtproper(test->lhs, buffer[0], sizeof(buffer[0])),
                ri_fmtproper(test->rhs, buffer[1], sizeof(buffer[1])),
                ri_fmtproper(test->mod, buffer[2], sizeof(buffer[2])),
                ri_fmtproper(test->lhs, buffer[3], sizeof(buffer[3])),
                ri_fmtproper(test->rhs, buffer[4], sizeof(buffer[4])),
                ri_fmtproper(dv,        buffer[5], sizeof(buffer[5])),
                ri_fmtproper(in,        buffer[6], sizeof(buffer[6])),
                ri_fmtproper(test->rhs, buffer[7], sizeof(buffer[7])),
                ri_fmtproper(test->mod, buffer[8], sizeof(buffer[8])),
                ri_fmtproper(test->lhs, buffer[9], sizeof(buffer[9])));
    }
    else
    {
        pt_pass("%s %% %s = %s and %s * %s + %s = %s\n",
                ri_fmtproper(test->lhs, buffer[0], sizeof(buffer[0])),
                ri_fmtproper(test->rhs, buffer[1], sizeof(buffer[1])),
                ri_fmtproper(test->mod, buffer[2], sizeof(buffer[2])),
                ri_fmtproper(test->rhs, buffer[3], sizeof(buffer[3])),
                ri_fmtproper(in,        buffer[4], sizeof(buffer[4])),
                ri_fmtproper(test->mod, buffer[5], sizeof(buffer[5])),
                ri_fmtproper(test->lhs, buffer[6], sizeof(buffer[6])));
    }
}

/* -- PHASE 6 TESTING -- */

/* -- Powers and Reciprocals -- */
typedef struct p6_test_case
{
    RationalInt base;
    RationalInt power;
    RationalInt result;
} p6_test_case;

/*
** Power runs into trouble rather quickly — it isn't as useful as all
** that.  There might be a way to avoid doing the multiple too soon, but
** that merely delays the onset of problems.
*/
static const p6_test_case p6_tests[] =
{
    { {  0,  1 }, {  0, +1 }, {          0,          +1 } },
    { {  0,  1 }, {  5, +1 }, {          0,          +1 } },
    { {  1,  1 }, {  0, +1 }, {          1,          +1 } },
    { {  2,  1 }, {  0, +1 }, {          1,          +1 } },
    { {  3,  2 }, {  0, +1 }, {          1,          +1 } },
    { {  2,  1 }, {  1, +1 }, {          2,          +1 } },
    { {  3,  1 }, {  1, +1 }, {          3,          +1 } },
    { {  5,  2 }, {  1, +1 }, {          5,          +2 } },
    { {  2,  1 }, {  2, +1 }, {          4,          +1 } },
    { {  2,  1 }, {  3, +1 }, {          8,          +1 } },
    { {  2,  1 }, { 10, +1 }, {       1024,          +1 } },
    { {  2,  1 }, { 15, +1 }, {      32768,          +1 } },
    { {  5,  2 }, {  2, +1 }, {         25,          +4 } },
    { {  5,  2 }, {  2, -1 }, {          4,         +25 } },
    { {  2,  1 }, { 16, +1 }, {      65536,          +1 } },
    { {  2,  1 }, { 17, +1 }, {     131072,          +1 } },
    { {  2,  1 }, { 20, +1 }, {  1024*1024,          +1 } },
    { {  2,  1 }, { 24, +1 }, { 16384*1024,          +1 } },
    { {  2,  1 }, { 30, +1 }, { 1073741824,          +1 } },
    { {  2,  1 }, { 30, -1 }, {          1, +1073741824 } },
    { { 10,  1 }, {  8, -1 }, {          1,  +100000000 } },
    { { 10,  1 }, {  8, +1 }, {  100000000,          +1 } },
    { { 10, 13 }, {  8, +1 }, {  100000000,  +815730721 } },
    { { 10, 13 }, {  8, -1 }, {  815730721,  +100000000 } },
    { { 13, 10 }, {  8, +1 }, {  815730721,  +100000000 } },
    { { 13, 10 }, {  8, -1 }, {  100000000,  +815730721 } },
    { { 87,  7 }, {  4, +1 }, {   57289761,       +2401 } },
};

static void p6_tester(const void *data)
{
    const p6_test_case *test = (const p6_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];
    ri_chk(test->base);
    ri_chk(test->power);
    ri_chk(test->result);

    RationalInt result = ri_pow(test->base, test->power);

    int rc = ri_cmp(result, test->result);
    if (rc != 0)
        pt_fail("unexpected result: %s ^ %s = (actual %s vs wanted %s) %d\n",
                 ri_fmtproper(test->base,   buffer1, sizeof(buffer1)),
                 ri_fmtproper(test->power,  buffer2, sizeof(buffer2)),
                 ri_fmtproper(result,       buffer3, sizeof(buffer3)),
                 ri_fmtproper(test->result, buffer4, sizeof(buffer4)),
                 rc);
    else
        pt_pass("%s ^ %s = %s\n",
                 ri_fmtproper(test->base,   buffer1, sizeof(buffer1)),
                 ri_fmtproper(test->power,  buffer2, sizeof(buffer2)),
                 ri_fmtproper(result,       buffer3, sizeof(buffer3)));
}

/* -- PHASE 7 TESTING -- */

/* -- Scanning fractions -- */
typedef struct p7_test_case
{
    const char *input;
    RationalInt output;
    int         offset;
    int         status;
} p7_test_case;

static const p7_test_case p7_tests[] =
{
    { "0",                {          0,        +1 },  1,  0 },
    { "-0",               {          0,        +1 },  2,  0 },
    { "+0",               {          0,        +1 },  2,  0 },
    { "- 0",              {          0,        +1 },  0, -1 },
    { "+ 0",              {          0,        +1 },  0, -1 },
    { "-. 0",             {          0,        +1 },  0, -1 },
    { "+. 0",             {          0,        +1 },  0, -1 },
    { "+0",               {          0,        +1 },  2,  0 },
    { "+000",             {          0,        +1 },  4,  0 },
    { "+123",             {        123,        +1 },  4,  0 },
    { "-321",             {        321,        -1 },  4,  0 },
    { "-321.",            {        321,        -1 },  5,  0 },
    { "-0.321",           {        321,     -1000 },  6,  0 },
    { "-0.-321",          {          0,        +1 },  3,  0 },
    { "-.-321",           {          0,        +1 },  0, -1 },
    { "+0.00",            {          0,        +1 },  5,  0 },
    { "+0.+00",           {          0,        +1 },  3,  0 },
    { "+9+00",            {          9,        +1 },  2,  0 },
    { "-.000",            {          0,        +1 },  5,  0 },
    { "0.5XX",            {          1,        +2 },  3,  0 },
    { "-3.14159",         {     314159,   -100000 },  8,  0 },
    { "2147483647X",      { 2147483647,        +1 }, 10,  0 },
    { "-2147.483647 ",    { 2147483647,  -1000000 }, 12,  0 },
    { "0002147483.647",   { 2147483647,     +1000 }, 14,  0 },
    { "000000.7483647",   {    7483647, +10000000 }, 14,  0 },
    { "-2147.483648 ",    {          0,        +1 }, 12, -1 },

    /* How to handle these trailing zeros given that the string is not modifiable? */
    { "-2147.48364700",   { 2147483647,  -1000000 }, 14,  0 },
    { "-2147.4836470000", { 2147483647,  -1000000 }, 16,  0 },
    { "-2147.2147480000", {  536803687,   -250000 }, 16,  0 },
    { "-2147.4000000000", {      10737,        -5 }, 16,  0 },
    { "-2147.2000000000", {      10736,        -5 }, 16,  0 },

    { "    0",            {          0,        +1 },  5,  0 },
    { "    0    ",        {          0,        +1 },  5,  0 },
    { "    X",            {          0,        +1 },  0, -1 },

    { "[0]",              {          0,        +1 },  3,  0 },
    { "[1/2]",            {          1,        +2 },  5,  0 },
    { "[+1/2]",           {          1,        +2 },  6,  0 },
    { "[-1/2]",           {          1,        -2 },  6,  0 },
    { "[+3/2]",           {          3,        +2 },  6,  0 },
    { "[+1 1/2]",         {          3,        +2 },  8,  0 },
    { "[-1 1/2]",         {          3,        -2 },  8,  0 },
    { "[1 1/2]",          {          3,        +2 },  7,  0 },
    { "[12 15/3]",        {         17,        +1 },  9,  0 },
};

static void p7_tester(const void *data)
{
    const p7_test_case *test = (const p7_test_case *)data;
    char buffer1[32];
    char buffer2[32];
    ri_chk(test->output);
    pt_settestid("<<%s>> for <<%s>>", test->input,
                 ri_fmt(test->output, buffer1, sizeof(buffer1)));
    char *eof;
    RationalInt res;
    int rc = ri_scn(test->input, &eof, &res);
    pt_check_status(test->status, rc);
    pt_check_int(test->offset, (int)(eof - test->input), "unexpected end of fraction");
    if (rc == 0 && test->status == 0)
    {
        rc = ri_cmp(res, test->output);
        if (rc != 0)
            pt_fail("unexpected result: %s => (actual %s vs wanted %s) %d\n",
                    test->input,
                    ri_fmtproper(res,          buffer1, sizeof(buffer1)),
                    ri_fmtproper(test->output, buffer2, sizeof(buffer2)),
                    rc);
        else
            pt_pass("%s = %s\n",
                    test->input,
                    ri_fmtproper(test->output, buffer1, sizeof(buffer1)));
    }
    pt_done("<<%s>>\n", test->input);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "ri_new" },
    { p2_tester, PT_ARRAYINFO(p2_tests), 0, "ri_cmp" },
    { p3_tester, PT_ARRAYINFO(p3_tests), 0, "Rational Binary Operators" },
    { p4_tester, PT_ARRAYINFO(p4_tests), 0, "Fraction and Integer" },
    { p5_tester, PT_ARRAYINFO(p5_tests), 0, "Check modulus" },
    { p6_tester, PT_ARRAYINFO(p6_tests), 0, "Powers and Reciprocals" },
    { p7_tester, PT_ARRAYINFO(p7_tests), 0, "Scanning fractions" },
};

int main(int argc, char **argv)
{
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

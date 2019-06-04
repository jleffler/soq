/*
@(#)File:           timespec_io.c
@(#)Purpose:        Convert string to timespec and vice versa
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     timespec_io.c 2.1 2019/06/02 05:12:31
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "timespec_io.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { NS_PER_SECOND = 1000000000 };

int scn_timespec(const char *str, struct timespec *value)
{
    assert(str != 0 && value != 0);
    if (str == 0 || value == 0)
    {
        errno = EINVAL;
        return -1;
    }
    long sec;
    long nsec = 0;
    int sign = +1;
    char *end;
    /* No library routine sets errno to 0 - but this one needs to */
    int old_errno = errno;

    errno = 0;

    /* Skip leading white space */
    while (isspace((unsigned char)*str))
        str++;

    /* Detect optional sign */
    if (*str == '+')
        str++;
    else if (*str == '-')
    {
        sign = -1;
        str++;
    }

    /* Next character must be a digit */
    if (!isdigit((unsigned char)*str))
    {
        errno = EINVAL;
        return -1;
    }

    /* Convert seconds part of string */
    sec = strtol(str, &end, 10);
    if (end == str || ((sec == LONG_MAX || sec == LONG_MIN) && errno == ERANGE))
    {
        errno = EINVAL;
        return -1;
    }

    if (*end != '\0' && !isspace((unsigned char)*end))
    {
        if (*end++ != '.')
        {
            errno = EINVAL;
            return -1;
        }
        if (*end == '\0')
            nsec = 0;
        else if (isdigit((unsigned char)*end))
        {
            char *frac = end;
            nsec = strtol(frac, &end, 10);
            if (end == str ||
                ((nsec == LONG_MAX || nsec == LONG_MIN) && errno == ERANGE) ||
                (nsec < 0 || nsec >= NS_PER_SECOND) || (end - frac > 9))
            {
                errno = EINVAL;
                return -1;
            }
            for (int i = 0; i < 9 - (end - frac); i++)
                nsec *= 10;
        }
    }

    /* Allow trailing white space - only */
    unsigned char uc;
    while ((uc = (unsigned char)*end++) != '\0')
    {
        if (!isspace(uc))
        {
            errno = EINVAL;
            return -1;
        }
    }

    /* Success! */
    value->tv_sec = sec * sign;
    value->tv_nsec = nsec * sign;
    errno = old_errno;
    return 0;
}

int fmt_timespec(const struct timespec *value, int dp, char *buffer, size_t buflen)
{
    assert(value != 0 && buffer != 0 && buflen != 0);
    if (value == 0 || buffer == 0 || buflen == 0)
    {
        errno = EINVAL;
        return -1;
    }
    assert(dp >= 0 && dp <= 9);
    if (dp < 0 || dp > 9)
    {
        errno = EINVAL;
        return -1;
    }
    if ((value->tv_sec > 0 && value->tv_nsec < 0) ||
        (value->tv_sec < 0 && value->tv_nsec > 0))
    {
        /* Non-zero components of struct timespec must have same sign */
        errno = EINVAL;
        return -1;
    }

    int len;
    if (dp == 0)
        len = snprintf(buffer, buflen, "%ld", value->tv_sec);
    else
    {
        long nsec = value->tv_nsec;
        long secs = value->tv_sec;
        const char *sign = (secs < 0 || (secs == 0 && nsec < 0)) ? "-" : "";
        if (secs < 0)
            secs = -secs;
        if (nsec < 0)
            nsec = -nsec;
        for (int i = 0; i < 9 - dp; i++)
            nsec /= 10;
        len = snprintf(buffer, buflen, "%s%ld.%.*ld", sign, secs, dp, nsec);
    }
    if (len > 0 && (size_t)len < buflen)
        return len;
    errno = EINVAL;
    return -1;
}

#ifdef TEST

#include "stderr.h"
#include "phasedtest.h"
#include "cchrstrlit.h"
#include <string.h>

/* -- PHASE 1 TESTING -- */

/* -- Basic test of scn_timespec and fmt_timespec-- */
typedef struct p1_test_case
{
    const char *input;
    struct timespec output;
    const char *result;
} p1_test_case;

static const p1_test_case p1_tests[] =
{
    { "0",                    { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "0.",                   { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "0.  ",                 { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "0.0",                  { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "0.01",                 { .tv_sec =          0, .tv_nsec =   10000000 },          "0.010000000" },
    { "0.012",                { .tv_sec =          0, .tv_nsec =   12000000 },          "0.012000000" },
    { "0.0123",               { .tv_sec =          0, .tv_nsec =   12300000 },          "0.012300000" },
    { "0.01234 \t\n",         { .tv_sec =          0, .tv_nsec =   12340000 },          "0.012340000" },
    { "0.012345   ",          { .tv_sec =          0, .tv_nsec =   12345000 },          "0.012345000" },
    { "0.0123456 ",           { .tv_sec =          0, .tv_nsec =   12345600 },          "0.012345600" },
    { "0.01234567",           { .tv_sec =          0, .tv_nsec =   12345670 },          "0.012345670" },
    { "0.012345678",          { .tv_sec =          0, .tv_nsec =   12345678 },          "0.012345678" },
    { "0.000005678",          { .tv_sec =          0, .tv_nsec =       5678 },          "0.000005678" },
    { "0.000000678",          { .tv_sec =          0, .tv_nsec =        678 },          "0.000000678" },
    { "0.000000078  ",        { .tv_sec =          0, .tv_nsec =         78 },          "0.000000078" },
    { "-0.000000008 ",        { .tv_sec =          0, .tv_nsec =         -8 },         "-0.000000008" },
    { "0.000000000",          { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "-0.000000000",         { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "+0.000000000",         { .tv_sec =          0, .tv_nsec =          0 },          "0.000000000" },
    { "1.012345678",          { .tv_sec =          1, .tv_nsec =   12345678 },          "1.012345678" },
    { "12.012345678",         { .tv_sec =         12, .tv_nsec =   12345678 },         "12.012345678" },
    { "123.012345678",        { .tv_sec =        123, .tv_nsec =   12345678 },        "123.012345678" },
    { "123456789.912345678",  { .tv_sec =  123456789, .tv_nsec =  912345678 },  "123456789.912345678" },
    { "-123456789.912345678", { .tv_sec = -123456789, .tv_nsec = -912345678 }, "-123456789.912345678" },
    { "+123456789.912345678", { .tv_sec =  123456789, .tv_nsec =  912345678 },  "123456789.912345678" },
};

static void p1_tester(const void *data)
{
    const p1_test_case *test = (const p1_test_case *)data;
    struct timespec t_out;
    char buffer1[32];
    int len;

    if (scn_timespec(test->input, &t_out) != 0)
        pt_fail("failed to convert [%s]\n", test->input);
    else if ((len = fmt_timespec(&t_out, 9, buffer1, sizeof(buffer1))) < 0)
        pt_fail("failed to format [%s]\n", test->input);
    else if (strcmp(buffer1, test->result) != 0)
        pt_fail("Format mismatch: wanted %s actual %s\n", test->result, buffer1);
    else
    {
        char buffer2[32];
        char buffer3[32];
        str_cstrlit(test->input, buffer2, sizeof(buffer2));
        snprintf(buffer3, sizeof(buffer3), "[%.*s]", (int)(sizeof(buffer3)-3), buffer2);
        pt_pass("%-22s formats to (%2d) [%s]\n", buffer3, len, buffer1);
    }
}

/* -- PHASE 2 TESTING -- */

/* -- Controlling display format of fmt_timespec -- */
typedef struct p2_test_case
{
    struct timespec input;
    int             dp;
    const char *output;
} p2_test_case;

static const p2_test_case p2_tests[] =
{
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 9, "1234.987654321" },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 8, "1234.98765432"  },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 7, "1234.9876543"   },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 6, "1234.987654"    },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 5, "1234.98765"     },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 4, "1234.9876"      },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 3, "1234.987"       },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 2, "1234.98"        },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 1, "1234.9"         },
    { { .tv_sec = 1234, .tv_nsec = 987654321 }, 0, "1234"           },
};

static void p2_tester(const void *data)
{
    const p2_test_case *test = (const p2_test_case *)data;

    char buffer[32];
    int rc;

    if ((rc = fmt_timespec(&test->input, test->dp, buffer, sizeof(buffer))) < 0)
        pt_fail("failed to generate [%s]\n", test->output);
    else if (strcmp(buffer, test->output) != 0)
        pt_fail("<<%s>> (actual) vs <<%s>> (wanted)\n", buffer, test->output);
    else
        pt_pass("(%d) <<%s>>\n", rc, test->output);
}

/* -- PHASE 3 TESTING -- */

/* -- Failure tests for scn_timespec -- */
typedef struct p3_test_case
{
    const char *input;
} p3_test_case;

static const p3_test_case p3_tests[] =
{
    { "" },
    { " " },
    { " ." },
    { " .0" },
    { " 1 0" },
    { "1.00X" },
    { "X1.00X" },
    { "12345678901234567890.112233" },
    { "1234.1234567890" },
};

static void p3_tester(const void *data)
{
    const p3_test_case *test = (const p3_test_case *)data;

    int rc;
    struct timespec t_out;
    errno = 0;

    rc = scn_timespec(test->input, &t_out);
    if (rc == 0)
        pt_fail("<<%s>> unexpected success\n", test->input);
    else if (errno != EINVAL)
        pt_fail("<<%s>> - unexpected errno (%d instead of %d)\n",
                test->input, errno, EINVAL);
    else
        pt_pass("<<%s>> - got expected failure\n", test->input);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "Basic test of scn_timespec and fmt_timespec" },
    { p2_tester, PT_ARRAYINFO(p2_tests), 0, "Controlling display format of fmt_timespec" },
    { p3_tester, PT_ARRAYINFO(p3_tests), 0, "Failure tests for scn_timespec" },
};

int main(int argc, char **argv)
{
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

#endif /* TEST */

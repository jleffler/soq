/*
@(#)File:           chkstrint.c
@(#)Purpose:        Checked string to integer conversions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     chkstrint.c 1.2 2016/01/18 03:39:42
*/

/*TABSTOP=4*/

#include "chkstrint.h"
#include "jlss.h"       /* strtoi(), strtoui(), strtosize() */
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>

/* Checked string to integer conversions report true for successful conversion */

bool chk_strtosize(const char *data, char **eon, int base, size_t *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtosize(data, &end, base);
    if (end == data || (*result == SIZE_MAX && errno == ERANGE))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoi(const char *data, char **eon, int base, int *result)
{
    char *end;
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

bool chk_strtol(const char *data, char **eon, int base, long *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtol(data, &end, base);
    if (end == data || (errno == ERANGE && (*result == LONG_MIN || *result == LONG_MAX)))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoll(const char *data, char **eon, int base, long long *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoll(data, &end, base);
    if (end == data || (errno == ERANGE && (*result == LLONG_MIN || *result == LLONG_MAX)))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoui(const char *data, char **eon, int base, unsigned int *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoui(data, &end, base);
    if (end == data || (*result == UINT_MAX && errno == ERANGE))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoul(const char *data, char **eon, int base, unsigned long *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoul(data, &end, base);
    if (end == data || (*result == ULONG_MAX && errno == ERANGE))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoull(const char *data, char **eon, int base, unsigned long long *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoull(data, &end, base);
    if (end == data || (*result == ULLONG_MAX && errno == ERANGE))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoimax(const char *data, char **eon, int base, intmax_t *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoimax(data, &end, base);
    if (end == data || (errno == ERANGE && (*result == INTMAX_MIN || *result == INTMAX_MAX)))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}

bool chk_strtoumax(const char *data, char **eon, int base, uintmax_t *result)
{
    char *end;
    bool rc = true;
    int old_errno = errno;

    errno = 0;
    *result = strtoumax(data, &end, base);
    if (end == data || (*result == UINTMAX_MAX && errno == ERANGE))
        rc = false;

    if (eon != 0)
        *eon = end;
    if (errno == 0)
        errno = old_errno;
    return rc;
}


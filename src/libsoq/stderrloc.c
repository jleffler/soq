/*
@(#)File:           stderrloc.c
@(#)Purpose:        Standard Error Logging Functions with Locations
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016-2023
@(#)Derivation:     stderrloc.c 1.4 2023/03/09 04:52:52
*/

/*TABSTOP=4*/

/* -- Include Files */

#include "posixver.h"
#include "stderrloc.h"
#include "stderr.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/* Missing time stamp and PID data */

NORETURN void err_pos_error(const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_pos_verror(file, line, func, fmt, args);
    va_end(args);
}

NORETURN void err_pos_syserr(const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_pos_vsyserr(file, line, func, fmt, args);
    va_end(args);
}

void err_pos_remark(const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_pos_vremark(file, line, func, fmt, args);
    va_end(args);
}

void err_pos_sysrem(const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_pos_vsysrem(file, line, func, fmt, args);
    va_end(args);
}

static inline void fmt_args(char *buffer, size_t buflen, const char *fmt, va_list args)
{
    vsnprintf(buffer, buflen, fmt, args);
}

void err_pos_vremark(const char *file, int line, const char *func, const char *fmt, va_list args)
{
    char buffer1[1024];
    snprintf(buffer1, sizeof(buffer1), "%s:%d: %s() - ", file, line, func);
    char buffer2[1024];
    fmt_args(buffer2, sizeof(buffer2), fmt, args);
    err_remark("%s%s", buffer1, buffer2);
}

void err_pos_vsysrem(const char *file, int line, const char *func, const char *fmt, va_list args)
{
    int errnum = errno;
    char buffer1[1024];
    snprintf(buffer1, sizeof(buffer1), "%s:%d: %s() - ", file, line, func);
    char buffer2[1024];
    fmt_args(buffer2, sizeof(buffer2), fmt, args);
    err_remark("%s%s (%d: %s)\n", buffer1, buffer2, errnum, strerror(errnum));
}

NORETURN void err_pos_verror(const char *file, int line, const char *func, const char *fmt, va_list args)
{
    char buffer1[1024];
    snprintf(buffer1, sizeof(buffer1), "%s:%d: %s() - ", file, line, func);
    char buffer2[1024];
    fmt_args(buffer2, sizeof(buffer2), fmt, args);
    err_error("%s%s", buffer1, buffer2);
    exit(EXIT_FAILURE);
}

NORETURN void err_pos_vsyserr(const char *file, int line, const char *func, const char *fmt, va_list args)
{
    int errnum = errno;
    char buffer1[1024];
    snprintf(buffer1, sizeof(buffer1), "%s:%d: %s() - ", file, line, func);
    char buffer2[1024];
    fmt_args(buffer2, sizeof(buffer2), fmt, args);
    err_error("%s%s (%d: %s)\n", buffer1, buffer2, errnum, strerror(errnum));
    exit(EXIT_FAILURE);
}


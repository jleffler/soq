/*
@(#)File:           timespec_io.h
@(#)Purpose:        Convert string to timespec and vice versa
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-2024
@(#)Derivation:     timespec_io.h 3.2 2024/05/07 05:05:02
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_TIMESPEC_IO_H
#define JLSS_ID_TIMESPEC_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

/*
** scn_timespec() reports how many bytes were consumed by the scan.
**       const char str[] = "12.13213";
**       struct timespec ts;
**       int nbytes = scn_timespec(str, &ts);
**       if (nbytes <= 0 || str[nbytes] != '\0')
**           err_error("failed to consume entire string [%s]\n", str);
** The returned length allows you to determine what character caused the
** scan to stop.  As long as a valid time value was read, it will not
** report failure.  A string like "-.123" is valid too; so is "12." and
** the dot is deemed to be consumed.
**
** fmt_timespec() reports how many bytes were written to the buffer, not
** including the terminal null byte.  Errors are reported by returning
** -1, with errno = EINVAL if buffer is null or dp is negative or larger
** than 9, or errno = ENOSPC if buflen is zero or too small.  A return
** value of 0 indicates no valid value was found.  The fraction is
** optional.  Leading white space is skipped.
**
** FMT_TIMESPEC_BUFFER_SIZE is the recommended buffer size - it is big
** enough for a full-size 64-bit signed integer (19 decimal digits) and
** 9 decimal places, plus a negative sign, decimal point and null byte.
**
** NB: It is assumed that negative values are stored with a negative (or zero)
** value for tv_sec and a negative (or zero) value for tv_nsec.  POSIX
** (https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html)
** says in section 2.8.5 Clocks and Timers:
** - The tv_nsec member [of a struct timespec value] is only valid if
**   greater than or equal to zero, and less than the number of
**   nanoseconds in a second (1000 million).  The time interval
**   described by this structure is (tv_sec * 10^9 + tv_nsec)
**   nanoseconds.
** If applied literally to negative values of tv_sec, then a value like
** -1.234 would be represented by tv_sec = -2 and tv_nsec = 766000000.
** This is not coonvenient or easy to understand or print.
*/

enum { FMT_TIMESPEC_BUFFER_SIZE = 32 };

extern int scn_timespec(const char *str, struct timespec *value);
extern int fmt_timespec(const struct timespec *value, int dp, char *buffer, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_TIMESPEC_IO_H */

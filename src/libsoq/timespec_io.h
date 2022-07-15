/*
@(#)File:           timespec_io.h
@(#)Purpose:        Convert string to timespec and vice versa
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-2019
@(#)Derivation:     timespec_io.h 2.2 2019/08/16 05:25:57
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_TIMESPEC_IO_H
#define JLSS_ID_TIMESPEC_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

extern int scn_timespec(const char *str, struct timespec *value);
extern int fmt_timespec(const struct timespec *value, int dp, char *buffer, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_TIMESPEC_IO_H */

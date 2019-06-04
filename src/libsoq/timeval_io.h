/*
@(#)File:           timeval_io.h
@(#)Purpose:        Convert string to timeval and vice versa
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2019
@(#)Derivation:     timeval_io.h 2.1 2019/06/02 05:21:54
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_TIMEVAL_IO_H
#define JLSS_ID_TIMEVAL_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     /* size_t */
#include <sys/time.h>   /* struct timeval */

extern int scn_timeval(const char *str, struct timeval *value);
extern int fmt_timeval(const struct timeval *value, int dp, char *buffer, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_TIMEVAL_IO_H */

/*
@(#)File:           timeval_math.h
@(#)Purpose:        Add, subtract, compare two struct timeval values
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2019-2024
@(#)Derivation:     timeval_math.h 2.2 2024/04/04 03:22:36
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_TIMEVAL_MATH_H
#define JLSS_ID_TIMEVAL_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

extern void sub_timeval(struct timeval t_old, struct timeval t_new, struct timeval *td);
extern void add_timeval(struct timeval t_old, struct timeval t_new, struct timeval *td);
extern int  cmp_timeval(struct timeval t1, struct timeval t2);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_TIMEVAL_MATH_H */

/*
@(#)File:           timeval_math.h
@(#)Purpose:        Add, subtract, compare two struct timeval values
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2019
@(#)Derivation:     timeval_math.h 2.1 2019/06/02 05:22:44
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_TIMEVAL_MATH_H
#define JLSS_ID_TIMEVAL_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

extern void sub_timeval(struct timeval t1, struct timeval t2, struct timeval *td);
extern void add_timeval(struct timeval t1, struct timeval t2, struct timeval *td);
extern int  cmp_timeval(struct timeval t1, struct timeval t2);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_TIMEVAL_MATH_H */

/*
@(#)File:           prng48.h
@(#)Purpose:        Generate pseudo-random integers over a specified range
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Derivation:     prng48.h 1.1 2022/06/25 20:01:11
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_PRNG48_H
#define JLSS_ID_PRNG48_H

/*
** Using nrand48() and a private seed avoids interfering with any other
** PRNG at work.  Using types long and unsigned short matches what POSIX
** says for the types.  The range of values generated is limited to the
** unsigned 31-bit values. Thus the equivalent of RAND_MAX is PRNG48_MAX.
*/

enum { PRNG48_MAX = 0x7FFFFFFF };

extern void prng48_seed(unsigned short[3]);
/* Return random numner in range [lo..hi] */
extern long prng48_rand(long lo, long hi);

#endif /* JLSS_ID_PRNG48_H */

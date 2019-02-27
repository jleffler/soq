/*
@(#)File:           isqrt.h
@(#)Purpose:        Integer square root functions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Derivation:     isqrt.h 1.1 2015/07/11 07:00:48
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_ISQRT_H
#define JLSS_ID_ISQRT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern int32_t isqrt_32(uint32_t x);
extern int64_t isqrt_64(uint64_t x);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_ISQRT_H */

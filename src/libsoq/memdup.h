/*
@(#)File:           memdup.h
@(#)Purpose:        Duplicate a block of memory (analogous to strdup())
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Derivation:     memdup.h 1.1 2017/11/20 06:39:29
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_MEMDUP_H
#define JLSS_ID_MEMDUP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     // size_t

extern void *memdup(const void *mem, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_MEMDUP_H */

/*
@(#)File:           aomcore.h
@(#)Purpose:        Array of Memory Blocks - Core Information
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2023
@(#)Derivation:     aomcore.h 1.2 2023/01/16 20:30:59
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOMCORE_H
#define JLSS_ID_AOMCORE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AoM_Block
{
    size_t  blk_size;
    void   *blk_data;
} AoM_Block;

typedef void (*AoM_SimpleApply)(const AoM_Block *blk);
typedef void (*AoM_ContextApply)(const AoM_Block *blk, void *context);
typedef void (*AoM_PrintData)(FILE *fp, const AoM_Block *blk, void *context);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOMCORE_H */

/*
@(#)File:           aommngd.h
@(#)Purpose:        Array of Memory Blocks - Memory Managed Data
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018-2024
@(#)Derivation:     aommngd.h 1.5 2024/05/20 14:43:13
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOMMNGD_H
#define JLSS_ID_AOMMNGD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>    /* bool */
#include "aomcore.h"    /* (FILE, size_t), AoM_Block, AoM_SimpleApply, AoM_ContextApply, AoM_PrintData */

/*
** The AoM_Managed structure is for an array of memory blocks which
** makes a copy of each memory block it is given to store.  It can
** return a raw pointer to the copy of any memory block which it stored,
** or it can return a copy of the copied memory block when an item is
** extracted.  The aomm_base() method returns the current data uncopied
** (and modifiable), but you are on your honour not to damage that
** array of memory blocks.  The array of memory block pointers is always
** terminated with a null pointer.
*/

typedef struct AoM_Managed AoM_Managed;

typedef AoM_Block (*AoM_BlkCopy)(size_t blk_size, const void *blk_data);
typedef void      (*AoM_BlkFree)(size_t blk_size,       void *blk_data);

extern AoM_Managed *aomm_create(size_t num_ptrs, AoM_BlkCopy copier, AoM_BlkFree release);
extern void aomm_destroy(AoM_Managed *aom);
extern bool aomm_add(AoM_Managed *aom, size_t blk_size, const void *blk_data);
extern bool aomm_set(AoM_Managed *aom, size_t index, size_t blk_size, const void *blk_data);
extern AoM_Block *aomm_base(const AoM_Managed *aom);
extern size_t aomm_length(const AoM_Managed *aom);
extern AoM_Block aomm_item_copy(const AoM_Managed *aom, size_t index);
extern AoM_Block aomm_item(const AoM_Managed *aom, size_t index);
extern void aomm_delete(AoM_Managed *aom, size_t bos, size_t eos);
extern void aomm_apply(const AoM_Managed *aom, size_t bos, size_t eos, AoM_SimpleApply function);
extern void aomm_apply_ctxt(const AoM_Managed *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt);

extern void aomm_dump(FILE *fp, const char *tag, const AoM_Managed *aom, AoM_PrintData printer, void *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOMMNGD */

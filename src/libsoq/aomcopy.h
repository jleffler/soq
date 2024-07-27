/*
@(#)File:           aomcopy.h
@(#)Purpose:        Array of Memory Blocks - Copy Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2024
@(#)Derivation:     aomcopy.h 1.7 2024/05/20 14:43:13
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOMCOPY_H
#define JLSS_ID_AOMCOPY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>    /* bool */
#include "aomcore.h"    /* (FILE, size_t), AoM_Block, AoM_SimpleApply, AoM_ContextApply, AoM_PrintData */

/*
** The AoM_Copy structure is for an array of memory blocks which makes a
** copy of each memory block it is given to store.  It can return a raw
** pointer to the copy of any memory block which it stored, or it can
** return a copy of the copied memory block when an item is extracted.
** The aomc_base() method returns the current data uncopied — and
** modifiable, but you are on your honour not to damage that array of
** memory blocks.  The array of memory block pointers is always
** terminated with a null pointer.
*/

typedef struct AoM_Copy AoM_Copy;

extern AoM_Copy *aomc_create(size_t num_ptrs);
extern void aomc_destroy(AoM_Copy *aom);
extern bool aomc_add(AoM_Copy *aom, size_t blk_size, const void *blk_data);
extern bool aomc_set(AoM_Copy *aom, size_t index, size_t blk_size, const void *blk_data);
extern AoM_Block *aomc_base(const AoM_Copy *aom);
extern size_t aomc_length(const AoM_Copy *aom);
extern AoM_Block aomc_item_copy(const AoM_Copy *aom, size_t index);
extern AoM_Block aomc_item(const AoM_Copy *aom, size_t index);
extern void aomc_delete(AoM_Copy *aom, size_t bos, size_t eos);
extern void aomc_apply(const AoM_Copy *aom, size_t bos, size_t eos, AoM_SimpleApply function);
extern void aomc_apply_ctxt(const AoM_Copy *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt);

extern void aomc_dump(FILE *fp, const char *tag, const AoM_Copy *aom, AoM_PrintData printer, void *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOMCOPY_H */

/*
@(#)File:           aomptr.h
@(#)Purpose:        Array of Memory Blocks - Pointer Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2024
@(#)Derivation:     aomptr.h 1.5 2024/05/20 14:43:13
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOMPTR_H
#define JLSS_ID_AOMPTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>    /* bool */
#include "aomcore.h"    /* (FILE, size_t), AoM_Block, AoM_SimpleApply, AoM_ContextApply, AoM_PrintData */

/*
** The AoM_Pointer structure is for an array of memory blocks which
** saves only a pointer to the start of each memory block and its size;
** it does not copy the data.  It can return a raw pointer to the copy
** of any memory block which it stored, or it can return a copy of the
** copied memory block when an item is extracted.  The aomp_base()
** method returns the current data uncopied — and modifiable, but you
** are on your honour not to damage that array of memory blocks.  The
** array of memory block pointers is always terminated with a null
** pointer.
*/

typedef struct AoM_Pointer AoM_Pointer;

extern AoM_Pointer *aomp_create(size_t num_ptrs);
extern void aomp_destroy(AoM_Pointer *aom);
extern bool aomp_add(AoM_Pointer *aom, size_t blk_size, void *blk_data);
extern bool aomp_set(AoM_Pointer *aom, size_t index, size_t blk_size, void *blk_data);
extern AoM_Block *aomp_base(const AoM_Pointer *aom);
extern size_t aomp_length(const AoM_Pointer *aom);
extern AoM_Block aomp_item_copy(const AoM_Pointer *aom, size_t index);
extern AoM_Block aomp_item(const AoM_Pointer *aom, size_t index);
extern void aomp_delete(AoM_Pointer *aom, size_t bos, size_t eos);
extern void aomp_apply(const AoM_Pointer *aom, size_t bos, size_t eos, AoM_SimpleApply function);
extern void aomp_apply_ctxt(const AoM_Pointer *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt);

extern void aomp_dump(FILE *fp, const char *tag, const AoM_Pointer *aom, AoM_PrintData printer, void *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOMPTR_H */

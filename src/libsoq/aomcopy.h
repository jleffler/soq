/*
@(#)File:           aomcopy.h
@(#)Purpose:        Array of Memory Blocks - Copy Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2018
@(#)Derivation:     aomcopy.h 1.4 2018/06/12 06:10:45
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOMCOPY_H
#define JLSS_ID_AOMCOPY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     /* size_t */
#include <stdbool.h>    /* bool */

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

/* Also in aomptr.h */
#ifndef AOM_BLOCK_DEFINED
typedef struct AoM_Block AoM_Block;
struct AoM_Block
{
    size_t  blk_size;
    void   *blk_data;
};
typedef void (*AoM_SimpleApply)(const AoM_Block *blk);
typedef void (*AoM_ContextApply)(const AoM_Block *blk, void *context);
#define AOM_BLOCK_DEFINED
#endif /* AOM_BLOCK_DEFINED */

typedef struct AoM_Copy AoM_Copy;

extern AoM_Copy *aomc_create(size_t num_ptrs);
extern void aomc_destroy(AoM_Copy *aom);
extern bool aomc_add(AoM_Copy *aom, size_t blk_size, const void *blk_data);
extern bool aomc_set(AoM_Copy *aom, size_t index, size_t blk_size, const void *blk_data);
extern AoM_Block *aomc_base(AoM_Copy *aom);
extern size_t aomc_length(AoM_Copy *aom);
extern AoM_Block aomc_item_copy(AoM_Copy *aom, size_t index);
extern AoM_Block aomc_item(AoM_Copy *aom, size_t index);
extern void aomc_apply(AoM_Copy *aom, size_t bos, size_t eos, AoM_SimpleApply function);
extern void aomc_apply_ctxt(AoM_Copy *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOMCOPY_H */

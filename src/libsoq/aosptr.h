/*
@(#)File:           aosptr.h
@(#)Purpose:        Array of Strings - Pointer Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2023
@(#)Derivation:     aosptr.h 1.4 2023/01/09 23:21:02
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOSPTR_H
#define JLSS_ID_AOSPTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>      /* size_t, FILE */
#include <stdbool.h>    /* bool */

/*
** The AoS_Pointer structure is for an array of strings which saves only
** the pointer it is given to store.  It can return the raw pointer or a
** copy of an item when an item is extracted.  The aosp_base() method
** returns the current data uncopied — and modifiable, but you are on
** your honour not to change that array of strings.  The array of
** strings is always terminated with a null pointer.
*/

typedef struct AoS_Pointer AoS_Pointer;

typedef void (*AoS_SimpleApply)(const char *str);
typedef void (*AoS_ContextApply)(const char *str, void *context);

extern AoS_Pointer *aosp_create(size_t num_ptrs);
extern void aosp_destroy(AoS_Pointer *aos);
extern bool aosp_add(AoS_Pointer *aos, char *str);
extern bool aosp_set(AoS_Pointer *aos, size_t index, char *str);
extern char **aosp_base(const AoS_Pointer *aos);
extern size_t aosp_length(const AoS_Pointer *aos);
extern char *aosp_item_copy(const AoS_Pointer *aos, size_t index);
extern const char *aosp_item(const AoS_Pointer *aos, size_t index);
extern void aosp_delete(AoS_Pointer *aos, size_t lo, size_t hi);
extern void aosp_apply(const AoS_Pointer *aos, size_t bos, size_t eos, AoS_SimpleApply function);
extern void aosp_apply_ctxt(const AoS_Pointer *aos, size_t bos, size_t eos, AoS_ContextApply function, void *ctxt);

extern void aosp_dump(FILE *fp, const char *tag, const AoS_Pointer *aos);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOSPTR_H */

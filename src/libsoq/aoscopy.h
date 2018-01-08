/*
@(#)File:           aoscopy.h
@(#)Purpose:        Array of Strings - Copy Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Derivation:     aoscopy.h 1.4 2017/12/29 00:38:43
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_AOSCOPY_H
#define JLSS_ID_AOSCOPY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     /* size_t */
#include <stdbool.h>    /* bool */

/*
** The AoS_Copy structure is for an array of strings which makes a copy
** of the strings it is given to store.  It can return a raw pointer to
** the copy of the string which it stored, or it can return a copy of
** the copied item when an item is extracted.  The aosc_base() method
** returns the current data uncopied — and modifiable, but you are on
** your honour not to change that array of strings.  The array of
** strings is always terminated with a null pointer (it could be used
** as argv in a call to `execvp()`, for example).
** Each string is always terminated with a null pointer, even when added
** with aosc_addbytes().
** Note that asoc_addbytes() takes a pointer to the start of the string
** and a pointer one beyond the end.
*/

typedef struct AoS_Copy AoS_Copy;

typedef void (*AoS_SimpleApply)(const char *str);
typedef void (*AoS_ContextApply)(const char *str, void *context);

extern AoS_Copy *aosc_create(size_t num_ptrs);
extern void aosc_destroy(AoS_Copy *aos);
extern bool aosc_add(AoS_Copy *aos, const char *str);
extern bool aosc_addbytes(AoS_Copy *aos, const char *str, const char *eos);
extern bool aosc_set(AoS_Copy *aos, size_t index, const char *str);
extern char **aosc_base(AoS_Copy *aos);
extern size_t aosc_length(AoS_Copy *aos);
extern char *aosc_item_copy(AoS_Copy *aos, size_t index);
extern const char *aosc_item(AoS_Copy *aos, size_t index);
extern void aosc_apply(AoS_Copy *aos, size_t bos, size_t eos, AoS_SimpleApply function);
extern void aosc_apply_ctxt(AoS_Copy *aos, size_t bos, size_t eos, AoS_ContextApply function, void *ctxt);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_AOSCOPY_H */

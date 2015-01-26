/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Circular Doubly-Linked List
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Product:        :PRODUCT:
*/

/* SO 28010892 */

/*TABSTOP=4*/

#ifndef JLSS_ID_CIRCULAR_DLL_H
#define JLSS_ID_CIRCULAR_DLL_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_circular_dll_h[];
const char jlss_id_circular_dll_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

typedef struct Circular_DLL Circular_DLL;
typedef void (*CDLL_Apply)(void *data, void *ctxt);
typedef int  (*CDLL_Compare)(const void *data, const void *word);

extern Circular_DLL *cdll_add_after(Circular_DLL *list, void *data);
extern Circular_DLL *cdll_add_before(Circular_DLL *list, void *data);
extern Circular_DLL *cdll_find(Circular_DLL *list, CDLL_Compare function, void *ctxt);
extern Circular_DLL *cdll_next(Circular_DLL *list);
extern Circular_DLL *cdll_prev(Circular_DLL *list);
extern Circular_DLL *cdll_remove(Circular_DLL *list);

extern void *cdll_data(Circular_DLL *list);

extern void cdll_apply(Circular_DLL *list, CDLL_Apply function, void *ctxt);
extern void cdll_destroy(Circular_DLL *list);
extern void cdll_dump_item(FILE *fp, const char *tag, const Circular_DLL *item);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_CIRCULAR_DLL_H */

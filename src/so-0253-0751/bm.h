/*
@(#)File:           $RCSfile: bm.h,v $
@(#)Version:        $Revision: 1.4 $
@(#)Last changed:   $Date: 2015/09/28 02:50:56 $
@(#)Purpose:        Boyer-Moore String Search Algorithm
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005,2008,2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#if !defined(BM_H)
#define BM_H

#if defined(MAIN_PROGRAM)
#if !defined(lint)
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_bm_h[];
const char jlss_id_bm_h[] = "@(#)$Id: bm.h,v 1.4 2015/09/28 02:50:56 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <stddef.h> /* size_t */

typedef struct bm_control bm_control;

/*
** To set up a search (to repeatedly look for the same search string in
** multiple scan strings, use bm_setsearch().  To start a search on a
** new scan string, use bm_settarget().  To find the next match of a
** given search string in a given target string, use bm_search().  Note
** that bm_setsearch() and bm_settarget() do not copy the data in the
** source and target strings; the pointers must remain valid You can
** copy bm_control structures for reuse if desired.
*/

typedef void *(*bm_malloc)(size_t nbytes);
typedef void (*bm_free)(void *data);

extern bm_control *bm_setsearch(const char *search, size_t schlen);
extern void bm_settarget(bm_control *ctrl, const char *target, size_t tgtlen);
extern const char *bm_search(bm_control *ctrl);
extern void bm_release(bm_control *ctrl);
extern void bm_setalloc(bm_malloc mem_alloc, bm_free mem_free);

#endif /* BM_H */

/*
@(#)File:           $RCSfile: kmp.h,v $
@(#)Version:        $Revision: 1.5 $
@(#)Last changed:   $Date: 2013/09/16 02:58:29 $
@(#)Purpose:        Knuth-Morris-Pratt Search Algorithm
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005,2008,2013
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef KMP_H
#define KMP_H

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
const char jlss_id_kmp_h[] = "@(#)$Id: kmp.h,v 1.5 2013/09/16 02:58:29 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <stddef.h> /* size_t */

typedef struct kmp_control kmp_control;

/*
** To set up a search (to repeatedly look for the same search string in
** multiple scan strings), use kmp_setsearch().  To start a search on a
** new scan string, use kmp_settarget().  To find the next match of a
** given search string in a given target string, use kmp_search().  Note
** that kmp_setsearch() and kmp_settarget() do not copy the data in the
** source and target strings; the pointers must remain valid.
**
** Example use:
**
**    char *needle = "needle";
**    char *haystack = read_haystack(input_file_name);
**    kmp_control *kmp = kmp_setsearch(needle, strlen(needle));
**    kmp_settarget(kmp, haystack, strlen(haystack));
**    const char *found;
**    while ((found = kmp_search(kmp)) != 0)
**        printf("Found %s at offset %d\n", needle, found - haystack);
**
*/
typedef void *(*kmp_malloc)(size_t nbytes);
typedef void  (*kmp_free)(void *data);

extern kmp_control *kmp_setsearch(const char *search, size_t schlen);
extern void kmp_settarget(kmp_control *ctrl, const char *target, size_t tgtlen);
extern const char *kmp_search(kmp_control *ctrl);
extern void kmp_release(kmp_control *ctrl);
extern void kmp_setalloc(kmp_malloc mem_alloc, kmp_free mem_free);

#endif /* KMP_H */

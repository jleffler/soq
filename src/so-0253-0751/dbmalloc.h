/*
@(#)File:           $RCSfile: dbmalloc.h,v $
@(#)Version:        $Revision: 4.1 $
@(#)Last changed:   $Date: 2016/01/05 06:48:34 $
@(#)Purpose:        Header for Debugging Malloc
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2002,2005,2008,2013,2016
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef DBMALLOC_H
#define DBMALLOC_H

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
const char jlss_id_dbmalloc_h[] = "@(#)$Id: dbmalloc.h,v 4.1 2016/01/05 06:48:34 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

extern void  db_free(void *vp);
extern void *db_malloc(size_t nbytes);
extern void *db_calloc(size_t n, size_t s);
extern void *db_realloc(void *vp, size_t n);

extern void  db_prt_note(const char *fmt, ...);
extern void  db_dump_malloc(void);
extern void  db_bfree(void *vp, size_t n);

extern FILE *db_malloc_fp(void);

#ifdef DBMALLOC_MAP_STDC
#include <stdlib.h>
#define malloc(size)        db_malloc(size)
#define realloc(ptr, size)  db_realloc(ptr, size)
#define calloc(num, size)   db_calloc(num, size)
#define free(ptr)           db_free(ptr)
#endif /* DBMALLOC_MAP_STDC */

#ifdef __cplusplus
}
#endif

#endif /* DBMALLOC_H */

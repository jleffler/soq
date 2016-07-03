/*
@(#)File:           emalloc.h
@(#)Purpose:        Interfaces to routines in emalloc.c
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990,1992-93,1996-97,2001,2003,2005,2008,2015-16
@(#)Derivation:     emalloc.h,v 5.10 2015/02/17 04:50:35 
*/

/*TABSTOP=4*/

#ifndef EMALLOC_H
#define EMALLOC_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>

/* -- Macro Definitions */

/* Make it easier to avoid using emalloc() et al */
#ifdef USE_REAL_MALLOC
#define MALLOC(n)       malloc((n))
#define CALLOC(n, s)    calloc((n), (s))
#define REALLOC(s, n)   realloc((s), (n))
#define FREE(s)         free((s))
#define STRDUP(s)       strdup((s))
#endif /* USE_REAL_MALLOC */

#ifndef MALLOC
#define MALLOC(n)       emalloc((size_t)(n))
#endif /* MALLOC */

#ifndef CALLOC
#define CALLOC(n, s)    ecalloc((size_t)(n), (size_t)(s))
#endif /* CALLOC */

#ifndef REALLOC
#define REALLOC(s, n)   erealloc((void *)(s), (size_t)(n))
#endif /* REALLOC */

#ifndef FREE
#define FREE(s)         efree((void *)(s))
#endif /* FREE */

#ifndef STRDUP
#define STRDUP(s)       estrdup((s))
#endif /* STRDUP */

#ifndef NOSTRICT
#ifdef lint
#define NOSTRICT(type, exp) ((type)((exp) ? 0 : 0))
#else
#define NOSTRICT(type, exp) ((type)(exp))
#endif
#endif /* NOSTRICT */

/* -- Declarations */

extern void *emalloc(size_t nbytes);
extern void *ecalloc(size_t nitems, size_t size);
extern void *erealloc(void *space, size_t nbytes);
extern void  efree(void *space);
extern char *estrdup(const char *str);

/* Configure 'out of memory' error reporting function */
/* Default corresponds to err_error() from stderr.h */
extern void  emallocerror(void (*function)(const char *));

#endif /* EMALLOC_H */

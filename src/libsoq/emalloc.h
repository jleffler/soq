/*
@(#)File:           emalloc.h
@(#)Purpose:        Interfaces to routines in emalloc.c
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2018
@(#)Derivation:     emalloc.h 5.11 2018/04/15 17:58:22
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

/*
** Once upon a time, when lint was a program, maybe NOSTRICT had a
** purpose, possibly in the days of yore when malloc() returned a char
** pointer and not a void pointer.
** It is now (2018) deemed dead, but the non-lint definition is left in
** place for backwards compatibility.  It should not be used in new code
** and should be removed from old code when it is updated.
*/

/* -- Declarations */

extern void *emalloc(size_t nbytes);
extern void *ecalloc(size_t nitems, size_t size);
extern void *erealloc(void *space, size_t nbytes);
extern void  efree(void *space);
extern char *estrdup(const char *str);

#endif /* EMALLOC_H */

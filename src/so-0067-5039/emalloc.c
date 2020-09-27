/*
@(#)File:           emalloc.c
@(#)Purpose:        More secure memory allocation
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1989-2018
@(#)Derivation:     emalloc.c 5.14 2018/04/15 17:56:53
*/

/*TABSTOP=4*/

#include "emalloc.h"
#include "debug.h"
#include "stderr.h"
#include <inttypes.h>
#include <stdlib.h>

/*
**  Note: under normal circumstances
**      MALLOC  <=> emalloc  <=> malloc
**      REALLOC <=> erealloc <=> realloc
**      FREE    <=> efree    <=> free
**  Under error conditions, the behaviour of these routines is different:
**  1.  FREE    does no damage when given a null pointer
**  2.  REALLOC does no damage when given a null pointer
**  3.  REALLOC does an error exit if it fails to allocate memory
**  4.  MALLOC  does an error exit if it fails to allocate memory
*/

static unsigned long counter = 1;
static const char sz_format[] = "%07lu:%-17s: 0x%08" PRIXPTR " %8zu\n";
static const char pt_format[] = "%07lu:%-17s: 0x%08" PRIXPTR "\n";

static NORETURN void err_reporter(size_t size)
{
    DB_TRACKING();
    err_error("out of memory allocating %zu bytes\n", size);
}

/* Secure memory allocation */
void *emalloc(size_t u)
{
    void           *cp;

    if ((cp = malloc(u)) == 0)
        err_reporter(u);
    DB_TRACE(10, sz_format, counter++, "emalloc", (uintptr_t)cp, u);
    return(cp);
}

/* Secure allocation of zeroed memory */
void *ecalloc(size_t n, size_t s)
{
    void           *cp;

    if ((cp = calloc(n, s)) == 0)
        err_reporter(n * s);
    DB_TRACE(10, sz_format, counter++, "ecalloc", (uintptr_t)cp, n * s);
    return(cp);
}

/* Secure memory re-allocation */
void *erealloc(void *s, size_t n)
{
    void           *cp;

    if (s == 0)
    {
        cp = malloc(n);
        DB_TRACE(10, sz_format, counter++, "erealloc-malloc", (uintptr_t)cp, n);
    }
    else
    {
        DB_TRACE(10, pt_format, counter++, "erealloc-realloc1", (uintptr_t)s);
        cp = realloc(s, n);
        DB_TRACE(10, sz_format, counter++, "erealloc-realloc2", (uintptr_t)cp, n);
    }

    if (cp == 0)
        err_reporter(n);

    return(cp);
}

/* Secure memory de-allocation */
void efree(void *s)
{
    if (s != 0)
    {
        DB_TRACE(10, pt_format, counter++, "efree", (uintptr_t)s);
        free(s);
    }
}

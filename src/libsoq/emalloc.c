/*
@(#)File:           emalloc.c
@(#)Purpose:        More secure memory allocation
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1989-93,1996-97,2003,2005,2008,2015-16
@(#)Derivation:     emalloc.c 5.13 2016/01/17 16:05:58
*/

/*TABSTOP=4*/

#include "emalloc.h"
#include "debug.h"
#include "stderr.h"
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

static void err_reporter(const char *);
static void (*err_function)(const char *) = err_reporter;

static const char no_memory[] = "out of memory\n";

static unsigned long counter = 1;
static const char sz_format[] = "%07lu:%-17s: 0x%08X %8lu\n";
static const char pt_format[] = "%07lu:%-17s: 0x%08X\n";

static NORETURN void err_reporter(const char *str)
{
    DB_TRACKING();
    err_error("%s", str);
}

void emallocerror(void (*function)(const char *))
{
    err_function = function;
}

/* Secure memory allocation */
void *emalloc(size_t u)
{
    void           *cp;

    if ((cp = malloc(u)) == 0)
        (*err_function)(no_memory);
    DB_TRACE(10, sz_format, counter++, "emalloc", cp, u);
    return(cp);
}

/* Secure allocation of zeroed memory */
void *ecalloc(size_t n, size_t s)
{
    void           *cp;

    if ((cp = calloc(n, s)) == 0)
        (*err_function)(no_memory);
    DB_TRACE(10, sz_format, counter++, "ecalloc", cp, n * s);
    return(cp);
}

/* Secure memory re-allocation */
void *erealloc(void *s, size_t n)
{
    void           *cp;

    if (s == 0)
    {
        cp = malloc(n);
        DB_TRACE(10, sz_format, counter++, "erealloc-malloc", cp, n);
    }
    else
    {
        DB_TRACE(10, pt_format, counter++, "erealloc-realloc1", s);
        cp = realloc(s, n);
        DB_TRACE(10, sz_format, counter++, "erealloc-realloc2", cp, n);
    }

    if (cp == 0)
        (*err_function)(no_memory);

    return(cp);
}

/* Secure memory de-allocation */
void efree(void *s)
{
    if (s != 0)
    {
        DB_TRACE(10, pt_format, counter++, "efree", s);
        free(s);
    }
}

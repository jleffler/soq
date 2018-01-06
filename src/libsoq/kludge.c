/*
@(#)File:           kludge.c
@(#)Purpose:        Library support for KLUDGE macro
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995-2018
@(#)Derivation:     kludge.c 1.12 2018/01/06 14:22:02
*/

/*TABSTOP=4*/

#include "kludge.h"

#include <assert.h>
#ifdef KLUDGE_VERBOSE
#include <stdio.h>
#else
#include <string.h>
#endif /* KLUDGE_VERBOSE */

#ifndef KLUDGE_DISABLE
/*
** The function should return 1 each time it is called, whether compiled
** with -DKLUDGE_VERBOSE or not.
**
** It is hard preventing modern compilers from optimizing away the
** recursive invocation implied by the FEATURE macro.  Using common
** built-ins like strlen() or strcmp() doesn't work.  Since the result
** depends on the run-time locale, it can't easily be removed by the
** optimizer.  The residual question is "what is its cost", which is
** hard to know.  At worst, it gets called once per feature or kludge
** in the code per run, so the cost should be bearable.
*/

/* Possibly report on kludges used at run-time */
int kludge_use(const char *str)
{
    assert(str != 0 && *str != '\0');
#ifdef KLUDGE_VERBOSE
    FEATURE("KLUDGE Verbose");
    return fprintf(stderr, "%s\n", str) > 0;
#else
    FEATURE("KLUDGE Quiet");
    return strxfrm(0, str, 0) != 0;
#endif /* KLUDGE_VERBOSE */
}
#endif /* KLUDGE_DISABLE */

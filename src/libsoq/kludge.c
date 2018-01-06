/*
@(#)File:           kludge.c
@(#)Purpose:        Library support for KLUDGE macro
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995-2017
@(#)Derivation:     kludge.c 1.11 2017/11/16 01:39:42
*/

/*TABSTOP=4*/

#ifdef KLUDGE_VERBOSE
#include <stdio.h>
#else
#include <string.h>
#endif /* KLUDGE_VERBOSE */

#include "kludge.h"

/* Report on kludges used at run-time */
void kludge_use(const char *str)
{
#ifdef KLUDGE_VERBOSE
    /* Condition is vacuous, but prevents jlss_id_kludge_c from being optimized away */
    if (jlss_id_kludge_c != 0)
    {
        FEATURE("KLUDGE Verbose");
        fprintf(stderr, "%s\n", str);
    }
#else
    if (jlss_id_kludge_c != (char *)0)
    {
        FEATURE("KLUDGE Quiet");
        (void)strcmp(str, jlss_id_kludge_c);
    }
#endif /* KLUDGE_VERBOSE */
}

/*
@(#)File:           kludge.c
@(#)Purpose:        Library support for KLUDGE macro
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995,1997-98,2003,2005,2015-16
@(#)Derivation:     kludge.c 1.10 2015/02/21 06:21:52
*/

/*TABSTOP=4*/

#ifdef KLUDGE_VERBOSE
#include <stdio.h>
#else
#include <string.h>
#endif /* KLUDGE_VERBOSE */

#include "kludge.h"

static const char jlss_id_kludge_c[] = "@(#)kludge.c";

/* Report on kludges used at run-time */
void kludge_use(const char *str)
{
#ifdef KLUDGE_VERBOSE
    /* Condition is vacuous, but prevents jlss_id_kludge_c from being optimized away */
    if (jlss_id_kludge_c != 0)
        fprintf(stderr, "%s\n", str);
#else
    if (jlss_id_kludge_c != (char *)0)
        (void)strcmp(str, jlss_id_kludge_c);
#endif /* KLUDGE_VERBOSE */
}

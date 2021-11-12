/*
@(#)File:           estrdup.c
@(#)Purpose:        Simulate STRDUP(3) with error exit on
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2001,2005,2008,2015
@(#)Derivation:     estrdup.c 5.7 2015/06/02 03:05:40
*/

/*TABSTOP=4*/

#include "emalloc.h"
#include <string.h>

char *estrdup(char const *s)
{
    const char *src = s ? s : "";
    char *dst = (char *)MALLOC(strlen(src) + 1);    /*=C++=*/
    strcpy(dst, src);
    return(dst);
}

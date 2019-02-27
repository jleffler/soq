/*
@(#)File:           memdup.c
@(#)Purpose:        Duplicate a block of memory (analogous to strdup())
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Derivation:     memdup.c 1.1 2017/11/20 06:39:29
*/

/*TABSTOP=4*/

#include "memdup.h"
#include <stdlib.h>
#include <string.h>

void *memdup(const void *mem, size_t len)
{
    void *copy = malloc(len);
    if (copy != 0)
        memmove(copy, mem, len);
    return copy;
}

#ifdef TEST
#error No test written
#endif

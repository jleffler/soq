/*
@(#)File:           lib1b.c
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     lib1b.c 1.2 2016/01/17 00:25:46
*/

#include <stdio.h>
#include "lib1.h"
#include "lib2.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_lib1b_c[];
const char jlss_id_lib1b_c[] = "@(#)$Id: lib1b.c,v 1.2 2016/01/17 00:25:46 jleffler Exp $";
#endif /* lint */

void def_345(int i)
{
    printf("Library 1:%s:%d-->>%s() - %d\n", __FILE__, __LINE__, __func__, i);
    ghi_678(i+10);
    printf("Library 1:%s:%d<<--%s() - %d\n", __FILE__, __LINE__, __func__, i);
}

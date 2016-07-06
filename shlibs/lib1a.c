/*
@(#)File:           $RCSfile: lib1a.c,v $
@(#)Version:        $Revision: 1.2 $
@(#)Last changed:   $Date: 2016/01/17 00:25:46 $
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
*/

#include <stdio.h>
#include "lib1.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_lib1a_c[];
const char jlss_id_lib1a_c[] = "@(#)$Id: lib1a.c,v 1.2 2016/01/17 00:25:46 jleffler Exp $";
#endif /* lint */

void abc_123(int i)
{
    printf("Library 1:%s:%d:%s() - %d\n", __FILE__, __LINE__, __func__, i);
    printf("Note this extra message\n");
}

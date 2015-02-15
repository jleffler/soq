/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014
*/

#include <stdio.h>
#include "lib1.h"

void abc_123(int i)
{
    printf("Library 1:%s:%d:%s() - %d\n", __FILE__, __LINE__, __func__, i);
    printf("Note this extra message\n");
}

/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014
@(#)Product:        :PRODUCT:
*/

#include <stdio.h>
#include "lib2.h"

void abc_123(int i)
{
    printf("Library 2:%s:%d:%s() - %d\n", __FILE__, __LINE__, __func__, i);
    printf("This is a completely different message\n");
}

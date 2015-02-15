/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014
*/

#include <stdio.h>
#include "lib2.h"

void ghi_678(int i)
{
    printf("Library 2:%s:%d-->>%s() - %d\n", __FILE__, __LINE__, __func__, i);
    abc_123(i * 10);
    printf("Library 2:%s:%d<<--%s() - %d\n", __FILE__, __LINE__, __func__, i);
}

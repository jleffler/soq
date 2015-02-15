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
#include "lib1.h"
#include "lib2.h"

void def_345(int i)
{
    printf("Library 1:%s:%d-->>%s() - %d\n", __FILE__, __LINE__, __func__, i);
    ghi_678(i+10);
    printf("Library 1:%s:%d<<--%s() - %d\n", __FILE__, __LINE__, __func__, i);
}

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

int main(void)
{
    printf("Cross-library linking and calling\n");
    printf("Main calling abc_123(29)\n");
    abc_123(29);
    printf("Main calling def_345(45)\n");
    def_345(45);
    printf("Main calling ghi_678(57)\n");
    ghi_678(57);
    printf("Demonstration over\n");
    return 0;
}

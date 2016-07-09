/*
@(#)File:           test1.c
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     test1.c 1.2 2016/01/17 00:28:29
*/

#include <stdio.h>
#include "lib1.h"
#include "lib2.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_test1_c[];
const char jlss_id_test1_c[] = "@(#)$Id: test1.c,v 1.2 2016/01/17 00:28:29 jleffler Exp $";
#endif /* lint */

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

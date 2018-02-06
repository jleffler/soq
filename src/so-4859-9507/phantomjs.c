/*
@(#)File:           $RCSfile: alev.c,v $
@(#)Version:        $Revision: 1.2 $
@(#)Last changed:   $Date: 2016/01/17 19:03:09 $
@(#)Purpose:        List command name, arguments and environment, one per line, and standard input
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014-2018
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include <stdio.h>

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_alev_c[];
const char jlss_id_alev_c[] = "@(#)$Id: alev.c,v 1.2 2016/01/17 19:03:09 jleffler Exp $";
#endif /* lint */

int main(int argc, char **argv, char **envp)
{
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = <<%s>>\n", i, argv[i]);
    for (int i = 0; envp[i] != 0; i++)
        printf("envp[%d] = <<%s>>\n", i, envp[i]);
    FILE *fp = fopen(argv[argc - 1], "r");
    if (fp != 0)
    {
        int c;
        while ((c = getc(fp)) != EOF)
            putchar(c);
    }
    else
        fprintf(stderr, "failed to open file %s for reading\n", argv[argc-1]);
    return(0);
}

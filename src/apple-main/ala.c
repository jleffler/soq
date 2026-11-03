/*
@(#)Format:         vim: set ts=4 sw=4 et:
@(#)File:           ala.c
@(#)Purpose:        Demonstrate Apple-specific 4-argument main()
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2026
*/

#ifndef __APPLE__
#error "This only works when __APPLE__ is defined"
#endif

#include <stdio.h>

int main(int argc, char **argv, char **envp, char **appv)
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = [[%s]]\n", i, argv[i]);
    for (int i = 0; envp[i] != NULL; i++)
        printf("envp[%d] = [[%s]]\n", i, envp[i]);
    for (int i = 0; appv[i] != NULL; i++)
        printf("appv[%d] = [[%s]]\n", i, appv[i]);
    return 0;
}

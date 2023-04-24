/*
@(#)File:           grpwd43.h
@(#)Purpose:        Generate random password
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2023
@(#)Derivation:     grpwd43.h 1.1 2023/04/24 05:36:16
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_GRPWD43_H
#define JLSS_ID_GRPWD43_H

#include <stddef.h>

extern void gen_random_passwd(size_t length, char buffer[length]);

#endif /* JLSS_ID_GRPWD43_H */

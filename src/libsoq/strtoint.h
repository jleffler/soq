/*
@(#)File:           strtoint.h
@(#)Purpose:        Convert string to int, unsigned or size_t
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018
@(#)Derivation:     strtoint.h 1.1 2018/06/11 00:56:39
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_STRTOINT_H
#define JLSS_ID_STRTOINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* strtoi() and strtoui() - analogues to strtol() and strtoul() */
extern int strtoi(const char *str, char **endptr, int base);
extern unsigned int strtoui(const char *str, char **endptr, int base);

/* strtosize() - analogue to strtol() for size_t */
extern size_t strtosize(const char *data, char **endptr, int base);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_STRTOINT_H */

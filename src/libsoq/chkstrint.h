/*
@(#)File:           chkstrint.h
@(#)Purpose:        Checked string to integer conversions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     chkstrint.h 1.1 2015/11/26 18:40:49
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_CHKSTRINT_H
#define JLSS_ID_CHKSTRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>        /* bool */
#include <stddef.h>         /* size_t */
#include <stdint.h>         /* intmax_t, uintmax_t */

/* chk_strtosize() - reports true for successful conversion */
extern bool chk_strtosize(const char *data, char **eon, int base, size_t *result);
extern bool chk_strtoi(const char *data, char **eon, int base, int *result);
extern bool chk_strtol(const char *data, char **eon, int base, long *result);
extern bool chk_strtoll(const char *data, char **eon, int base, long long *result);
extern bool chk_strtoui(const char *data, char **eon, int base, unsigned int *result);
extern bool chk_strtoul(const char *data, char **eon, int base, unsigned long *result);
extern bool chk_strtoull(const char *data, char **eon, int base, unsigned long long *result);
extern bool chk_strtoimax(const char *data, char **eon, int base, intmax_t *result);
extern bool chk_strtoumax(const char *data, char **eon, int base, uintmax_t *result);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_CHKSTRINT_H */

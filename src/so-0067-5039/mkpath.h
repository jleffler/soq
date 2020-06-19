/*
@(#)File:           mkpath.h
@(#)Purpose:        Create missing directories in given path
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Derivation:     mkpath.h 1.2 2017/07/08 03:35:58
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_MKPATH_H
#define JLSS_ID_MKPATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>      /* mode_t */

/* Create all directories in path */
extern int mkpath(const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_MKPATH_H */

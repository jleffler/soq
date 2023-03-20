/*
@(#)File:           imageprt.h
@(#)Purpose:        Print assembler-style text/hex data dump.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005-2017
@(#)Derivation:     imageprt.h 2017.1 2017/03/25 18:48:50
*/

/*TABSTOP=4*/

#ifndef IMAGEPRT_H
#define IMAGEPRT_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>

/* Do hex/text dump of data to file - compressing repeated output lines */
extern void image_print(FILE *fp, size_t offset, const void *buffer, size_t nbytes);
extern void image_print_compressed(FILE *fp, size_t offset, const void *buffer, size_t nbytes);

#ifdef  __cplusplus
}
#endif

#endif /* IMAGEPRT_H */

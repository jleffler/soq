/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        ?
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_CHECK_CONSERVATION_H
#define JLSS_ID_CHECK_CONSERVATION_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_check_conservation_h[];
const char jlss_id_check_conservation_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <stddef.h>

extern size_t check_conservation(const void *data1, const void *data2,
                                 size_t number, size_t size,
                                 int (*compare)(const void *p1, const void *p2));

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_CHECK_CONSERVATION_H */

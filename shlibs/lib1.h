/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Demo cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_LIB1_H
#define JLSS_ID_LIB1_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_lib1_h[];
const char jlss_id_lib1_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

extern void abc_123(int i);
extern void def_345(int i);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_LIB1_H */

/*
@(#)File:           $RCSfile: lib1.h,v $
@(#)Version:        $Revision: 1.2 $
@(#)Last changed:   $Date: 2016/01/17 00:25:46 $
@(#)Purpose:        Demo cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
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
const char jlss_id_lib1_h[] = "@(#)$Id: lib1.h,v 1.2 2016/01/17 00:25:46 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

extern void abc_123(int i);
extern void def_345(int i);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_LIB1_H */

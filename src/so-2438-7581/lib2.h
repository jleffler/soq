/*
@(#)File:           lib2.h
@(#)Purpose:        Demonstrate cross-library linking
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     lib2.h 1.2 2016/01/17 00:25:46
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_LIB2_H
#define JLSS_ID_LIB2_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_lib2_h[];
const char jlss_id_lib2_h[] = "@(#)$Id: lib2.h,v 1.2 2016/01/17 00:25:46 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

extern void abc_123(int i);
extern void ghi_678(int i);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_LIB2_H */

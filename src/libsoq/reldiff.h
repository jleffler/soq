/*
@(#)File:           reldiff.h
@(#)Purpose:        Relative difference of two floating point numbers
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Derivation:     reldiff.h 1.1 2016/05/09 08:00:19
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_RELDIFF_H
#define JLSS_ID_RELDIFF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_reldiff_h[];
const char jlss_id_reldiff_h[] = "@(#)$Id: reldiff.h,v 1.1 2016/05/09 08:00:19 jleffler Exp $";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <math.h>

static inline double reldiff(double x, double y)
{
    return fabs(x - y) / fmax(fabs(x), fabs(y));
}

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_RELDIFF_H */

/*
@(#)File:           reldiff.h
@(#)Purpose:        Relative difference of two floating point numbers
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016-2017
@(#)Derivation:     reldiff.h 1.2 2017/08/10 14:56:33
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_RELDIFF_H
#define JLSS_ID_RELDIFF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

static inline double reldiff(double x, double y)
{
    double divisor = fmax(fabs(x), fabs(y));
    // If divisor is zero, both x and y are zero, so the difference
    // between them is zero
    if (divisor == 0.0)
        return 0.0;
    return fabs(x - y) / divisor;
}

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_RELDIFF_H */

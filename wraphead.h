/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Wrap a C header in extern "C" { ... } for C++
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2014
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/* Example usage:
**
** #define WRAPPED_HEADER "stderr.h"
** #include "wraphead.h"
*/

#if defined(WRAPPED_HEADER)
#if defined(__cplusplus)
extern "C" {
#endif
#include WRAPPED_HEADER
#if defined(__cplusplus)
}
#endif
#undef WRAPPED_HEADER
#endif /* WRAPPED_HEADER */

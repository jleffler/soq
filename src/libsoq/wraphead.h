/*
@(#)File:           wraphead.h
@(#)Purpose:        Wrap a C header in extern "C" { ... } for C++
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     wraphead.h 1.1 2015/02/16 23:29:47
*/

/*TABSTOP=4*/

/* Yes, the operational code is outside any include guard */
/* This header can be used multiple times in a single TU  */

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
#else
#error Macro WRAPPED_HEADER not set before including file "wraphead.h"
#endif /* WRAPPED_HEADER */

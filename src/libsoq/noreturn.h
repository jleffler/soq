/*
@(#)File:           noreturn.h
@(#)Purpose:        Cover for <stdnoreturn.h>
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Derivation:     noreturn.h 1.3 2015/10/14 23:10:51
*/

/*TABSTOP=4*/

#if !defined(JLSS_ID_NORETURN_H)
#define JLSS_ID_NORETURN_H

/* Protect against stderr.h being included first */
#if !defined(NORETURN)
#if __STDC_VERSION__ >= 201112L
#define NORETURN    _Noreturn
#elif defined(__GNUC__)
#define NORETURN    __attribute__((__noreturn__))
#else
#define NORETURN    /* If only */
#endif /* __STDC_VERSION__ || __GNUC__ */
#endif /* NORETURN */

#endif /* JLSS_ID_NORETURN_H */

/*
@(#)File:           kludge.h
@(#)Purpose:        Provide support for KLUDGE and FEATURE macros
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995-2018
@(#)Derivation:     kludge.h 1.18 2018/01/06 14:38:31
*/

/*TABSTOP=4*/

#ifndef KLUDGE_H
#define KLUDGE_H

/*
 * The KLUDGE and FEATURE macros are enabled by default.
 * They can be disabled by specifying -DKLUDGE_DISABLE
 */

#ifdef KLUDGE_DISABLE

/* Ensure the macros are called with a string literal argument */
#define KLUDGE(x)       assert(sizeof(x "") != 0)
#define FEATURE(x)      assert(sizeof(x "") != 0)
#define KLUDGE_FILE(x)  assert(sizeof(x "") != 0)
#define FEATURE_FILE(x) assert(sizeof(x "") != 0)

#else

/*
** Example use: KLUDGE("Fix macro to accept arguments with commas");
** Note that the argument is now a string.  An alternative (and
** previously used) design is to have the argument as a non-string:
**              KLUDGE(Fix macro to accept arguments with commas);
** This allows it to work with traditional compilers but runs foul of
** the absence of string concatenation, and you have to avoid commas
** in the reason string, etc.
**
** KLUDGE_FILE and FEATURE_FILE include the source file name after the
** main string.
**
** NB: If kludge.c (which defines kludge_use()) is compiled with
**     -DKLUDGE_VERBOSE, then the first time a feature or kludge is
**     used, a message is written to standard error.  The function
**     returns 1, so the reporting process is not repeated (for any
**     given feature or kludge).
*/

#define KLUDGE_ONCE   static int once = 0; if (once++ == 0) once =

#define KLUDGE(x)   { KLUDGE_ONCE kludge_use("@(#)KLUDGE: " x); }
#define FEATURE(x)  { KLUDGE_ONCE kludge_use("@(#)Feature: " x); }

#define KLUDGE_FILE(x)   KLUDGE(x " (" __FILE__ ")")
#define FEATURE_FILE(x)  FEATURE(x " (" __FILE__ ")")

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int kludge_use(const char *str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KLUDGE_DISABLE */

#endif /* KLUDGE_H */

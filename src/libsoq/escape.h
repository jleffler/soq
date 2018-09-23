/*
@(#)File:           escape.h
@(#)Purpose:        Escape a string to protect against shell expansion
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2005,2007-08,2012
@(#)Derivation:     escape.h 1.5 2012/07/22 01:34:03
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_ESCAPE_H
#define JLSS_ID_ESCAPE_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stddef.h> /* size_t */

/*
** escape() is not thread-safe and not re-entrant.  It always escapes
** the argument. escape() returns a pointer to space which it manages
** (initially statically allocated; dynamically allocated if there isn't
** enough space in the static buffer) and reuses it on subsequent calls.
*/
extern char *escape(const char *s);

/*
** Thread-safe, re-entrant alternatives to classic escape() function.
** escape_always() - escapes every string, putting single quote at start
**                   and end, and replaces single quotes with quote,
**                   backslash, quote, quote, just like the classic
**                   escape() does.
** escape_simple() - escapes a string only if it contains any characters
**                   outside the set [-A-Za-z0-9_.,/] (basic file names
**                   are left unescaped), which is found in escape_ok[].
** escape_chosen() - escapes a string only if it contains any characters
**                   outside the set specified as OK.  It ignores
**                   attempts to claim that control characters, spaces
**                   or backslashes are OK.
** escape_always() is implemented as: escape_chosen(src, "", buffer, buflen);
** escape_simple() is implemented as: escape_chosen(src, escape_ok, buffer, buflen);
*/
extern size_t escape_always(const char *src, char *buffer, size_t buflen);
extern size_t escape_simple(const char *src, char *buffer, size_t buflen);
extern size_t escape_chosen(const char *src, const char *ok, char *buffer, size_t buflen);

extern const char escape_ok[];

#ifdef  __cplusplus
}
#endif

#endif /* JLSS_ID_ESCAPE_H */

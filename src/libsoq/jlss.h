/*
@(#)File:           jlss.h
@(#)Purpose:        JLSS Library Functions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1997-2001,2003-05,2008-13,2015-16
@(#)Derivation:     jlss.h 2015.6 2015/11/26 18:41:52
*/

/*TABSTOP=4*/

#ifndef JLSS_H
#define JLSS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "posixver.h"
#include <stdio.h>
#include <sys/types.h>  /* mode_t */
#include <stdbool.h>    /* ?OK? */

#ifndef HAVE_MEMMEM
/* Found on Linux, AIX and MacOS X Lion (10.7) */
/* memmem() -- search for byte pattern in memory */
/* m1, l1: Block to be searched (haystack); m2, l2: Pattern to be searched for (needle) */
extern void *memmem(const void *m1, size_t l1, const void *m2, size_t l2);
#endif /* HAVE_MEMMEM */

#ifndef HAVE_STRNLEN
/* Defined by POSIX 2008 - available on GNU/Linux and Mac OS X Yosemite (10.10) */
extern size_t strnlen(const char *str, size_t len);
#endif /* HAVE_STRNLEN */

#ifndef HAVE_STRNDUP
/* Defined by POSIX 2008 - available on GNU/Linux and Mac OS X Yosemite (10.10) */
extern char *strndup(const char *str, size_t len);
#endif /* HAVE_STRNDUP */

/* Open temporary file via mkstemp() - read/write - name ends XXXXXX */
extern FILE *fmkstemp(char *name);
/* Open file or quit on failure */
extern FILE *efopen(const char *name, const char *mode);
/* Case-insensitive string search */
extern const char *cistrstr(const char *s1, const char *s2);
/* Case-insensitive string compare */
extern int  cistrcmp(const char *s1, const char *s2);
/* Case-insensitive length-limited string compare */
extern int  cistrncmp(const char *s1, const char *s2, size_t len);

/* Destructively convert string into tokens */
extern int tokenise(char *str, char *sep, char **token, int maxtok, int nulls);
/* Copy contents of file1 to file2 */
extern void fcopy(FILE *f1, FILE *f2);
/* Read line of data - prefix avoids conflict with POSIX 2008 getline() */
extern int jlss_getline(FILE *fp, char *buffer, size_t buflen);

/* strncpy() except for argument order and guaranteed null terminated */
/* Argument order is different to ensure you call the function you mean! */
extern void nstrcpy(char *dst, size_t sz, const char *src);

/* Concatenate variable number of strings */
extern char *vstrcpy(char *dst, int n, ...);

/* Concatenate variable number of strings into sized target string */
extern char *nvstrcpy(char *tgt, size_t sz, int n, ...);

/* Case-convert strings in situ.  Return pointer to terminal null character */
extern char *strupper(char *s);
extern char *strlower(char *s);

/* Test for prefix of string */
extern int strprefix(const char *prefix, const char *str);

/* Capitalize first character; convert rest to lower case */
extern char *strcapital(char *s);

/* Insert string t in front of string s in string s */
extern char *strinsert(char *s, const char *t);

/* Create all directories in path */
extern int mkpath(const char *path, mode_t mode);

/* Convert C String Literal in (str..end] (excluding surrounding quotes) */
/* to string, returning length of string, or -1 if conversion error, or */
/* -2 if there is not enough room for the output */
extern int cstrlit_str(const char *str, const char *end, char *buffer, size_t buflen);
/* Convert C Character Literal in (str..end] (excluding surrounding quotes) */
/* to character, returning converted char or -1 if string is invalid. */
/* If non-null, eptr is set to first non-converted (or non-convertible) character */
extern int cstrlit_chr(const char *str, const char *end, char const ** const eptr);

/* Convert character to C Character Literal. */
/* buffer[0] = '\0' if there isn't enough room in buffer */
extern void chr_cstrlit(unsigned char c, char *buffer, size_t buflen);
/* Convert string to C String Literal */
extern void str_cstrlit(const char *str, char *buffer, size_t buflen);

/* Convert character [0-9a-zA-Z] to digit in given base (2-36), */
/* returning -1 for invalid bases and characters. */
extern int basedigit(char c, int base);

/* JLSS-specific variant on basename() */
extern const char *jlss_basename(const char *s);
/* JLSS-specific variant on dirname().  Not thread-safe. */
/* It allocates but never frees memory (without leaking). */
extern const char *jlss_dirname(const char *s);

/* strtoi() and strtoui() - analogues to strtol() and strtoul() */
extern int strtoi(const char *str, char **endptr, int base);
extern unsigned int strtoui(const char *str, char **endptr, int base);
/* strtosize() - analogue to strtol() for size_t */
extern size_t strtosize(const char *data, char **endptr, int base);

#endif /* JLSS_H */

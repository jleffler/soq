/*
@(#)File:           jlss-getopt.h
@(#)Purpose:        Declarations for jlss_getopt(3) and jlss_getsubopt(3)
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1992-2024
@(#)Derivation:     jlss-getopt.h 2024.1 2024/05/31 19:02:18
*/

#ifndef JLSS_GETOPT_H
#define JLSS_GETOPT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

/* Note that POSIX says getopt() returns -1 rather than EOF */
#include <stdio.h>  /* Declares getopt() and getsubopt() on Solaris 7, 8 */
#ifdef HAVE_UNISTD_H
#include <unistd.h> /* Declares getopt() under SUS v3 aka POSIX 1003.1 2001 */
#endif /* HAVE_UNISTD_H */
#include <stdlib.h> /* Declares getsubopt() under SUS v3 aka POSIX 1003.1 2001 */

/* With file renaming, always use JLSS variants */
#undef USE_JLSS_GETOPT
#define USE_JLSS_GETOPT
#undef USE_JLSS_GETSUBOPT
#define USE_JLSS_GETSUBOPT

/*
** GNU getopt (and JLSS getopt, which is built on an ancient GNU getopt)
** provides facilities not available in standard getopt.  Specifically, it
** will reorder all option arguments before all non-option arguments unless
** the environment variable POSIXLY_CORRECT is defined (or if the first
** character in the option string is '+').  It can also handle optional
** arguments, which must be attached to option letter on the command line,
** indicated by two colons after the option letter.  It can be told to
** return all arguments in order, with a value of '\0' indicating a file
** option by starting the options string with a '-'.  If the first argument
** of the option string is ':', it permutes the arguments even if
** POSIXLY_CORRECT is set.  It also has a different interface from standard
** getopt because the second (argv) argument is not const.
*/

/*
** Go with POSIX-compliant declarations for getopt() and getsubopt().
** Note, however, that at various times past, declaring either getopt() or
** getsubopt() has proven incredibly problematic, with varying alternative
** headers declaring them with varying feature test macros and with varying
** degrees of constness in the arguments.
**
** Note that on Linux, <unistd.h> includes <getopt.h>, which may pick up
** this header.  For our immediate purposes, where no code uses GNU's
** getopt_long(), it is sufficient for this code to always define getopt()
** and its global variables.  Of course, GNU's <getopt.h> does not declare
** getsubopt().
**
** NB: AIX 7.2 and XLC 13.1.3 complain about #pragma GCC.  Hence the
** conditional compilation around the #pragma lines - but you begin to
** wonder if the freedom from compilation warnings is worth the effort.
** Heresy? Almost!
*/

#define GETOPT(argc, argv, opts)    jlss_getopt(argc, argv, opts)
#define opterr  jlss_opterr
#define optind  jlss_optind
#define optarg  jlss_optarg
#define optopt  jlss_optopt
extern int jlss_getopt(int argc, char **argv, const char *opts);

/* NB: names mapped above */
extern int   optopt;
extern int   opterr;
extern int   optind;
extern char *optarg;

#define GETSUBOPT(argc, argv, opts) jlss_getsubopt(argc, argv, opts)
extern int jlss_getsubopt(char **opt, char * const *names, char **value);

#endif /* JLSS_GETOPT_H */

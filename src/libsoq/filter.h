/*
@(#)File:           filter.h
@(#)Purpose:        Header for filter functions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1993,1995-98,2003-04,2006,2008,2014-15
@(#)Derivation:     filter.h 2015.2 2015/02/17 04:51:48
*/

/*TABSTOP=4*/

#ifndef FILTER_H
#define FILTER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>

/* Classic mode - not recommended for new programs */
/* Non-const file name; no error status feedback */
/* Source: filter.c */
typedef void (*ClassicFilter)(FILE *ifp, char *fn);
extern void filter(int argc, char **argv, int optnum, ClassicFilter function);

/* No file name at all; no error status feedback */
/* Source: filtera.c */
typedef void (*ClassicFilterAnon)(FILE *ifp);
extern void filter_anon(int argc, char **argv, int optnum, ClassicFilterAnon function);

/* Modern mode 1 - without output file specified */
/* Source: stdfilter.c */
typedef int (*StdoutFilter)(FILE *ifp, const char *fn);
extern int filter_stdout(int argc, char **argv, int optnum, StdoutFilter function);

/* Modern mode 1 - without output file specified */
/* Source: stdfiltera.c */
typedef int (*StdoutFilterAnon)(FILE *ifp);
extern int filter_stdout_anon(int argc, char **argv, int optnum, StdoutFilterAnon function);

/* Modern mode 2 - with output file specified */
/* NB: OutputFilter is compatible with AFF code */
/* Source: outfilter.c */
typedef int (*OutputFilter)(FILE *ifp, const char *fn, FILE *ofp);
extern int filter_output(int argc, char **argv, int optnum, OutputFilter function);

/* Modern mode 2 - with output file specified */
/* Source: outfiltera.c */
typedef int (*OutputFilterAnon)(FILE *ifp, FILE *ofp);
extern int filter_output_anon(int argc, char **argv, int optnum, OutputFilterAnon function);

/* Set output file for filter_output() and filter_output_anon() */
/* Returns previous value of the file (does not set new value if passed null pointer). */
/* Source: outfilterso.c */
extern FILE *filter_setoutput(FILE *out);

/* Standard I/O error check code */
/* Used internally by filter_stdout(), filter_stdout_anon(), filter_output() and filter_output_anon(). */
/* Not normally used by client programs. */
/* Source: filterio.c */
extern int filter_io_check(FILE *ifp, const char *ifn, FILE *ofp);

/*
** Number of files to process: enables support for grep-like prefixing
** of output with file name - or not.
** To print file names before output lines, use:
**    if (filter_numfiles() > 1)
**        printf("%s:%s\n", filename, line);
**    else
**        puts(line);
** Call filter_setnumfiles(0) to reset to default state (seldom needed).
** Call filter_setnumfiles(1) to suppress headings (grep -h).
** Call filter_setnumfiles(2) to force headings (grep -H).
** Source: filterio.c
*/
extern int filter_numfiles(void);
extern void filter_setnumfiles(int num);

#endif /* FILTER_H */

/*
@(#)File:           filter.c
@(#)Purpose:        Classic File Filter
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1987-89,1991,1993,1996-99,2002-05,2008,2012,2014-15
@(#)Derivation:     filter.c 2015.2 2015/02/17 04:53:03
*/

/*TABSTOP=4*/

#include "filter.h"
#include "stderr.h"
#include <string.h>
#include <errno.h>

static char  dash[] = "-";
static char *no_args[] = { dash, 0 };
static const char em_invoptnum[] = "invalid (negative) option number";

/*
    Purpose:    Classic File Filter

    Maintenance Log
    ---------------
    09/03/1987  JL    Original version stabilised
    18/04/1988  JL    Now pass fp and file name to function
    15/12/1991  JL    Upgrade for ANSI C
    29/06/1993  JL    Rename to filter and accept optind argument
    15/10/1996  JL    Remove non-ANSI support and ffilter(); rename file
    31/03/1998  JL    Add support for continuing on error opening a file
    22/08/2003  JL    Remove filter_setcontinue - always continue on error.
    18/12/2004  JL    Rename Filter to ClassicFilter; do not modify argv.
    27/12/2014  JL    Support filter_numfiles()

    Arguments
    ---------
    argc            In: Number of arguments
    argv            In: Argument list of program
    optind          In: Offset in list to start at
    function        In: Function to process file

    Comments
    --------
    1.  For every non-flag option in the argument list, or standard input
        if there are no non-flag arguments, run 'function' on file.
    2.  If a file name is '-', use standard input.
    3.  The optnum argument should normally be the value of optind as
        supplied by getopt(3).  But it should be the index of the first
        non-flag argument.

*/

void filter(int argc, char **argv, int optnum, ClassicFilter function)
{
    int   i;
    FILE *fp;

    if (optnum < 0)
        err_abort(em_invoptnum);
    else if (optnum >= argc)
    {
        argc = 1;
        argv = no_args;
        optnum = 0;
    }
    filter_setnumfiles(argc - optnum);

    for (i = optnum; i < argc; i++)
    {
        if (strcmp(argv[i], "-") == 0)
        {
            char name[] = "(standard input)";
            (*function)(stdin, name);
        }
        else if ((fp = fopen(argv[i], "r")) != NULL)
        {
            (*function)(fp, argv[i]);
            fclose(fp);
        }
        else
            err_sysrem("failed to open file %s\n", argv[i]);
    }
}

#ifdef TEST

/*
** Test program
** -- with no arguments, copies named files to standard output
** -- with -v argument, makes non-printing characters visible
** -- with -V argument, prints version information
*/

#include <ctype.h>
#include <unistd.h>

static void fcopy(FILE *f1, FILE *f2)
{
    char   buffer[BUFSIZ];
    size_t n;

    while ((n = fread(buffer, sizeof(char), sizeof(buffer), f1)) > 0)
    {
        if (fwrite(buffer, sizeof(char), n, f2) != n)
            err_error("write failed\n");
    }
}

static void vis(FILE *fp, char *fn)
{
    int c;

    fprintf(stdout, "%s:\n", fn);
    while ((c = getc(fp)) != EOF)
    {
        if (c == '\n' || c == '\t')
            putchar(c);
        else if (c > 127 || !isprint(c))
            printf("\\%03o", c);
        else
            putchar(c);
    }
}

static void cat(FILE *fp, char *fn)
{
    fprintf(stdout, "%s:\n", fn);
    fcopy(fp, stdout);
}

int main(int argc, char **argv)
{
    int             opt;
    ClassicFilter   f = cat;

    err_setarg0(argv[0]);
    opterr = 0;
    while ((opt = getopt(argc, argv, "Vv")) != EOF)
    {
        if (opt == 'v')
            f = vis;
        else if (opt == 'V')
            err_version("FILTER", "$Revision: 2015.2 $ ($Date: 2015/02/17 04:53:03 $)");
        else
            err_usage("[-vV] [file ...]");
    }
    filter(argc, argv, optind, f);
    return(0);
}

#endif /* TEST */

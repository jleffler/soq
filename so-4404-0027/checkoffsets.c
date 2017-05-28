/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Check reported offsets
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "filter.h"
#include "stderr.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

/* U+2713 is a tick (check mark); U+2715 is a cross */

static const char optstr[] = "hVf:v";
static const char usestr[] = "[-hvV] -f reference [offset-file ...]";
static const char hlpstr[] = 
    "  -f  reference  Search in this file\n"
    "  -h             Print this help message and exit\n"
    "  -v             Verbose mode\n"
    "  -V             Print version information and exit\n"
    ;

enum { MAX_WORD_LEN = 256 };

static FILE *ref;
static const char *reference = 0;
static bool verbose = false;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_checkoffsets_c[];
const char jlss_id_checkoffsets_c[] = "@(#)$Id$";
#endif /* lint */

static int check_offsets(FILE *fp, const char *fn)
{
    char *buffer = 0;
    size_t buflen = 0;
    ssize_t linelen;
    size_t lineno = 0;
    char scanfmt[16];
    sprintf(scanfmt, "%%%ds%%n", MAX_WORD_LEN - 1);

    err_remark("scan format [%s]\n", scanfmt);

    while ((linelen = getline(&buffer, &buflen, fp)) != -1)
    {
        lineno++;
        buffer[linelen-1] = '\0';
        int wordlen;
        char word[MAX_WORD_LEN];
        if (sscanf(buffer, scanfmt, word, &wordlen) != 1)
            err_error("No word on line %zu of '%s' [%s]\n", lineno, fn, buffer);
        if (wordlen >= MAX_WORD_LEN - 1)
            err_error("word '%s' is longer than expected/allowed\n", word);
        char *bufpos = buffer + wordlen;
        int offset;
        int eon;
        if (verbose)
            printf("%s: ", word);
        while (sscanf(bufpos, "%d%n", &offset, &eon) == 1)
        {
            char inword[MAX_WORD_LEN];
            if (fseek(ref, offset, SEEK_SET) != 0)
                err_syserr("failed to seek to offset %d in '%s'\n",
                           offset, reference);
            if (fread(inword, wordlen, 1, ref) != 1)
                err_syserr("read error for %d bytes at offset %d in '%s'\n",
                           wordlen, offset, reference);
            inword[wordlen] = '\0';
            if (strcasecmp(word, inword) != 0)
            {
                if (verbose)
                    printf("(\u2715%d)", offset);
                else
                {
                    printf("Word mismatch - wanted '%s' actual '%s' at offset %d in '%s'\n",
                           word, inword, offset, reference);
                    printf("    line %zu of '%s': %s\n", lineno, fn, buffer);
                }
            }
            else if (verbose)
                printf("(\u2713%d)", offset);
            bufpos += eon;
        }
        if (verbose)
            putchar('\n');
    }
    return 0;
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'f':
            reference = optarg;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'v':
            verbose = true;
            break;
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (reference == 0)
        err_error("You must specify the reference file (-f reference)");

    if ((ref = fopen(reference, "r")) == 0)
        err_syserr("failed to open file '%s' for reading\n", reference);

    filter_stdout(argc, argv, optind, check_offsets);

    return 0;
}

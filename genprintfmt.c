/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Generate an initializer for a PrintFormat structure
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/* -- Include Files */

#include "posixver.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stderr.h"
#include "printfmt.h"

static const char optstr[] = "hV";
static const char usestr[] = "[-hV] name format-string [name format-string ...]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_genprintfmt_c[];
const char jlss_id_genprintfmt_c[] = "@(#)$Id$";
#endif /* lint */

static const char *pw_value(int value, char *buffer)
{
    if (value == FWP_Star)
        strcpy(buffer, "FWP_Star");
    else if (value == FWP_None)
        strcpy(buffer, "FWP_None");
    else
        sprintf(buffer, "%d", value);
    return buffer;
}

static void print_format_initializer(const char *name, const PrintFormat *pf)
{
    char buff1[12];
    char buff2[12];
    int  fmtlen = pf->end - pf->start + 1;
    printf("\nstatic PrintFormat %s =\n", name);
    printf("{    /* \"%*.*s\" */\n", fmtlen, fmtlen, pf->start);
    printf("    .start = 0, .end = 0, .error = PFE_NoError,\n");
    printf("    .width = %s, .precision = %s,\n",
           pw_value(pf->width, buff1), pw_value(pf->precision, buff2));
    printf("    .conv_num = %d, .width_num = %d, .prec_num = %d,\n",
           pf->conv_num, pf->width_num, pf->prec_num);
    printf("    .flags = \"%s\", .modifier = \"%s\", .convspec = '%c',\n",
           pf->flags, pf->modifier, pf->convspec);
    printf("};\n\n");
}

int main(int argc, char **argv)
{
    int opt;
    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("GENPRINTFMT", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    for (int i = optind; i < argc; i += 2)
    {
        if (i >= argc-1)
        {
            err_remark("Missing format string argument\n");
            err_usage(usestr);
        }
        PrintFormat pf;
        PFP_Status rc;
        const char *name = argv[i];
        const char *start = argv[i+1];
        while ((rc = print_format_parse(start, &pf)) == PFP_Found)
        {
            print_format_initializer(name, &pf);
            start = pf.end + 1;
        }
        if (rc == PFP_Error)
            err_remark("Problem parsing '%s': %d %s\n",
                       argv[i+1], (int)rc, print_format_error(rc));
    }

    return 0;
}

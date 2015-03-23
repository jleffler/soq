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

#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stderr.h"
#include "printfmt.h"

static const char optstr[] = "ahi:n:oV";
static const char usestr[] = "[-ahV] [-n name] format-string [...]";
static const char hlpstr[] =
    "  -a       Generate an array\n"
    "  -h       Print this help message and exit\n"
    "  -i init  Number to start counting at (default 0)\n"
    "  -n name  Use given name (default \"pf_var\")\n"
    "  -o       Old (C89/C90) initializers\n"
    "  -V       Print version information and exit\n"
    ;

static int array = 0;       /* Print initializers in an array */
static int style = 0;       /* Print non-designated initializers */
static int number = 0;      /* Index number for variable names */
static const char *pf_name = "pf_name";
static const char *indent = "";

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

enum {  D_START, D_END, D_ERROR, D_WIDTH, D_PRECISION, D_CONV_NUM,
        D_WIDTH_NUM, D_PREC_NUM, D_FLAGS, D_MODIFIER, D_CONVSPEC };
static const char *designators[][11] =
{
    {   ".start =", ".end =", ".error =", ".width =", ".precision =",
        ".conv_num =", ".width_num =", ".prec_num =", ".flags =",
        ".modifier =", ".convspec =",
    },
    {   "", "", "", "", "", "", "", "", "", "", "" },
};

static void print_format_initializer(const PrintFormat *pf)
{
    char buff1[12];
    char buff2[12];
    int  fmtlen = pf->end - pf->start + 1;
    if (array == 0)
        printf("\nstatic PrintFormat %s_%d =\n", pf_name, number++);
    printf("%s{    /* \"%*.*s\" */\n", indent, fmtlen, fmtlen, pf->start);
    printf("%s    %s 0, %s 0, %s PFE_NoError,\n",
           indent, designators[style][D_START],
           designators[style][D_END], designators[style][D_ERROR]);
    printf("%s    %s %s, %s %s,\n",
           indent, designators[style][D_WIDTH], pw_value(pf->width, buff1),
           designators[style][D_PRECISION], pw_value(pf->precision, buff2));
    printf("%s    %s %d, %s %d, %s %d,\n",
           indent, designators[style][D_CONV_NUM], pf->conv_num,
           designators[style][D_WIDTH_NUM], pf->width_num,
           designators[style][D_PREC_NUM], pf->prec_num);
    printf("%s    %s \"%s\", %s \"%s\", %s '%c',\n",
           indent, designators[style][D_FLAGS], pf->flags,
           designators[style][D_MODIFIER], pf->modifier,
           designators[style][D_CONVSPEC], pf->convspec);
    if (array == 0)
        printf("};\n\n");
    else
        printf("%s},\n", indent);
}

int main(int argc, char **argv)
{
    int opt;
    err_setarg0(argv[0]);
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            array = 1;
            indent = "    ";
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'i':
            number = atoi(optarg);
            if (number < 0)
                number = 0;
            break;
        case 'n':
            pf_name = optarg;
            break;
        case 'o':
            style = 1;
            break;
        case 'V':
            err_version("GENPRINTFMT", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    if (array == 1)
        printf("\nstatic PrintFormat %s[] =\n{\n", pf_name);

    for (int i = optind; i < argc; i++)
    {
        PrintFormat pf;
        PFP_Status rc;
        const char *start = argv[i];
        while ((rc = print_format_parse(start, &pf)) == PFP_Found)
        {
            print_format_initializer(&pf);
            start = pf.end + 1;
        }
        if (rc == PFP_Error)
            err_remark("Problem parsing '%s': %d %s\n",
                       argv[i+1], (int)rc, print_format_error(rc));
    }

    if (array == 1)
        printf("};\n\n");

    return 0;
}

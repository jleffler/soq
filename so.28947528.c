/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Test code for SO 28947528
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
#include "phasedtest.h"

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_so_28947528_c[];
const char jlss_id_so_28947528_c[] = "@(#)$Id$";
#endif /* lint */

static size_t scan_format(const char *format, PrintFormat *pf, size_t pf_size)
{
    size_t i = 0;
    PFP_Status rc;
    const char *start = format;
    while (i < pf_size && (rc = print_format_parse(start, &pf[i])) == PFP_Found)
    {
        start = pf[i].end + 1;
        i++;
    }
    if (rc == PFP_Error)
    {
        fprintf(stderr, "Failed to parse [[%s]] (%d: %s)\n",
                format, (int)rc, print_format_error(pf[i].error));
    }
    return i;
}


/* -- PHASE 1 TESTING -- */

/* -- Test for compatibility of format strings -- */
typedef struct p1_test_case
{
    const char        *format1;
    const char        *format2;
    const PrintFormat *pf1[2];
    const PrintFormat *pf2[2];
    size_t             num1;
    size_t             num2;
    int                status;
} p1_test_case;

#if 0
    const char *start;          /* Pointer to % symbol */
    const char *end;            /* Pointer to conversion specifier */
    PFP_Errno   error;          /* Conversion error number */
    short       width;          /* Field width (FWP_None for none, FWP_Star for *) */
    short       precision;      /* Field precision (FWP_None for none, FWP_Star for *) */
    short       conv_num;       /* n of %n$ for value (0 for none) */
    short       width_num;      /* n of *n$ for width (0 for none) */
    short       prec_num;       /* n of *n$ for precision (0 for none) */
    char        flags[7];       /* [+-0# '] */
    char        modifier[3];    /* hh|h|l|ll|j|z|t|L */
    char        convspec;       /* [diouxXfFeEgGAascpnCS] */
#endif

static PrintFormat pf_d =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 0, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'd'
};

static PrintFormat pf_f =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 0, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'f'
};

static PrintFormat pf_1_d =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 1, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'd'
};

static PrintFormat pf_2_f =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 2, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'f'
};

static const p1_test_case p1_tests[] =
{
    { "Something %d", "Something else %d",    { &pf_d, 0 }, { &pf_d, 0 }, 1, 1, 1 },
    { "Something %d", "Something else %f",    { &pf_d, 0 }, { &pf_f, 0 }, 1, 1, 0 },
    { "Something %d", "Something %d else %d", { &pf_d, 0 }, { &pf_d, &pf_d }, 1, 2, 0 },
    { "Something %d and %f", "Something %2$f and %1$d", { &pf_d, &pf_f }, { &pf_2_f, &pf_1_d }, 2, 2, 1 },
};

/* Group of integer formats and double formats */
static char * const format_group[] = { "diouxX", "faAeEgG", 0 };

static int similar_format(PrintFormat *pf1, PrintFormat *pf2)
{
    if (pf1->conv_num  != pf2->conv_num  ||
        pf1->width_num != pf2->width_num ||
        pf1->prec_num  != pf2->prec_num  ||
        strcmp(pf1->modifier, pf2->modifier) != 0)
        return 0;
    if (pf1->convspec == pf2->convspec)
        return 1;
    for (int i = 0; format_group[i] != 0; i++)
    {
        const char *f1 = strchr(format_group[i], pf1->convspec);
        const char *f2 = strchr(format_group[i], pf2->convspec);
        if (f1 != 0 && f2 != 0)
            return 1;
        if ((f1 != 0 && f2 == 0) || (f1 == 0 && f2 != 0))
            return 0;
    }
    return 0;
}

static int simple_equivalent(PrintFormat *pf1, PrintFormat *pf2, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        if (!similar_format(&pf1[i], &pf2[i]))
            return 0;
    }
    return 1;
}

static int complex_equivalent(PrintFormat *pf1, PrintFormat *pf2, size_t num)
{
    for (size_t i = 0; i < num; i++)
        if (&pf1[i] != &pf2[i])
            return 0;
    return 1;
}

static void p1_tester(const void *data)
{
    enum { MAX_CONVSPECS = 2 };
    const p1_test_case *test = (const p1_test_case *)data;
    PrintFormat pf1[MAX_CONVSPECS];
    PrintFormat pf2[MAX_CONVSPECS];

    size_t nf1 = scan_format(test->format1, pf1, MAX_CONVSPECS);
    size_t nf2 = scan_format(test->format2, pf2, MAX_CONVSPECS);

    if (nf1 != test->num1)
        pt_fail("Incorrect number of format strings recognized: wanted %zu, actual %zu (format [[%s]])\n",
            test->num1, nf1, test->format1);
    else if (nf1 != test->num1)
        pt_fail("Incorrect number of format strings recognized: wanted %zu, actual %zu (format [[%s]])\n",
            test->num2, nf2, test->format2);
    else if (nf1 != nf2 && test->status == 0)
        pt_pass("Incompatible: <<%s>> and <<%s>> - "
                "number of conversion specifications don't match (%zu vs %zu)\n",
                test->format1, test->format2, nf1, nf2);
    else if (nf1 != nf2 && test->status == 1)
        pt_fail("Test error: number of conversion specifications differ (%zu vs %zu)"
                " but the result is supposed to be compatible (which is wrong!)\n",
                nf1, nf2);
    else if (simple_equivalent(pf1, pf2, nf1) && test->status == 1)
        pt_pass("Compatible: <<%s>> and <<%s>> are simply compatible\n",
                test->format1, test->format2);
    else if (complex_equivalent(pf1, pf2, nf1) && test->status == 1)
        pt_pass("Compatible: <<%s>> and <<%s>> are complex but compatible\n",
                test->format1, test->format2);
    else if (simple_equivalent(pf1, pf2, nf1) && test->status == 0)
        pt_fail("Test error: <<%s>> and <<%s>> are simply compatible yet test expects incompatible\n",
                test->format1, test->format2);
    else
        pt_fail("Test error: <<%s>> and <<%s>> are complex but compatible, yet test expects incompatible\n",
                test->format1, test->format2);
}

/* -- Phased Test Infrastructure -- */

static pt_auto_phase phases[] =
{
    { p1_tester, PT_ARRAYINFO(p1_tests), 0, "Test for compatibility of format strings" },
};

int main(int argc, char **argv)
{
    return(pt_auto_harness(argc, argv, phases, DIM(phases)));
}

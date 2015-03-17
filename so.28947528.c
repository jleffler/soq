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

#if 0
static inline size_t check_number(size_t *indexes, size_t max_indexes, size_t value, size_t max_sofar)
{
    if (value == 0 || value >= max_indexes)
        return PFE_DollarOverflow;  /* Sub-optimal error */
    indexes[value]++;
    if (value > max_sofar)
        max_sofar = value;
    return max_sofar;
}
        max_sofar = check_number(indexes, max_indexes, pf[i].conv_num, max_sofar);
        max_sofar = check_number(indexes, max_indexes, pf[i].width_num, max_sofar);
        max_sofar = check_number(indexes, max_indexes, pf[i].prec_num, max_sofar);
#endif /* 0 */

static PFP_Errno check_consistency(PrintFormat *pf, size_t pf_size)
{
    size_t ndollar_count = 0;
    size_t ndollar_width = 0;
    size_t ndollar_prec  = 0;
    size_t width_stars   = 0;
    size_t prec_stars    = 0;

    for (size_t i = 0; i < pf_size; i++)
    {
        if (pf[i].conv_num != 0)
            ndollar_count++;
        if (pf[i].width_num != 0)
            ndollar_width++;
        if (pf[i].prec_num != 0)
            ndollar_prec++;
        if (pf[i].width == FWP_Star)
            width_stars++;
        if (pf[i].precision == FWP_Star)
            prec_stars++;
    }

    if (ndollar_count == 0 && ndollar_width == 0 && ndollar_prec == 0)
        return PFE_NoError;

    if (ndollar_count != pf_size || ndollar_width != width_stars || ndollar_prec != prec_stars)
        return PFE_MissingNDollar;

    size_t max_indexes = 3 * pf_size + 1;
    size_t indexes[max_indexes];
    for (size_t i = 0; i < max_indexes; i++)
        indexes[i] = 0;
    size_t max_sofar = 0;
    for (size_t i = 0; i < pf_size; i++)
    {
        if (pf[i].conv_num <= 0 || (size_t)pf[i].conv_num > max_indexes)
            return PFE_DollarOverflow;      /* Sub-optimal error */
        indexes[pf[i].conv_num]++;
        if ((size_t)pf[i].conv_num > max_sofar)
            max_sofar = pf[i].conv_num;
        if (pf[i].width == FWP_Star)
        {
            if (pf[i].width_num <= 0 || (size_t)pf[i].width_num > max_indexes)
                return PFE_DollarOverflow;  /* Sub-optimal error */
            indexes[pf[i].width_num]++;
            if ((size_t)pf[i].width_num > max_sofar)
                max_sofar = pf[i].width_num;
        }
        if (pf[i].precision == FWP_Star)
        {
            if (pf[i].prec_num <= 0 || (size_t)pf[i].prec_num > max_indexes)
                return PFE_DollarOverflow;  /* Sub-optimal error */
            indexes[pf[i].prec_num]++;
            if ((size_t)pf[i].prec_num > max_sofar)
                max_sofar = pf[i].prec_num;
        }
    }
    for (size_t i = 1; i <= max_sofar; i++)
    {
        if (indexes[i] == 0)
            return PFE_MissingNDollar;      /* Sub-optimal error */
    }
    return PFE_NoError;
}

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
                format, (int)pf[i].error, print_format_error(pf[i].error));
        i = 0;
    }
    else
    {
        PFP_Errno err = check_consistency(pf, i);
        if (err != PFE_NoError)
        {
            fprintf(stderr, "Consistency check failure parsing [[%s]] (%d: %s)\n",
                    format, (int)err, print_format_error(err));
            i = 0;
        }
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

static PrintFormat pf_6_e =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 6, .width_num = 4, .prec_num = 5,
    .flags = "-", .modifier = "L", .convspec = 'e'
};

static PrintFormat pf_3_d =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 3, .width_num = 1, .prec_num = 2,
    .flags = "+", .modifier = "ll", .convspec = 'd'
};

static PrintFormat pf_6_A =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 6, .width_num = 4, .prec_num = 5,
    .flags = "-", .modifier = "L", .convspec = 'A'
};

static PrintFormat pf_3_X =
{
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 3, .width_num = 1, .prec_num = 2,
    .flags = "+", .modifier = "ll", .convspec = 'X'
};

static const p1_test_case p1_tests[] =
{
    { "Something %d", "Something else %d",    { &pf_d, 0 }, { &pf_d, 0 }, 1, 1, 1 },
    { "Something %d", "Something else %f",    { &pf_d, 0 }, { &pf_f, 0 }, 1, 1, 0 },
    { "Something %d", "Something %d else %d", { &pf_d, 0 }, { &pf_d, &pf_d }, 1, 2, 0 },
    { "Something %d and %f", "Something %2$f and %1$d with more",
      { &pf_d, &pf_f }, { &pf_2_f, &pf_1_d }, 2, 2, 1
    },
    { "Something %3$+*1$.*2$lld and %6$-*4$.*5$Le",
      "Anything %4$*5$.*6$LA or %3$*1$.*2$llX and more",
      { &pf_3_d, &pf_6_e }, { &pf_6_A, &pf_3_X }, 2, 2, 1
    },
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
    if ((pf1->width == FWP_Star && pf2->width != FWP_Star) ||
        (pf1->width != FWP_Star && pf2->width == FWP_Star))
        return 0;
    if ((pf1->precision == FWP_Star && pf2->precision != FWP_Star) ||
        (pf1->precision != FWP_Star && pf2->precision == FWP_Star))
        return 0;
    if (pf1->convspec == pf2->convspec)
        return 1;
    for (int i = 0; format_group[i] != 0; i++)
    {
        const char *f1 = strchr(format_group[i], pf1->convspec);
        const char *f2 = strchr(format_group[i], pf2->convspec);
        if (f1 != 0 && f2 != 0)
            return 1;
        /* Or: if (f1 == 0 && f2 == 0) continue; else return 0; */
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
    {
        if (&pf1[i] != &pf2[i])
            return 0;
    }
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

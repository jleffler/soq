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

#include "posixver.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

static inline PFP_Errno check_number(size_t *indexes, size_t max_indexes, size_t value, size_t *max_sofar)
{
    if (value == 0 || value >= max_indexes)
        return PFE_DollarOverflow;  /* Sub-optimal error */
    indexes[value]++;
    if (value > *max_sofar)
        *max_sofar = value;
    return PFE_NoError;
}

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

    /* No conversions use n$ */
    if (ndollar_count == 0 && ndollar_width == 0 && ndollar_prec == 0)
        return PFE_NoError;

    /* Some conversions use n$, others do not */
    if (ndollar_count != pf_size || ndollar_width != width_stars || ndollar_prec != prec_stars)
        return PFE_MissingNDollar;

    /* All values of n$ from 1 to some maximum must be used (no gaps) */
    size_t max_indexes = 3 * pf_size + 1;
    size_t indexes[max_indexes];
    for (size_t i = 0; i < max_indexes; i++)
        indexes[i] = 0;
    size_t max_sofar = 0;

    for (size_t i = 0; i < pf_size; i++)
    {
        PFP_Errno err = check_number(indexes, max_indexes, pf[i].conv_num, &max_sofar);
        if (err == PFE_NoError && pf[i].width == FWP_Star)
            err = check_number(indexes, max_indexes, pf[i].width_num, &max_sofar);
        if (err == PFE_NoError && pf[i].precision == FWP_Star)
            err = check_number(indexes, max_indexes, pf[i].prec_num, &max_sofar);
        if (err != PFE_NoError)
            return err;
    }

    for (size_t i = 1; i <= max_sofar; i++)
    {
        if (indexes[i] == 0)
            return PFE_MissingNDollar;      /* Sub-optimal error */
    }

    /* So far, so good */
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

/*
** Match: %1$*2$.*3$d and %1$*3$.*2$d OK, or not OK?
** Match: %1$10.*2$d and %1$*2$.3d OK, or not OK?
*/

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

static bool complex_equivalent(PrintFormat *pf1, PrintFormat *pf2, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        bool matched = false;
        for (size_t j = 0; j < num; j++)
        {
            if (similar_format(&pf1[i], &pf2[j]))
            {
                matched = true;
                break;
            }
        }
        if (!matched)
            return false;
    }
    return true;
}

static PrintFormat *dup_pflist(PrintFormat *old_list, size_t num)
{
    PrintFormat *new_list = malloc(num * sizeof(*new_list));
    assert(new_list != 0);
    if (new_list != 0)
        memmove(new_list, old_list, num * sizeof(*new_list));
    return new_list;
}

static void fix_pflist(PrintFormat *list, size_t num)
{
    size_t count = 0;
    for (size_t i = 0; i < num; i++)
    {
        if (list[i].width_num == FWP_Star)
            list[i].width_num = ++count;
        if (list[i].prec_num == FWP_Star)
            list[i].prec_num = ++count;
        list[i].conv_num = ++count;
    }
}

static int formats_equivalent(PrintFormat *pf1, PrintFormat *pf2, size_t num)
{
    if (simple_equivalent(pf1, pf2, num))
        return 1;
    /* No numbered fields */
    if (pf1[0].conv_num == 0 && pf2[0].conv_num == 0)
        return 0;
    /* Convert list with unnumbered fields to numbered fields (if any) */
    bool free_pf1 = false;
    bool free_pf2 = false;
    if (pf1[0].conv_num == 0)
    {
        pf1 = dup_pflist(pf1, num);
        fix_pflist(pf1, num);
        free_pf1 = true;
    }
    if (pf2[0].conv_num == 0)
    {
        pf2 = dup_pflist(pf2, num);
        fix_pflist(pf2, num);
        free_pf2 = true;
    }
    assert(!free_pf1 || !free_pf2);
    bool rc = complex_equivalent(pf1, pf2, num);
    if (free_pf1)
        free(pf1);
    if (free_pf2)
        free(pf2);
    return rc;
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
{   /* "%d" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 0, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'd'
};

static PrintFormat pf_f =
{
    /* "%f" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 0, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'f'
};

static PrintFormat pf_1_d =
{
    /* "%1$d" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 1, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'd'
};

static PrintFormat pf_2_f =
{
    /* "%2$f" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_None, .precision = FWP_None,
    .conv_num = 2, .width_num = 0, .prec_num = 0,
    .flags = "", .modifier = "", .convspec = 'f'
};

static PrintFormat pf_6_e =
{
    /* "%6$-*4$.*5$Le" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 6, .width_num = 4, .prec_num = 5,
    .flags = "-", .modifier = "L", .convspec = 'e'
};

static PrintFormat pf_3_d =
{
    /* "%3$+*1$.*2$lld" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 3, .width_num = 1, .prec_num = 2,
    .flags = "+", .modifier = "ll", .convspec = 'd'
};

static PrintFormat pf_4_A =
{
    /* "%4$-*5$.*6$LA" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 4, .width_num = 5, .prec_num = 6,
    .flags = "-", .modifier = "L", .convspec = 'A'
};

static PrintFormat pf_3_X =
{
    /* "%3$*1$.*2$llX" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 3, .width_num = 1, .prec_num = 2,
    .flags = "+", .modifier = "ll", .convspec = 'X'
};

static PrintFormat pf_6_A =
{
    /* "%6$-*4$.*5$LA" */
    .start = 0, .end = 0, .error = PFE_NoError,
    .width = FWP_Star, .precision = FWP_Star,
    .conv_num = 6, .width_num = 4, .prec_num = 5,
    .flags = "-", .modifier = "L", .convspec = 'A'
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
      { &pf_3_d, &pf_6_e }, { &pf_4_A, &pf_3_X }, 2, 2, 0
    },
    { "Something %3$+*1$.*2$lld and %6$-*4$.*5$Le",
      "Anything %6$*4$.*5$LA or %3$*1$.*2$llX and more",
      { &pf_3_d, &pf_6_e }, { &pf_6_A, &pf_3_X }, 2, 2, 1
    },
};

static void p1_tester(const void *data)
{
    enum { MAX_CONVSPECS = 2 };
    const p1_test_case *test = (const p1_test_case *)data;
    PrintFormat pf1[MAX_CONVSPECS];
    PrintFormat pf2[MAX_CONVSPECS];

    size_t nf1 = scan_format(test->format1, pf1, MAX_CONVSPECS);
    size_t nf2 = scan_format(test->format2, pf2, MAX_CONVSPECS);
    int rc;

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
    else if ((rc = formats_equivalent(pf1, pf2, nf1)) && test->status == 1)
        pt_pass("Compatible: <<%s>> and <<%s>> are compatible\n",
                test->format1, test->format2);
    else if (rc == 0 && test->status == 0)
        pt_pass("Incompatible: <<%s>> and <<%s>> are incompatible\n", test->format1, test->format2);
    else if (rc == 0 && test->status == 1)
        pt_fail("Incompatible: <<%s>> and <<%s>> are deemed incompatible but should be compatible\n",
                test->format1, test->format2);
    else if (rc == 1 && test->status == 0)
        pt_fail("Compatible: <<%s>> and <<%s>> are deemed compatible but should be incompatible\n",
                test->format1, test->format2);
    else
        pt_fail("Test error: <<%s>> and <<%s>> -- can't happen\n",
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

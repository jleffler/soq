/* SO 4313-7847 */

#include "polynomial.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "emalloc.h"
#include "stderr.h"

typedef struct termlist
{
    int n_terms;
    term *terms;
} termlist;

static void wikipedia_example_1(void)
{
    // First Wikipedia example:
    // dividend: x^3 - 2x^2 - 4
    // divisor:  x − 3
    // quotient: x^2 + x + 3
    // remainder: 5
    struct termlist tl_top = { 3, (term []){ { 3, { 1, +1 } },
                                             { 2, { 2, -1 } },
                                             { 0, { 4, -1 } }, } };
    struct termlist tl_bot = { 2, (term []){ { 1, { 1, +1 } },
                                             { 0, { 3, -1 } }, } };
    struct termlist tl_quo = { 3, (term []){ { 2, { 1, +1 } },
                                             { 1, { 1, +1 } },
                                             { 0, { 3, +1 } }, } };
    struct termlist tl_rem = { 1, (term []){ { 0, { 5, +1 } }, } };
    polynomial *w_top = make_polynomial(tl_top.n_terms, tl_top.terms);
    polynomial *w_bot = make_polynomial(tl_bot.n_terms, tl_bot.terms);
    polynomial *w_quo = make_polynomial(tl_quo.n_terms, tl_quo.terms);
    polynomial *w_rem = make_polynomial(tl_rem.n_terms, tl_rem.terms);

    printf("Wikipedia example 1:\n");
    print_polynomial("Dividend", w_top);
    print_polynomial("Divisor", w_bot);
    poly_pair qr = div_polynomial(w_top, w_bot);
    print_polynomial("Actual Quotient", qr.quotient);
    print_polynomial("Actual Remainder", qr.remainder);
    print_polynomial("Wanted Quotient", w_quo);
    print_polynomial("Wanted Remainder", w_rem);
    free_polynomial(qr.quotient);
    free_polynomial(qr.remainder);
    putchar('\n');
}

static void wikipedia_example_2(void)
{
    // Second Wikipedia example (tangent):
    // dividend: x^3 - 12x^2 - 42
    // divisor:  (x − 1)^2 = x^2 - 2x + 1
    // quotient: x - 10
    // remainder: -21x - 32
    struct termlist tl_top = { 3, (term []){ { 3, {  1, +1 } },
                                             { 2, { 12, -1 } },
                                             { 0, { 42, -1 } }, } };
    struct termlist tl_bot = { 3, (term []){ { 2, {  1, +1 } },
                                             { 1, {  2, -1 } },
                                             { 0, {  1, +1 } }, } };
    struct termlist tl_quo = { 2, (term []){ { 1, {  1, +1 } },
                                             { 0, { 10, -1 } }, } };
    struct termlist tl_rem = { 2, (term []){ { 1, { 21, -1 } },
                                             { 0, { 32, -1 } }, } };
    polynomial *w_top = make_polynomial(tl_top.n_terms, tl_top.terms);
    polynomial *w_bot = make_polynomial(tl_bot.n_terms, tl_bot.terms);
    polynomial *w_quo = make_polynomial(tl_quo.n_terms, tl_quo.terms);
    polynomial *w_rem = make_polynomial(tl_rem.n_terms, tl_rem.terms);

    printf("Wikipedia example 2:\n");
    print_polynomial("Dividend", w_top);
    print_polynomial("Divisor", w_bot);
    poly_pair qr = div_polynomial(w_top, w_bot);
    print_polynomial("Actual Quotient", qr.quotient);
    print_polynomial("Actual Remainder", qr.remainder);
    print_polynomial("Wanted Quotient", w_quo);
    print_polynomial("Wanted Remainder", w_rem);
    free_polynomial(qr.quotient);
    free_polynomial(qr.remainder);
    putchar('\n');
}

int main(int argc, char **argv)
{
    err_setarg0(argv[argc-argc]);
    termlist p1[] =
    {
        { .n_terms = 4, .terms = (term[]){ { 3, { 2, +1 } },
                                           { 2, { 1, +1 } },
                                           { 1, { 4, +1 } },
                                           { 0, { 9, -1 } } } },
        { .n_terms = 3, .terms = (term[]){ { 2, { 3, +1 } },
                                           { 1, { 4, -1 } },
                                           { 0, { 8,  1 } } } },
        { .n_terms = 3, .terms = (term[]){ { 1, { 5, +1 } },
                                           { 0, { 3, +1 } },
                                           { 2, { 4, -1 } } } },
        { .n_terms = 2, .terms = (term[]){ { 4, { 5, +1 } },
                                           { 0, { 5, -1 } } } },
        { .n_terms = 4, .terms = (term[]){ { 3, { 2, +1 } },
                                           { 2, { 1, +1 } },
                                           { 1, { 4,  1 } },
                                           { 2, { 9, -1 } } } },
    };
    enum { NUM_POLYS = sizeof(p1) / sizeof(p1[0]) };
    polynomial *poly[NUM_POLYS] = { 0 };

    for (int i = 0; i < NUM_POLYS; i++)
    {
        poly[i] = make_polynomial(p1[i].n_terms, p1[i].terms);
        print_polynomial("Building", poly[i]);
    }

    printf("Checking:\n");
    for (int i = 0; i < NUM_POLYS; i++)
        print_polynomial("Next", poly[i]);
    putchar('\n');

    printf("Multiplying polynomials:\n");
    for (int i = 0; i < NUM_POLYS; i++)
    {
        for (int j = 0; j < NUM_POLYS; j++)
        {
            print_polynomial("Term 1", poly[i]);
            print_polynomial("Term 2", poly[j]);
            polynomial *prod = mul_polynomial(poly[i], poly[j]);
            print_polynomial("Product", prod);
            free_polynomial(prod);
        }
        putchar('\n');
    }

    printf("Adding polynomials:\n");
    for (int i = 0; i < NUM_POLYS; i++)
    {
        for (int j = 0; j < NUM_POLYS; j++)
        {
            print_polynomial("Term 1", poly[i]);
            print_polynomial("Term 2", poly[j]);
            polynomial *sum = add_polynomial(poly[i], poly[j]);
            print_polynomial("Sum", sum);
            free_polynomial(sum);
        }
        putchar('\n');
    }

    printf("Subtracting polynomials:\n");
    for (int i = 0; i < NUM_POLYS; i++)
    {
        for (int j = 0; j < NUM_POLYS; j++)
        {
            print_polynomial("Term 1", poly[i]);
            print_polynomial("Term 2", poly[j]);
            polynomial *diff = sub_polynomial(poly[i], poly[j]);
            print_polynomial("Difference", diff);
            free_polynomial(diff);
        }
        putchar('\n');
    }

    printf("Dividing polynomials:\n");

    wikipedia_example_1();
    wikipedia_example_2();

    for (int i = 0; i < NUM_POLYS; i++)
    {
        for (int j = 0; j < NUM_POLYS; j++)
        {
            print_polynomial("Term 1", poly[i]);
            print_polynomial("Term 2", poly[j]);
            poly_pair qr = div_polynomial(poly[i], poly[j]);
            print_polynomial("Quotient", qr.quotient);
            print_polynomial("Remainder", qr.remainder);
            free_polynomial(qr.quotient);
            free_polynomial(qr.remainder);
            putchar('\n');
        }
    }

    for (int i = 0; i < NUM_POLYS; i++)
        free_polynomial(poly[i]);

    return 0;
}

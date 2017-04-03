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
        }
        putchar('\n');
    }

    for (int i = 0; i < NUM_POLYS; i++)
        free_polynomial(poly[i]);

    return 0;
}

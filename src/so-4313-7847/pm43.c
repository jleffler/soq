/* SO 4313-7847 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "emalloc.h"

/* -- SOF polynomial.h -- */
typedef struct polynomial polynomial;

typedef struct poly_pair
{
    polynomial *quotient;
    polynomial *remainder;
} poly_pair;

typedef struct term
{
    unsigned int power;
    int coeff;
} term;

/* What should be the exposed/exposable interface for creating a polynomial? */
static void print_polynomial(const char *tag, const polynomial *poly);
static polynomial *mul_polynomial(const polynomial *poly1, const polynomial *poly2);
static polynomial *add_polynomial(const polynomial *poly1, const polynomial *poly2);
static polynomial *sub_polynomial(const polynomial *poly1, const polynomial *poly2);
static poly_pair   div_polynomial(const polynomial *poly1, const polynomial *poly2);
static void free_polynomial(polynomial *poly);
static void print_polynomial(const char *tag, const polynomial *poly);
static polynomial *make_polynomial(int n_terms, const term *terms);
/* -- EOF polynomial.h -- */

/* -- SOF polynomial.c -- */
struct polynomial
{
    unsigned int power;
    int          coeff;
    polynomial  *next;
};

static polynomial *make_term(unsigned int power, int coeff, polynomial *next)
{
    polynomial *new_term = MALLOC(sizeof(*new_term));
    new_term->power = power;
    new_term->coeff = coeff;
    new_term->next  = next;
    return new_term;
}

static polynomial *add_term(polynomial *poly, unsigned int power, int coeff)
{
    if (coeff == 0)
        return poly;
    if (poly == NULL)
        return make_term(power, coeff, NULL);

    /* Find where this term goes */
    polynomial *term = poly;
    polynomial *prev = NULL;
    while (term != NULL && term->power > power)
    {
        prev = term;
        term = term->next;
    }

    if (term != NULL && term->power == power)
    {
        term->coeff += coeff;
    }
    else
    {
        assert(term == NULL || term->power < power);
        polynomial *new_term = make_term(power, coeff, term);
        if (prev == NULL)
            poly = new_term;
        else
            prev->next = new_term;
    }
    return poly;
}

static polynomial *mul_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    polynomial *result = NULL;

    for (const polynomial *p1 = poly1; p1 != NULL; p1 = p1->next)
    {
        for (const polynomial *p2 = poly2; p2 != NULL; p2 = p2->next)
            result = add_term(result, p1->power + p2->power, p1->coeff * p2->coeff);
    }
    return result;
}

static polynomial *add_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    polynomial *result = NULL;

    for (const polynomial *p1 = poly1; p1 != NULL; p1 = p1->next)
        result = add_term(result, p1->power, p1->coeff);
    for (const polynomial *p2 = poly2; p2 != NULL; p2 = p2->next)
        result = add_term(result, p2->power, p2->coeff);
    return result;
}

static polynomial *sub_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    polynomial *result = NULL;

    for (const polynomial *p1 = poly1; p1 != NULL; p1 = p1->next)
        result = add_term(result, p1->power, p1->coeff);
    for (const polynomial *p2 = poly2; p2 != NULL; p2 = p2->next)
        result = add_term(result, p2->power, -p2->coeff);
    return result;
}

static poly_pair div_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    poly_pair result = { NULL, NULL };
    return result;
}

static void print_polynomial(const char *tag, const polynomial *poly)
{
    int printed = 0;
    printf("%s:", tag);
    char sign = ' ';
    while (poly != NULL)
    {
        int coeff = poly->coeff;
        if (coeff != 0)
        {
            if (sign != ' ' && coeff < 0)
            {
                sign = '-';
                coeff = -coeff;
            }
            if (poly->power == 0)
                printf(" %c %d", sign, coeff);
            else if (poly->power == 1)
                printf(" %c %dx", sign, coeff);
            else
                printf(" %c %dx^%u", sign, coeff, poly->power);
            printed++;
        }
        poly = poly->next;
        sign = '+';
    }
    if (printed == 0)
        printf("   0");
    putchar('\n');
    fflush(stdout);
}

static void free_polynomial(polynomial *poly)
{
    while (poly != NULL)
    {
        polynomial *next = poly->next;
        free(poly);
        poly = next;
    }
}

static polynomial *make_polynomial(int n_terms, const term *terms)
{
    polynomial *poly = 0;
    for (int i = 0; i < n_terms; i++)
    {
        printf("Term: %dx^%u\n", terms[i].coeff, terms[i].power);
        fflush(stdout);
        poly = add_term(poly, terms[i].power, terms[i].coeff);
    }
    return poly;
}

/* -- EOF polynomial.c -- */

/* -- SOF polytest.c -- */

typedef struct termlist
{
    int n_terms;
    term *terms;
} termlist;

int main(void)
{
    termlist p1[] =
    {
        { .n_terms = 4, .terms = (term[]){ { 3, 2 }, { 2,  1 }, { 1,  4 }, { 0, -9 } } },
        { .n_terms = 3, .terms = (term[]){ { 2, 3 }, { 1, -4 }, { 0,  8 } } },
        { .n_terms = 3, .terms = (term[]){ { 1, 5 }, { 0,  3 }, { 2, -4 } } },
        { .n_terms = 2, .terms = (term[]){ { 4, 5 }, { 0, -5 } } },
        { .n_terms = 4, .terms = (term[]){ { 3, 2 }, { 2,  1 }, { 1,  4 }, { 2, -9 } } },
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

/* -- EOF polytest.c -- */

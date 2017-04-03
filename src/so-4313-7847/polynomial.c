/* SO 4313-7847 */
#include "polynomial.h"

#include "emalloc.h"
#include "stderr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void print_term(int coeff, unsigned int power);

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

polynomial *mul_polynomial(const polynomial *poly1, const polynomial *poly2)
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

polynomial *add_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    polynomial *result = NULL;

    for (const polynomial *p1 = poly1; p1 != NULL; p1 = p1->next)
        result = add_term(result, p1->power, p1->coeff);
    for (const polynomial *p2 = poly2; p2 != NULL; p2 = p2->next)
        result = add_term(result, p2->power, p2->coeff);
    return result;
}

polynomial *sub_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    polynomial *result = NULL;

    for (const polynomial *p1 = poly1; p1 != NULL; p1 = p1->next)
        result = add_term(result, p1->power, p1->coeff);
    for (const polynomial *p2 = poly2; p2 != NULL; p2 = p2->next)
        result = add_term(result, p2->power, -p2->coeff);
    return result;
}

polynomial *copy_polynomial(const polynomial *poly1)
{
    polynomial *result = NULL;
    while (poly1 != NULL)
    {
        result = add_term(result, poly1->power, poly1->coeff);
        poly1 = poly1->next;
    }
    return result;
}

bool zero_polynomial(const polynomial *poly)
{
    while (poly != NULL)
    {
        if (poly->coeff != 0)
            return false;
        poly = poly->next;
    }
    return true;
}

int coeff_for_term_polynomial(const polynomial *poly, unsigned int power)
{
    while (poly != NULL)
    {
        if (poly->power < power)
            return 0;
        if (poly->power == power)
            return poly->coeff;
        poly = poly->next;
    }
    return 0;
}

int degree_polynomial(const polynomial *poly)
{
    while (poly != NULL)
    {
        if (poly->coeff != 0)
            return poly->power;
        poly = poly->next;
    }
    return 0;
}

/*
** Pseudo-code algorithm from Wikipedia
**
**  function n / d:
**    require d ≠ 0
**    q ← 0
**    r ← n       # At each step n = d × q + r
**    while r ≠ 0 AND degree(r) ≥ degree(d):
**      t ← lead(r)/lead(d)     # Divide the leading terms
**      q ← q + t
**      r ← r − t * d
**    return (q, r)
*/

poly_pair div_polynomial(const polynomial *poly1, const polynomial *poly2)
{
    assert(poly1 != NULL && poly2 != NULL);
    poly_pair result = { NULL, copy_polynomial(poly1) };
    int power_div = degree_polynomial(poly2);
    int coeff_div = coeff_for_term_polynomial(poly2, power_div);
    //if (coeff_div == 0)
    //{
        //print_polynomial("Crasher", poly2);
        //printf("Power div = %d\n", power_div);
    //}
    assert(coeff_div != 0);
    int power_rem;
    while (!zero_polynomial(result.remainder) &&
           (power_rem = degree_polynomial(result.remainder)) >= power_div)
    {
        int coeff_rem = coeff_for_term_polynomial(result.remainder, power_rem);
        //printf("coeff_rem = %d; coeff_div = %d; power_rem = %d; power_div = %d; modulus = %d\n",
        //        coeff_rem, coeff_div, power_rem, power_div, coeff_rem % coeff_div);
        if (coeff_rem % coeff_div != 0)
            err_error("Ratio %d / %d requires rational arithmetic\n", coeff_rem, coeff_div);
        result.quotient = add_term(result.quotient, power_rem - power_div, coeff_rem / coeff_div);
        polynomial *t = make_polynomial(1, (term []){ { .power = power_rem - power_div,
                                                        .coeff = coeff_rem / coeff_div } });
        //print_polynomial("t", t);
        //print_polynomial("quotient", result.quotient);
        //print_polynomial("remainder", result.remainder);
        //print_polynomial("poly2", poly2);
        polynomial *td = mul_polynomial(poly2, t);
        result.remainder = sub_polynomial(result.remainder, td);
        free_polynomial(t);
        free_polynomial(td);
    }
    return result;
}

static void print_term(int coeff, unsigned int power)
{
    if (power == 0)
        printf("%d", coeff);
    else if (power == 1)
        printf("%dx", coeff);
    else
        printf("%dx^%u", coeff, power);
}

void print_polynomial(const char *tag, const polynomial *poly)
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
            printf(" %c ", sign);
            print_term(coeff, poly->power);
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

void free_polynomial(polynomial *poly)
{
    while (poly != NULL)
    {
        polynomial *next = poly->next;
        free(poly);
        poly = next;
    }
}

polynomial *make_polynomial(int n_terms, const term *terms)
{
    polynomial *poly = 0;
    for (int i = 0; i < n_terms; i++)
    {
        printf("Term: ");
        print_term(terms[i].coeff, terms[i].power);
        putchar('\n');
        fflush(stdout);
        poly = add_term(poly, terms[i].power, terms[i].coeff);
    }
    return poly;
}

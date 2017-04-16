/* SO 4313-7847 */
#include "polynomial.h"

#include "emalloc.h"
#include "stderr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void print_term(Rational coeff, unsigned int power);

#define RI_ZERO()   ((Rational){ 0, 1 })
#define RI_ONE() ((Rational){ 1, 1 })

struct polynomial
{
    unsigned int power;
    Rational     coeff;
    polynomial  *next;
};

static polynomial *make_term(unsigned int power, Rational coeff, polynomial *next)
{
    polynomial *new_term = MALLOC(sizeof(*new_term));
    new_term->power = power;
    new_term->coeff = coeff;
    new_term->next  = next;
    return new_term;
}

static polynomial *add_term(polynomial *poly, unsigned int power, Rational coeff)
{
    if (ri_cmp(coeff, RI_ZERO()) == 0)
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
        term->coeff = ri_add(term->coeff, coeff);
        if (ri_cmp(term->coeff, RI_ZERO()) == 0)
        {
            if (prev == NULL)
                poly = term->next;
            else
                prev->next = term->next;
            free(term);
        }
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
            result = add_term(result, p1->power + p2->power, ri_mul(p1->coeff, p2->coeff));
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
        result = add_term(result, p2->power, ri_neg(p2->coeff));
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
        if (ri_cmp(poly->coeff, RI_ZERO()) != 0)
            return false;
        poly = poly->next;
    }
    return true;
}

Rational coeff_for_term_polynomial(const polynomial *poly, unsigned int power)
{
    while (poly != NULL)
    {
        if (poly->power < power)
            return RI_ZERO();
        if (poly->power == power)
            return poly->coeff;
        poly = poly->next;
    }
    return RI_ZERO();
}

int degree_polynomial(const polynomial *poly)
{
    while (poly != NULL)
    {
        if (ri_cmp(poly->coeff, RI_ZERO()) != 0)
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
    poly_pair result = { .quotient = NULL, .remainder = copy_polynomial(poly1) };
    //printf("-->> %s:\n", __func__);
    //print_polynomial("Dividend", poly1);
    //print_polynomial("Divisor", poly2);
    //print_polynomial("Quotient", result.quotient);
    //print_polynomial("Remainder", result.remainder);
    int power_div = degree_polynomial(poly2);
    //printf("Degree divisor: %d\n", power_div);
    Rational coeff_div = coeff_for_term_polynomial(poly2, power_div);
    //printf("Term (divisor): ");
    //print_term(coeff_div, power_div); putchar('\n');
    assert(ri_cmp(coeff_div, RI_ZERO()) != 0);
    int power_rem = 0;
    while (!zero_polynomial(result.remainder) &&
           (power_rem = degree_polynomial(result.remainder)) >= power_div)
    {
        //printf("Degree remainder: %d\n", power_rem);
        Rational coeff_rem = coeff_for_term_polynomial(result.remainder, power_rem);
        //printf("Term (remainder): ");
        //print_term(coeff_rem, power_rem); putchar('\n');
        Rational coeff = ri_div(coeff_rem, coeff_div);
        //printf("Term (add to quotient): ");
        //print_term(coeff, power_rem - power_div); putchar('\n');
        result.quotient = add_term(result.quotient, power_rem - power_div, coeff);
        //print_polynomial("Quotient", result.quotient);
        polynomial *t = make_polynomial(1, (term []){ { .power = power_rem - power_div,
                                                        .coeff = coeff } });
        //print_polynomial("t", t);
        //print_polynomial("quotient", result.quotient);
        //print_polynomial("remainder", result.remainder);
        //print_polynomial("poly2", poly2);
        polynomial *td = mul_polynomial(poly2, t);
        //print_polynomial("t * d", td);
        result.remainder = sub_polynomial(result.remainder, td);
        //print_polynomial("remainder", result.remainder);
        free_polynomial(t);
        free_polynomial(td);
    }
    //printf("Degree remainder: %d\n", power_rem);
    //print_polynomial("Final Quotient", result.quotient);
    //print_polynomial("Final Remainder", result.remainder);
    //printf("<<-- %s:\n", __func__);
    return result;
}

static void print_term(Rational coeff, unsigned int power)
{
    char buffer[32];
    ri_fmt(coeff, buffer, sizeof(buffer), "");
    /* Much room for improvement here! */
    if (power == 0)
        printf("%s", buffer);
    else if (ri_cmp(coeff, RI_ONE()) == 0 && power == 1)
        printf("x");
    else if (power == 1)
        printf("%s.x", buffer);
    else if (ri_cmp(coeff, RI_ONE()) == 0)
        printf("x^%u", power);
    else
        printf("%s.x^%u", buffer, power);
}

void print_polynomial(const char *tag, const polynomial *poly)
{
    int printed = 0;
    printf("%s:", tag);
    char sign = ' ';
    while (poly != NULL)
    {
        Rational coeff = poly->coeff;
        if (ri_cmp(poly->coeff, RI_ZERO()) != 0)
        {
            if (sign != ' ' && ri_cmp(poly->coeff, RI_ZERO()) < 0)
            {
                sign = '-';
                coeff = ri_neg(coeff);
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
        //printf("Term: ");
        //print_term(terms[i].coeff, terms[i].power);
        //putchar('\n');
        //fflush(stdout);
        poly = add_term(poly, terms[i].power, terms[i].coeff);
    }
    return poly;
}

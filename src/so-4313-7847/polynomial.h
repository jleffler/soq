/* SO 4313-7847 */

#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <stdbool.h>
#include "rational.h"

typedef RationalInt Rational;       // Abbreviate!
typedef struct polynomial polynomial;

typedef struct poly_pair
{
    polynomial *quotient;
    polynomial *remainder;
} poly_pair;

typedef struct term
{
    unsigned int power;
    Rational     coeff;
} term;

extern void print_polynomial(const char *tag, const polynomial *poly);
extern polynomial *mul_polynomial(const polynomial *poly1, const polynomial *poly2);
extern polynomial *add_polynomial(const polynomial *poly1, const polynomial *poly2);
extern polynomial *sub_polynomial(const polynomial *poly1, const polynomial *poly2);
extern poly_pair   div_polynomial(const polynomial *poly1, const polynomial *poly2);
extern void free_polynomial(polynomial *poly);
extern polynomial *make_polynomial(int n_terms, const term *terms);
extern polynomial *copy_polynomial(const polynomial *poly1);

extern int degree_polynomial(const polynomial *poly);
extern bool zero_polynomial(const polynomial *poly);
extern Rational coeff_for_term_polynomial(const polynomial *poly, unsigned int power);

#endif /* POLYNOMIAL_H_INCLUDED */

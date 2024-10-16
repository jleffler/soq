#include <stdio.h>
#include <complex.h>

/* CMPLX is missing from macOS Big Sur - and probably other versions */
#ifndef CMPLX
#define CMPLX(x, y)  ((double complex)((double)(x) + I * (double)(y)))
#endif

static void munge(double complex c)
{
    printf("(%.2f,%.2f) => ", creal(c), cimag(c));
    c = conj(c);
    printf("(%.2f,%.2f) => %.2f\n", creal(c), cimag(c), cabs(c));
}

int main(void)
{
    double complex c = CMPLX(3, 4);
    munge(c);
    munge(c);
    return 0;
}

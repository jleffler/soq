
#ifdef USE_EXTERN
extern void double_swap(double *d1, double *d2);

void double_swap(double *d1, double *d2)
{
    double d = *d1;
    *d1 = *d2;
    *d2 = d;
}

#else

static inline void double_swap(double *d1, double *d2)
{
    double d = *d1;
    *d1 = *d2;
    *d2 = d;
}

#endif /* USE_EXTERN */

#include <stdio.h>

int main(void)
{
    double a = 1.0;
    double b = 2.0;

    printf("linea: %d - before a(%.2f) b(%.2f)\n", __LINE__, a, b);
    double_swap(&a, &b);
    printf("linea: %d - after  a(%.2f) b(%.2f)\n", __LINE__, a, b);
    return 0;
}

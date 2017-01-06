#include <stdio.h>
#include <math.h>

static inline void f_factorial(void)
{
    float factorial = 1.0;
    for (int i = 1; i < 200; i++)
    {
        factorial *= i;
        if (!isfinite(factorial))
            break;
        printf("%3d! = %20.14e\n", i, factorial);
    }
}

static inline void d_factorial(void)
{
    double factorial = 1.0;
    for (int i = 1; i < 200; i++)
    {
        factorial *= i;
        if (!isfinite(factorial))
            break;
        printf("%3d! = %20.14e\n", i, factorial);
    }
}

static inline void l_factorial(void)
{
    long double factorial = 1.0;
    for (int i = 1; i < 300; i++)
    {
        factorial *= i;
        if (!isfinite(factorial))
            break;
        printf("%3d! = %20.14Le\n", i, factorial);
    }
}

int main(void)
{
    f_factorial();
    putchar('\n');
    d_factorial();
    putchar('\n');
    l_factorial();

    return 0;
}

#include <stdio.h>
#include <math.h>

static inline void f_print(int i, float f)
{
    printf("%3d! = %12.6e\n", i, f);
}

static inline void d_print(int i, double f)
{
    printf("%3d! = %20.14e\n", i, f);
}

static inline void l_print(int i, long double f)
{
    printf("%3d! = %20.14Le\n", i, f);
}

static inline int f_factorial(void)
{
    float factorial = 1.0;
    float old_value = factorial;
    int i;
    for (i = 1; i < 200; i++)
    {
        old_value = factorial;
        factorial *= i;
        if (!isfinite(factorial))
            break;
        if (i <= 12)
            f_print(i, factorial);
    }
    f_print(i - 1, old_value);
    return i - 1;
}

static inline int d_factorial(int f_max)
{
    double factorial = 1.0;
    double old_value = factorial;
    int i;
    for (i = 1; i < 200; i++)
    {
        old_value = factorial;
        factorial *= i;
        if (!isfinite(factorial))
            break;
        if (i <= 12 || (i == f_max + 1 || i == f_max))
            d_print(i, factorial);
    }
    d_print(i - 1, old_value);
    return i - 1;
}

static inline int l_factorial(int f_max, int l_max)
{
    long double factorial = 1.0;
    long double old_value = factorial;
    int i;
    for (i = 1; i < 300; i++)
    {
        old_value = factorial;
        factorial *= i;
        if (!isfinite(factorial))
            break;
        if (i <= 12 ||
            (i == f_max + 1 || i == f_max) ||
            (i == l_max + 1 || i == l_max))
            l_print(i, factorial);
    }
    l_print(i - 1, old_value);
    return i - 1;
}

int main(void)
{
    int f_max = f_factorial();
    putchar('\n');
    int d_max = d_factorial(f_max);
    putchar('\n');
    int l_max = l_factorial(f_max, d_max);
    putchar('\n');
    printf("Maximum: %d!\n", l_max);

    return 0;
}

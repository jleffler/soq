#include <stdio.h>

int main(void)
{
    int p = 0;
    int n = 0;
    int z = 0;

    int v;
    while (scanf("%d", &v) == 1)
    {
        if (v > 0)
            p++;
        else if (v < 0)
            n++;
        else
            z++;
    }

    double t = p + n + z;

    double fp = p / t;
    double fn = n / t;
    double fz = z / t;

    printf("%f\n%f\n%f\n", fp, fn, fz);
    return 0;
}

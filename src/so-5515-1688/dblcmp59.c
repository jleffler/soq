/* SO 5515-1688 */
#include <math.h>

/* Belongs in a header! */
extern int cmp_double(const void *v1, const void *v2);

/* Sort doubles, with NaNs coming first */
/* Switch return values -1 and +1 after testing n1, n2 to sort NaNs last */
int cmp_double(const void *v1, const void *v2)
{
    double d1 = *(const double *)v1;
    double d2 = *(const double *)v2;
    int n1 = isnan(d1);
    int n2 = isnan(d2);

    if (n1 && n2)
        return 0;
    if (n1)
        return -1;
    if (n2)
        return +1;
    if (d1 < d2)
        return -1;
    if (d1 > d2)
        return +1;
    if (d1 != 0.0)
        return 0;
    int s1 = signbit(d1);
    int s2 = signbit(d2);
    if (s1 != s2)
        return (s1) ? -1 : +1;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

static void dump_doubles(const char *tag, int num, double values[num])
{
    printf("%s (%d):\n", tag, num);
    int line_len = 0;
    for (int i = 0; i < num; i++)
    {
        int n = printf(" %+12.4f", values[i]);
        if (n <= 0)
            break;
        line_len += n;
        if (line_len >= 60)
        {
            line_len = 0;
            putchar('\n');
        }
    }
    if (line_len > 0)
        putchar('\n');
}

int main(void)
{
    enum { NUM_VALUES = 50 };
    double values[NUM_VALUES];

    int i = 0;

    for (i = 0; i < NUM_VALUES; i++)
    {
        if (scanf("%lf", &values[i]) != 1)
            break;
    }

    dump_doubles("Before sort", i, values);
    qsort(values, i, sizeof(values[0]), cmp_double);
    dump_doubles("After sort", i, values);

    return 0;
}

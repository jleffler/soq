/* SO 4203-5818 - Calculate all triangles with given perimeter */
#include <stdio.h>
#include <stdlib.h>

static int int_cmp(const void *va, const void *vb)
{
    int a = *(int *)va;
    int b = *(int *)vb;
    return (a > b) - (a < b);
}

int main(void)
{
    int p, a, b, c;
    for (p = 3; p < 30; p++)
    {
        for (a = 1; 2 * a < p; a++)
        {
            for (b = (p - a) / 2; (p - 2 * a) > 0 && (p - 2 * b) > 0 && (2 * a + 2 * b - p) > 0; b++)
            {
                c = p - (a + b);
                {
                int d[] = { a, b, c };
                qsort(d, 3, sizeof(d[0]), int_cmp);
                printf("%d: %d, %d, %d\n", p, d[0], d[1], d[2]);
                }
            }
        }
    }
    return 0;
}

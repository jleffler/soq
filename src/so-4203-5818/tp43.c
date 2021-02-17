/* SO 4203-5818 - Calculate all triangles with given perimeter */

#include <stdio.h>

int main(void)
{
    for (int p = 3; p < 30; p++)
    {
        for (int a = 1; a <= p / 2; a++)
        {
            for (int b = 1; b + a < p; b++)
            {
                int c = p - (a + b);
                if (a + b <= c || a + c <= b || b + c <= a)
                    continue;
                if (a <= b && b <= c)
                    printf("%d: %d, %d, %d\n", p, a, b, c);
            }
        }
    }
    return 0;
}

#include <stdio.h>

int main(void)
{
    int p, a, b, c;
    // printf("Enter a perimeter: ");
    // scanf("%d", &p);
    for (p = 3; p < 30; p++)
    {
        printf("Triangles with perimeter: %d\n", p);

        for (a = 1; 2 * a < p; a++)
        {
            for (b = (p - a) / 2; (p - 2 * a) > 0 && (p - 2 * b) > 0 && (2 * a + 2 * b - p) > 0; b++)
            {
                c = p - (a + b);
                if (a <= b && b <= c)
                    printf("%d, %d, %d\n", a, b, c);
            }
        }
    }
    return 0;
}

/* SO 4560-1288 */
/* How to reshape a flat array into a 2D array in C */
#include <stdio.h>

static void func(const unsigned int x, const int *flat_array)
{
    const int (*reshaped)[x] = (const int (*)[x])flat_array;
    for (unsigned int i = 0; i < x; i++)
    {
        for (unsigned int j = 0; j < x; j++)
            printf("%3d", reshaped[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    int flat[] =
    {
        /* random -n 25 10 99 | commalist -n 5 -B 8 */
        73, 34, 76, 48, 17,
        25, 71, 11, 87, 74,
        18, 87, 11, 47, 32,
        33, 62, 41, 55, 90,
        90, 28, 69, 58, 29,
    };

    for (int i = 0; i < 5; i++)
    {
        printf("R[%d]", i);
        for (int j = 0; j < 5; j++)
            printf(" [%d] = %2d", j, flat[i * 5 + j]);
        putchar('\n');
    }

    func(5, flat);
    return 0;
}

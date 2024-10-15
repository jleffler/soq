/* SO 7531-3779 */

#include <stdio.h>
#include <stdlib.h>

static void dump_array(const char *tag, size_t rows, size_t cols, int array[rows][cols])
{
    printf("%s (%zux%zu):\n", tag, rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        printf("%2zu:", r);
        for (size_t c = 0; c < cols; c++)
            printf(" %5d", array[r][c]);
        putchar('\n');
    }
}

int main(void)
{
    size_t rows = 13;
    size_t cols = 8;
    int (*array)[8] = malloc(sizeof(int [rows][cols]));

    for (size_t r = 0; r < rows; r++)
    {
        int sign = -1;
        for (size_t c = 0; c < cols; c++)
        {
            array[r][c] = sign * ((r + 1) * 100 + c + 1);
            sign = -sign;
        }
    }

    dump_array("Array 1", rows, cols, array);

    free(array);
    return 0;
}

#include <stdio.h>

static void print_matrix(size_t rows, size_t cols, const int data[rows][cols])
{
    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < cols; c++)
        {
            printf("%s%3d", pad, data[r][c]);
            pad = "  ";
        }
        putchar('\n');
    }
}

int main(void)
{
    /* Created by: gen_matrix -r 3 -c 5 -L 0 -H 999 -n matrix -E -w 3 -S 0x08C777A9 -i */
    /* Random seed: 0x08C777A9 */
    int matrix[3][5] =
    {
        { 984, 843, 464, 599,  17, },
        { 876, 173, 647,  61, 387, },
        { 138, 245, 718, 981, 629, },
    };
    enum { MATRIX_ROWS = 3, MATRIX_COLS = 5 };

    print_matrix(MATRIX_ROWS, MATRIX_COLS, matrix);

    return 0;
}

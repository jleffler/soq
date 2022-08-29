#include <stdio.h>

enum { MATRIX_ROWS = 3, MATRIX_COLS = 5 };

static void print_matrix(const int data[MATRIX_ROWS][MATRIX_COLS])
{
    for (size_t r = 0; r < MATRIX_ROWS; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < MATRIX_COLS; c++)
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
    int matrix[MATRIX_ROWS][MATRIX_COLS] =
    {
        { 984, 843, 464, 599,  17, },
        { 876, 173, 647,  61, 387, },
        { 138, 245, 718, 981, 629, },
    };

    print_matrix(matrix);

    return 0;
}

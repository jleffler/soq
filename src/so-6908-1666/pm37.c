/* SO 6908-1666 */

#include <stdio.h>

static void print_submatrix(int nrows, int ncols, char matrix[nrows][ncols],
                            int crow, int ccol, int rsize, int csize)
{
    int min_row = crow - (rsize / 2);
    int max_row = min_row + rsize;
    int min_col = ccol - (csize / 2);
    int max_col = min_col + csize;

    /* Array bounds? */
    if (min_col < 0)
        min_col = 0;
    if (min_row < 0)
        min_row = 0;
    if (max_col > ncols)
        max_col = ncols;
    if (max_row > nrows)
        max_row = nrows;

    printf("R = %d, C = %d, Centre (%d, %d), Size (%d, %d) ",
            nrows, ncols, crow, ccol, rsize, csize);
    printf("Columns [%d..%d), Rows [%d..%d)\n", min_col, max_col, min_row, max_row);
    for (int i = min_row; i < max_row; i++)
    {
        for (int j = min_col; j < max_col; j++)
            putchar(matrix[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    char array[7][8] =
    {
        { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' },
        { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i' },
        { 'k', 'j', 'h', 'g', 'f', 'd', 's', 'a' },
        { 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'q' },
        { 'g', 'z', 'p', 'l', 'k', 'h', 'n', 'a' },
        { 'q', 'e', 'm', 'a', 'c', 't', 'u', 'p' },
        { 'r', 'b', 'l', 't', 'k', 'f', 'b', 'z' },
    };

    print_submatrix(7, 8, array, 6, 2, 5, 5);
    print_submatrix(7, 8, array, 3, 6, 5, 5);
    print_submatrix(7, 8, array, 3, 3, 5, 5);
    /* Print whole matrix, but it isn't a good use of the interface */
    print_submatrix(7, 8, array, 3, 4, 7, 8);

    return 0;
}

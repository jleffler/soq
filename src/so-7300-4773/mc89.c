/* SO 7300-4773 */
#include <stdio.h>
#include "matmaxfldwid.h"

static void dump_matrix(const char *tag, size_t rows, size_t cols, int matrix[rows][cols])
{
    printf("%s (%zux%zu):\n", tag, rows, cols);
    int fldwid = max_field_width(rows, cols, matrix);

    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < cols; c++)
        {
            printf("%s%*d", pad, fldwid, matrix[r][c]);
            pad = " ";
        }
        putchar('\n');
    }
}

static void count_matrix(size_t rows, size_t cols, int matrix[rows][cols], int result[rows][cols])
{
    for (size_t c = 0; c < cols; c++)
    {
        for (size_t r = 0; r < rows; r++)
        {
            int value = matrix[r][c];
            int count = 0;
            for (size_t i = r + 1; i < rows; i++)
            {
                if (value >= matrix[i][c])
                    count++;
            }
            result[r][c] = count;
        }
    }
}

int main(void)
{
    /* Created by: gen_matrix -n N -L -99 -H +99 -r 5 -c 6 -E -w 3 -i */
    /* Random seed: 0x8E280D99 */
    int N[5][6] =
    {
        {  79, -40,  52,  26, -35,  86, },
        { -68,  13,  21, -34,  -9,  10, },
        {   7,  72,  68,  44,  45,  -3, },
        {  25,  78,  86,  81,  51, -33, },
        { -38, -89,  42,  61, -24,  69, },
    };
    enum { N_ROWS = 5, N_COLS = 6 };
    int result1[N_ROWS][N_COLS];

    dump_matrix("N", N_ROWS, N_COLS, N);
    count_matrix(N_ROWS, N_COLS, N, result1);
    dump_matrix("Result", N_ROWS, N_COLS, result1);
    putchar('\n');

    /* Created by: gen_matrix -n matrix -L -9 -H +9 -r 8 -c 6 -E -w 2 -i */
    /* Random seed: 0x00B6E0F7 */
    int matrix[8][6] =
    {
        { -3, -5,  5, -4,  7,  9, },
        {  9,  9, -9, -2,  4, -3, },
        {  2,  5, -8,  9, -7, -5, },
        {  5, -9, -5,  8,  2,  2, },
        {  5,  2, -5, -9,  4, -5, },
        {  1, -5, -3, -2,  4,  5, },
        {  8,  5,  3, -2,  1,  9, },
        {  4,  3,  2,  2,  9, -1, },
    };
    enum { MATRIX_ROWS = 8, MATRIX_COLS = 6 };
    int result3[MATRIX_ROWS][MATRIX_COLS];

    dump_matrix("Matrix", MATRIX_ROWS, MATRIX_COLS, matrix);
    count_matrix(MATRIX_ROWS, MATRIX_COLS, matrix, result3);
    dump_matrix("Result", MATRIX_ROWS, MATRIX_COLS, result3);
    putchar('\n');

    int M[2][2] =
    {
        {4, 6},
        {9, 2},
    };
    int result2[2][2];

    dump_matrix("M", 2, 2, M);
    count_matrix(2, 2, M, result2);
    dump_matrix("Result", 2, 2, result2);
    putchar('\n');

    printf("Original code:\n");
    dump_matrix("M", 2, 2, M);

    int i, j, row, col;
    int arr[2][2] = {0};
    int t;
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            t = M[i][j];
            for (col = 0; col < 2; ++col)
            {
                for (row = 0; row < 2; ++row)
                {
                    if (row == i && col == j)
                        continue;
                    else if (t >= M[row][col])
                        arr[i][j] += 1;
                }
            }
        }
    }

    printf("The Matrix:\n");
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
            printf("%d  ", arr[i][j]);
        printf("\n");
    }

    return 0;
}

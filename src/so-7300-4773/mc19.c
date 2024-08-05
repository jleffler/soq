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
            for (size_t i = 0; i < rows; i++)
            {
                if (value >= matrix[i][c])
                    count++;
            }
            result[r][c] = count - 1;
        }
    }
}

static void test_matrix(const char *name, size_t rows, size_t cols, int matrix[rows][cols])
{
    int result[rows][cols];

    dump_matrix(name, rows, cols, matrix);
    count_matrix(rows, cols, matrix, result);
    dump_matrix("Result", rows, cols, result);
    putchar('\n');
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
    test_matrix("N", N_ROWS, N_COLS, N);

    /* Created by: gen_matrix -n matrix1 -L -9 -H +9 -r 8 -c 6 -E -w 2 -i */
    /* Random seed: 0x00B6E0F7 */
    int matrix1[8][6] =
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
    enum { MATRIX1_ROWS = 8, MATRIX1_COLS = 6 };
    test_matrix("Matrix 1", MATRIX1_ROWS, MATRIX1_COLS, matrix1);

    int M[2][2] =
    {
        {4, 6},
        {9, 2},
    };
    test_matrix("M", 2, 2, M);

    /* Created by: gen_matrix -n matrix2 -L -9999 -H +9999 -r 4 -c 3 -E -w 5 -i */
    /* Random seed: 0x75DCF407 */
    int matrix2[4][3] =
    {
        {  8008, -6894, -4062, },
        {  7755,  2443,  3067, },
        {   820, -1761, -9612, },
        {  -118, -6303, -2996, },
    };
    enum { MATRIX2_ROWS = 4, MATRIX2_COLS = 3 };
    test_matrix("Matrix 2", MATRIX2_ROWS, MATRIX2_COLS, matrix2);

    return 0;
}

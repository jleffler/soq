/* SO 7085-1570 */
#include <stdio.h>
#include <assert.h>

static int SubMatrixHere(int r, int c,
                         int rows1, int cols1, const int m1[rows1][cols1],
                         int rows2, int cols2, const int m2[rows2][cols2])
{
    assert(r + rows2 <= rows1 && c + cols2 <= cols1);
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            if (m1[r+i][c+j] != m2[i][j])
                return 0;
        }
    }
    return 1;
}

static int CheckSubMatrix(int rows1, int cols1, const int m1[rows1][cols1],
                          int rows2, int cols2, const int m2[rows2][cols2])
{
    if (rows1 < rows2 || cols1 < cols2)
        return 0;

    int ub_rows = rows1 - rows2 + 1;
    int ub_cols = cols1 - cols2 + 1;
    for (int i = 0; i < ub_rows; i++)
    {
        for (int j = 0; j < ub_cols; j++)
        {
            /* The test for m1[i][j] == m2[0][0] is a big saving */
            if (m1[i][j] == m2[0][0] &&
                SubMatrixHere(i, j, rows1, cols1, m1, rows2, cols2, m2))
                return 1;
        }
    }
    return 0;
}

static int max_field_width(int r, int c, const int matrix[r][c])
{
    int min_val = matrix[0][0];
    int max_val = matrix[0][0];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (matrix[i][j] < min_val)
                min_val = matrix[i][j];
            if (matrix[i][j] > max_val)
                max_val = matrix[i][j];
        }
    }
    int fld_width = snprintf(0, 0, "%d", max_val);
    if (min_val < 0)
    {
        int min_width = snprintf(0, 0, "%d", min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
    return fld_width;
}

static void dump_matrix(const char *tag, int rows, int cols, const int matrix[rows][cols])
{
    int fld_width = max_field_width(rows, cols, matrix);
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        const char *pad = "{ ";
        int length = 0;
        for (int j = 0; j < cols; j++)
        {
            length += printf("%s%*d", pad, fld_width, matrix[i][j]);
            if (length > 60 && j < cols - 1)
            {
                putchar('\n');
                length = 0;
                pad = "  ";
            }
            else
                pad = ", ";
        }
        if (length > 0)
            puts(" }");
    }
    putchar('\n');
}

static void test_submatrix(const char *t1, int r1, int c1, const int m1[r1][c1],
                           const char *t2, int r2, int c2, const int m2[r2][c2])
{
    dump_matrix(t1, r1, c1, m1);
    dump_matrix(t2, r2, c2, m2);
    if (CheckSubMatrix(r1, c1, m1, r2, c2, m2))
        printf("%s is a sub-matrix of %s\n", t2, t1);
    else
        printf("%s is not a sub-matrix of %s\n", t2, t1);
    putchar('\n');
}

int main(void)
{
    int m1[4][4] =
    {
        { 1, 4, 6, 8 },
        { 2, 5, 7, 0 },
        { 3, 6, 9, 0 },
        { 4, 5, 8, 1 },
    };
    int m2[3][3] =
    {
        { 1, 4, 6 },
        { 2, 5, 7 },
        { 3, 6, 9 },
    };
    int m3[3][3] =
    {
        { 5, 7, 0 },
        { 6, 9, 0 },
        { 5, 8, 1 },
    };
    int m4[3][3] =
    {
        { 1, 4, 6 },
        { 2, 5, 7 },
        { 3, 6, 2 },
    };

    test_submatrix("m1", 4, 4, m1, "m2", 3, 3, m2);
    test_submatrix("m1", 4, 4, m1, "m3", 3, 3, m3);
    test_submatrix("m1", 4, 4, m1, "m4", 3, 3, m4);

    const int m5[6][4] =
    {
        { 68, 59, 61, 70 },
        { 65, 86, 44,  9 },
        { 23, 55, 24, 31 },
        { 51, 21, 10, 99 },
        { 19, 99, 43, 95 },
        { 64, 25, 79, 67 },
    };

    const int m6[2][3] =
    {
        { 55, 24, 31 },
        { 21, 10, 99 },
    };

    const int m7[4][2] =
    {
        { 44,  9 },
        { 24, 31 },
        { 10, 99 },
        { 43, 96 },
    };
    test_submatrix("m5", 6, 4, m5, "m6", 2, 3, m6);
    test_submatrix("m5", 6, 4, m5, "m7", 4, 2, m7);

    /* Created by: gen_matrix -C -n m8 -r 10 -c 16 -i */
    /* Random seed: 0x332BBFCD */
    const int m8[10][16] =
    {
        { 85, 51, 61, 76, 93, 83,  0, 18, 36, 46, 11, 49, 55, 83, 59, 89, },
        { 50,  9, 35, 63, 93, 58,  8, 59,  1, 47, 56, 13, 62, 73,  1, 96, },
        { 43, 57, 66, 39,  8, 50, 70, 57, 89, 91, 46, 70, 12, 87, 21, 67, },
        { 70,  4, 43, 59,  7, 38, 18, 41, 97, 87, 59,  0, 22, 20, 94, 61, },
        { 16, 56, 15,  3, 72, 45, 35, 94, 30, 56, 54,  7, 23, 79, 54, 32, },
        { 11,  2, 55,  3, 70, 16, 15, 25, 68, 99, 99, 65, 20,  5, 86, 68, },
        { 97, 91, 28, 67, 77,  8, 57,  0, 35,  9, 78, 10, 45, 98,  6, 91, },
        {  9,  3, 78, 64, 76, 68, 98, 76, 26, 50, 66, 77, 71, 27, 78,  4, },
        {  7, 82, 37, 94, 33, 95, 50, 97, 14, 69, 27,  1, 64, 25, 23, 16, },
        { 36, 67, 18, 61, 10, 15,  4, 42, 57,  8, 76, 34,  2, 24, 17,  7, },
    };

    const int m9[2][2] =
    {
        { 23, 16 },
        { 17,  7 },
    };

    test_submatrix("m8", 10, 16, m8, "m9", 2, 2, m9);

    /* Created by: gen_matrix -C -n m8 -r 10 -c 20 -i */
    /* Random seed: 0x4568167F */
    const int m10[10][20] =
    {
        { 11,  1, 50,  0,  7, 89, 99,  9, 54, 94, 76, 91, 51, 64, 29,  3, 15, 69, 96,  3, },
        { 34, 66, 60,  0, 79, 94, 83, 29, 54, 61, 27, 57, 34,  8, 25, 57, 19, 17, 89, 19, },
        { 90, 30,  6, 23, 46, 94,  8, 20, 43,  0, 87, 88, 15, 35, 60, 88, 73, 43, 58, 69, },
        { 76, 37, 41, 44,  0, 54,  4, 54, 57, 97, 71,  1, 50, 38, 69, 23,  4, 38, 56, 25, },
        { 61, 38, 81, 20, 77, 91, 49, 50,  0, 99, 65, 89,  4, 93, 79, 85,  1,  3, 25, 36, },
        { 85, 54,  6, 99, 73, 55, 21, 66, 69, 21, 66, 27, 38,  9, 85, 70, 15,  0,  8, 80, },
        { 70,  6, 88, 36, 71, 20, 67, 26, 21,  4,  3, 26, 47, 37, 73, 23, 97, 85, 41, 12, },
        { 73, 21, 88, 11, 38,  9, 68, 72, 77, 84, 21, 69, 27, 23, 94,  4, 85, 61, 37, 74, },
        { 34,  8, 87, 24, 80, 53, 20, 20, 12, 15, 66, 56, 20, 57, 75, 80, 73, 62, 28, 86, },
        { 97, 47, 24, 15, 42, 36, 13, 53,  7, 42,  4, 87, 67, 73,  0, 37, 36, 95, 79, 43, },
    };

    const int m11[3][3] =
    {
        { 61, 37, 74, },
        { 62, 28, 86, },
        { 95, 79, 43, },
    };

    test_submatrix("m10", 10, 20, m10, "m11", 3, 3, m11);

    return 0;
}

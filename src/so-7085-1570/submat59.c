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

static void dump_matrix(const char *tag, int rows, int cols, const int matrix[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        const char *pad = "";
        int length = 0;
        for (int j = 0; j < cols; j++)
        {
            length += printf("%s%d", pad, matrix[i][j]);
            if (length > 60)
            {
                putchar('\n');
                length = 0;
                pad = "";
            }
            else
                pad = ", ";
        }
        if (length > 0)
            putchar('\n');
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

    return 0;
}

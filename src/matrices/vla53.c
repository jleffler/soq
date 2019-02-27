#include <stdio.h>
#include <stdlib.h>

/* VLA notation using incomplete * notation in function prototypes */

static void mat_multiply(int x, int y, int z, int mat1[][*], int mat2[][*], int result[][*]);
static void mat_print(const char *tag, int m, int n, int matrix[][*]);

int main(void)
{
    int matrix1[][4] =
    {
        //random -n 20 -- -999 999 | commalist -n 4 -B 8 -b '{ ' -T ' },' -R -W 4
        {  421,  174,  389, -713, },
        {  799, -852,  998,  156, },
        { -414, -957,  491, -879, },
        { -461,  290, -274, -209, },
        { -878, -247, -778, -716, },
    };
    int matrix2[4][3] =
    {
        // random -n 12 -- -999 999 | commalist -n 3 -B 8 -b '{ ' -T ' },' -R -W 4
        { -612, -190,  297, },
        { -989,  705,  875, },
        {  961, -870,  599, },
        {   12, -267,  877, },
    };

    int matrix3[5][3];
    mat_multiply(5, 4, 3, matrix1, matrix2, matrix3);
    mat_print("matrix1", 5, 4, matrix1);
    mat_print("matrix2", 4, 3, matrix2);
    mat_print("matrix3", 5, 3, matrix3);
    return 0;
}

static void mat_multiply(int x, int y, int z, int mat1[][y], int mat2[][z], int result[][z])
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < z; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < y; k++)
                 result[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

static void mat_print(const char *tag, int m, int n, int matrix[][n])
{
    printf("%s (%dx%d):\n", tag, m, n);
    for (int i = 0; i < m; i++)
    {
        const char *pad = "";
        for (int j = 0; j < n; j++)
        {
            printf("%s%8d", pad, matrix[i][j]);
            pad = " ";
        }
        putchar('\n');
    }
}


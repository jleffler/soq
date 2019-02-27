/* SO 1719-2011 */
#if defined(__cplusplus)
#error "This code uses VLA and should not compile under C++"
#endif

#include <stdio.h>

static float m1[3][4] =
{
    { +1.0F, -0.02F, +0.76F, +3.14F },
    { +0.0F, +1.97F, +2.13F, +0.21F },
    { +4.1F, -1.37F, -1.00F, -2.11F },
};
static float m2[4][2] =
{
    { +1.50F, -7.22F },
    { +2.31F, +1.99F },
    { -0.77F, +4.72F },
    { -3.41F, -5.26F },
};

void matrix_multiply(int m, int p, int n, float matrix1[m][p],
                     float matrix2[p][n], float output[m][n]);
void matrix_print(const char *tag, int m, int n, float matrix[m][n]);
void matrix_zero(int m, int n, float matrix[m][n]);

int main(void)
{
    float result[3][2];
    matrix_multiply(3, 4, 2, m1, m2, result);
    matrix_print("m1", 3, 4, m1);
    matrix_print("m2", 4, 2, m2);
    matrix_print("m3", 3, 2, result);
}

void matrix_zero(int m, int n, float matrix[m][n])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0.0;
}

void matrix_multiply(int m, int p, int n, float matrix1[m][p],
                     float matrix2[p][n], float output[m][n])
{
    matrix_zero(m, n, output);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < n; k++)
                output[i][k] += matrix1[i][j] * matrix2[j][k];
}

void matrix_print(const char *tag, int m, int n, float matrix[m][n])
{
    printf("%s (%d x %d):\n", tag, m, n);
    for (int i = 0; i < m; i++)
    {
        char *pad = "[ ";
        for (int j = 0; j < n; j++)
        {
            printf("%s%+7.3f", pad, matrix[i][j]);
            pad = ", ";
        }
        printf("%s", " ]\n");
    }
}

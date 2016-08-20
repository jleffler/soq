/* SO 17192011 */
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

void matrix_multiply(float *matrix1, float *matrix2, int m, int p, int n, float *output);
void matrix_print(const char *tag, int m, int n, float *matrix);
void matrix_zero(float *matrix, int n, int m);

int main(void)
{
    float result[3][2];
    matrix_multiply(&m1[0][0], &m2[0][0], 3, 4, 2, &result[0][0]);
    matrix_print("m1", 3, 4, &m1[0][0]);
    matrix_print("m2", 4, 2, &m2[0][0]);
    matrix_print("m3", 3, 2, &result[0][0]);
    return 0;
}

void matrix_zero(float *matrix, int n, int m)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            matrix[i*n+j] = 0.0;
}

/*
** Matrix Multiplication Routine
** matrix1 = input matrix (m x p)
** matrix2 = input matrix (p x n)
** m = number of rows in matrix1
** p = number of columns in matrix1 and number of rows in matrix2
** n = number of columns in matrix2
** output = output matrix = matrix1 * matrix2 (m x n)
*/
void matrix_multiply(float *matrix1, float *matrix2, int m, int p, int n, float *output)
{
    int i, j, k;

    matrix_zero(output, m, n);

    for (i = 0; i < m; i++)
        for (j = 0; j < p; j++)
            for (k = 0; k < n; k++)
                output[i*n+k] += matrix1[i*p+j] * matrix2[j*n+k];
}

void matrix_print(const char *tag, int m, int n, float *matrix)
{
    int i, j;

    printf("%s (%d x %d):\n", tag, m, n);
    for (i = 0; i < m; i++)
    {
        const char *pad = "[ ";
        for (j = 0; j < n; j++)
        {
            printf("%s%+7.3f", pad, matrix[i*n+j]);
            pad = ", ";
        }
        printf("%s", " ]\n");
    }
}

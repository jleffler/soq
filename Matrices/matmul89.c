/* SO 17192011 */
#include <stdio.h>

#define N 2
static float m1[N][N] = {{1.0, -0.02}, {0.0, 1.0}};
static float m2[N][1] = {{1.5f}, {1.5f}};
static float result[1][N];

void matrix_multiply(float *matrix1, float *matrix2, int m, int p, int n, float *output);
void matrix_print(const char *tag, int m, int n, float *matrix);
void matrix_zero(float *matrix, int n, int m);

int main(void)
{
    matrix_multiply(&m1[0][0], &m2[0][0], N, N, 1, &result[0][0]);
    matrix_print("m1", N, N, &m1[0][0]);
    matrix_print("m2", N, 1, &m2[0][0]);
    matrix_print("m3", 1, N, &result[0][0]);
    return 0;
}

void matrix_zero(float *matrix, int n, int m)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            matrix[i*n+j] = 0.0;
    /* Or
    for (i = 0; i < m * n; i++)
        matrix[i] = 0.0;
    */
    /* Or even
    memset(matrix, '\0', n * m * sizeof(float));
    */
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
        const char *pad = "[";
        for (j = 0; j < n; j++)
        {
            printf("%s%6.3f", pad, matrix[i*n+j]);
            pad = ", ";
        }
        printf("%s", " ]\n");
    }
}

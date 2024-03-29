/* SO 1719-2011 */
/* Matrix multiplication using C99 and VLA notation */
#if defined(__cplusplus)
#error "This code uses VLA and should not compile under C++"
#endif

#include <stdio.h>

static double m1[3][4] =
{
    { +1.0, -0.02, +0.76, +3.14 },
    { +0.0, +1.97, +2.13, +0.21 },
    { +4.1, -1.37, -1.00, -2.11 },
};
static double m2[4][2] =
{
    { +1.50, -7.22 },
    { +2.31, +1.99 },
    { -0.77, +4.72 },
    { -3.41, -5.26 },
};

void matrix_multiply(int m, int p, int n, double matrix1[m][p],
                     double matrix2[p][n], double output[m][n]);
void matrix_multiply_arcane(int m, int p, int n, double matrix1[m][p],
                            double matrix2[p][n], double output[m][n]);
void matrix_print(const char *tag, int m, int n, double matrix[m][n]);
void matrix_zero(int m, int n, double matrix[m][n]);

int main(void)
{
    double result[3][2];
    matrix_print("m1", 3, 4, m1);
    matrix_print("m2", 4, 2, m2);
    matrix_multiply(3, 4, 2, m1, m2, result);
    matrix_print("m3 - simple", 3, 2, result);
    matrix_multiply_arcane(3, 4, 2, m1, m2, result);
    matrix_print("m3 - arcane", 3, 2, result);
}

/* This code simulates how you'd multiply two matrices by hand */
void matrix_multiply(int m, int p, int n, double matrix1[m][p],
                     double matrix2[p][n], double output[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < p; k++)
                sum += matrix1[i][k] * matrix2[k][j];
            output[i][j] = sum;
        }
    }
}

void matrix_zero(int m, int n, double matrix[m][n])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0.0;
}

/* Although correct, the sequence of nested loops here is arcane */
/* It also requires the result matrix to be zeroed first */
/* This has poor locality of reference - it skips around the output matrix */
void matrix_multiply_arcane(int m, int p, int n, double matrix1[m][p],
                            double matrix2[p][n], double output[m][n])
{
    matrix_zero(m, n, output);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < n; k++)
                output[i][k] += matrix1[i][j] * matrix2[j][k];
}

void matrix_print(const char *tag, int m, int n, double matrix[m][n])
{
    printf("%s (%d x %d):\n", tag, m, n);
    for (int i = 0; i < m; i++)
    {
        char *pad = "[ ";
        for (int j = 0; j < n; j++)
        {
            printf("%s%+7.4f", pad, matrix[i][j]);
            pad = ", ";
        }
        printf("%s", " ]\n");
    }
}

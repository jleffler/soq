#include <stdio.h>

#define N 2
static float m1[N][N] = {{1.0, -0.02}, {0.0, 1.0}};
static float m2[N][1] = {{1.5f}, {1.5f}};
static float result[1][N];

void matrix_multiply(int m, int p, int n, float matrix1[m][p], float matrix2[p][n], float output[m][n]);
void matrix_print(const char *tag, int m, int n, float matrix[m][n]);

int main(void)
{
    matrix_multiply(N, N, 1, m1, m2, result);
    matrix_print("m1", N, N, m1);
    matrix_print("m2", N, 1, m2);
    matrix_print("m3", 1, N, result);
}

void matrix_multiply(int m, int p, int n, float matrix1[m][p], float matrix2[p][n], float output[m][n])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            output[i][j] = 0.0;

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
        char *pad = "[";
        for (int j = 0; j < n; j++)
        {
            printf("%s%6.3f", pad, matrix[i][j]);
            pad = ", ";
        }
        printf("%s", " ]\n");
    }
}

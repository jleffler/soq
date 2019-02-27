/* SO 4576-0666 */
#include <stdio.h>
#include <stdlib.h>

static void free_mtrx(int **mtrx, int rows)
{
    for (int i = 0; i < rows; i++)
        free(mtrx[i]);
    free(mtrx);
}

static int **multiplying(int **A, int **B, int rows, int cols)
{
    int **C;
    C = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < cols; i++)
    {
        C[i] = (int *)malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++)
            C[i][j] = (A[i][j]) * (B[i][j]);
    }
    return C;
}

static void print_mtrx(const char *tag, int w, int N, int M, int **matrix)
{
    printf("%s (%dx%d):\n", tag, N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%*d", w, matrix[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    enum { EX2_SIZE = 3, EX3_SIZE = 3 };
    int f_matrix[EX2_SIZE][EX2_SIZE] = { {1, 2, 3}, {1, 4, 7}, {1, 5, 9} };
    int s_matrix[EX2_SIZE][EX2_SIZE] = { {9, 8, 7}, {4, 5, 6}, {0, 9, 6} };
    int m1_rows = EX2_SIZE, m1_cols = EX2_SIZE;
    int m2_rows = EX2_SIZE, m2_cols = EX2_SIZE; // For tester can change easily
    int *f[] = { &f_matrix[0][0], &f_matrix[1][0], &f_matrix[2][0] };
    int *s[] = { &s_matrix[0][0], &s_matrix[1][0], &s_matrix[2][0] };
    int **new_matrix;

    if (m1_rows != m2_rows || m1_cols != m2_cols)
        return 0;

    print_mtrx("F", 3, EX2_SIZE, EX2_SIZE, f);
    print_mtrx("S", 3, EX3_SIZE, EX3_SIZE, s);

    new_matrix = multiplying(f, s, m1_rows, m1_cols);
    print_mtrx("R", 3, m1_rows, m1_cols, new_matrix);
    free_mtrx(new_matrix, m1_cols);

    return 0;
}

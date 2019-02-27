/* SO 4576-0666 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static
int (*matrix_multiply(int A_rows, int A_cols, int B_cols,
                      int A[A_rows][A_cols], int B[A_cols][B_cols]))[5]  // Ghastly hack!
{
    int (*C)[B_cols] = malloc(sizeof(int [A_rows][B_cols]));
    for (int i = 0; i < A_rows; i++)
    {
         for (int j = 0; j < B_cols; j++)
         {
              int sum = 0;
              for (int k = 0; k < A_cols; k++)
                  sum += A[i][k] * B[k][j];
              C[i][j] = sum;
         }
    }
    return C;
}

static void print_matrix(const char *tag, int w, int N, int M, int matrix[N][M])
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
    enum { N = 3, M = 4, P = 4, Q = 5 };
    int A[N][M] =
    {
        { 41, 76, 70, 42, },
        { 70, 62, 77, 74, },
        { 49, 55, 43, 65, },
    };
    int B[P][Q] =
    {
        { 73, 33, 42, 72, 65, },
        { 69, 30, 83, 83, 64, },
        { 90, 74, 84, 51, 23, },
        { 62, 45, 84, 46, 43, },
    };
    static_assert(M == P, "Matrix dimensions are mismatched");  // C11
    int (*C)[Q];
    print_matrix("A", 3, N, M, A);
    print_matrix("B", 3, P, Q, B);
    C = matrix_multiply(N, M, Q, A, B);
    print_matrix("C", 6, N, Q, C);
    free(C);
    return 0;
}

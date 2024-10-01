/* SO 6511-7221 */
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifndef N
#define N 128
#endif

typedef struct Matrix
{
    int    size;
    float **data;
} Matrix;

static size_t cnt_create = 0;
static size_t cnt_destroy = 0;
static size_t cnt_NxN = 0;

static void err_nomemory(const char *file, const char *func, int line, size_t size)
{
    fprintf(stderr, "%s:%s():%d: out of memory attempting to allocate %zu bytes "
            "(%d: %s)\n", file, func, line, size, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

static void matrix_destroy(Matrix *M)
{
    cnt_destroy++;
    for (int i = 0; i < M->size; i++)
        free(M->data[i]);
    free(M->data);
}

static Matrix matrix_create(int n)
{
    cnt_create++;
    Matrix M = { .size = n, .data = malloc(n * sizeof(float *)) };
    if (M.data == NULL)
        err_nomemory(__FILE__, __func__, __LINE__, n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        if ((M.data[i] = (float *)malloc(n * sizeof(float))) == NULL)
            err_nomemory(__FILE__, __func__, __LINE__, n * sizeof(float));
    }
    return M;
}

static void matrix_print(const char *tag, const Matrix *M)
{
    printf("%s (%dx%d):", tag, M->size, M->size);
    if (M->size > 16)
    {
        printf(" Printing suppressed - matrix too large\n");
        return;
    }
    putchar('\n');
    char buffer[32];
    int len = snprintf(buffer, sizeof(buffer), "%d", M->size);
    for (int i = 0; i < M->size; i++)
    {
        printf("[%*d]: ", len, i);
        const char *pad = "";
        for (int j = 0; j < M->size; j++)
        {
            printf("%s%7.4f", pad, M->data[i][j]);
            pad = "  ";
        }
        printf("\n");
    }
}

static void matrix_multiply_NxN(const Matrix *A, const Matrix *B, Matrix *C)
{
    cnt_NxN++;
    assert(A->size == B->size);
    assert(A->size == C->size);
    for (int i = 0; i < A->size; i++)
    {
        for (int j = 0; j < A->size; j++)
        {
            float sum = 0.0;
            for (int k = 0; k < A->size; k++)
                sum += A->data[i][k] * B->data[k][j];
            C->data[i][j] = sum;
        }
    }
}


int main(void)
{
    struct timeval begin, end;
    Matrix A = matrix_create(N);
    Matrix B = matrix_create(N);
    Matrix C = matrix_create(N);

    for (int i = 0; i <  N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
            B.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
        }
    }

    gettimeofday(&begin, 0);
    matrix_multiply_NxN(&A, &B, &C);
    gettimeofday(&end, 0);

    matrix_print("A", &A);
    matrix_print("B", &B);
    matrix_print("C", &C);

    matrix_destroy(&A);
    matrix_destroy(&B);
    matrix_destroy(&C);

    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Number of NxN multiplications:   %zu\n", cnt_NxN);
    printf("Number of matrices created:      %zu\n", cnt_create);
    printf("Number of matrices destroyed:    %zu\n", cnt_destroy);
    printf("Total wall time: %f\n", elapsed);
    return 0;
}

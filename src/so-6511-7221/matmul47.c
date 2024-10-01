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

static size_t cnt_big = 0;
static size_t cnt_create = 0;
static size_t cnt_destroy = 0;
static size_t cnt_add = 0;
static size_t cnt_sub = 0;
static size_t cnt_1x1 = 0;

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

static Matrix add(const Matrix *M1, const Matrix *M2)
{
    cnt_add++;
    assert(M1->size == M2->size);
    Matrix M3 = matrix_create(M1->size);
    for (int i = 0; i < M1->size; i++)
    {
        for (int j = 0; j < M1->size; j++)
            M3.data[i][j] = M1->data[i][j] + M2->data[i][j];
    }

    return M3;
}

static Matrix sub(const Matrix *M1, const Matrix *M2)
{
    cnt_sub++;
    assert(M1->size == M2->size);
    Matrix M3 = matrix_create(M1->size);
    for (int i = 0; i < M1->size; i++)
    {
        for (int j = 0; j < M1->size; j++)
            M3.data[i][j] = M1->data[i][j] - M2->data[i][j];
    }

    return M3;
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

static Matrix strassen_multiply(const Matrix *A, const Matrix *B)
{
    assert(A->size == B->size);
    if (A->size == 1)
    {
        cnt_1x1++;
        Matrix C = matrix_create(A->size);
        C.data[0][0] = A->data[0][0] * B->data[0][0];
        return C;
    }
    cnt_big++;
    Matrix C = matrix_create(A->size);
    int k = A->size / 2;
    /** Creating sub matrices**/
    Matrix A11 = matrix_create(k);
    Matrix A12 = matrix_create(k);
    Matrix A21 = matrix_create(k);
    Matrix A22 = matrix_create(k);
    Matrix B11 = matrix_create(k);
    Matrix B12 = matrix_create(k);
    Matrix B21 = matrix_create(k);
    Matrix B22 = matrix_create(k);

    /** Dividing the Data Matrices A & B **/
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11.data[i][j] = A->data[i + 0][j + 0];
            A12.data[i][j] = A->data[i + 0][k + j];
            A21.data[i][j] = A->data[k + i][j + 0];
            A22.data[i][j] = A->data[k + i][k + j];
            B11.data[i][j] = B->data[i + 0][j + 0];
            B12.data[i][j] = B->data[i + 0][k + j];
            B21.data[i][j] = B->data[k + i][j + 0];
            B22.data[i][j] = B->data[k + i][k + j];
        }
    }

    Matrix T1 = sub(&B12, &B22);
    Matrix P1 = strassen_multiply(&A11, &T1);
    matrix_destroy(&T1);

    Matrix T2 = add(&A11, &A12);
    Matrix P2 = strassen_multiply(&T2, &B22);
    matrix_destroy(&T2);

    Matrix T3 = add(&A21, &A22);
    Matrix P3 = strassen_multiply(&T3, &B11);
    matrix_destroy(&T3);

    Matrix T4 = sub(&B21, &B11);
    Matrix P4 = strassen_multiply(&A22, &T4);
    matrix_destroy(&T4);

    Matrix T5A = add(&A11, &A22);
    Matrix T5B = add(&B11, &B22);
    Matrix P5 = strassen_multiply(&T5A, &T5B);
    matrix_destroy(&T5A);
    matrix_destroy(&T5B);

    Matrix T6A = sub(&A12, &A22);
    Matrix T6B = add(&B21, &B22);
    Matrix P6 = strassen_multiply(&T6A, &T6B);
    matrix_destroy(&T6A);
    matrix_destroy(&T6B);

    Matrix T7A = sub(&A11, &A21);
    Matrix T7B = add(&B11, &B12);
    Matrix P7 = strassen_multiply(&T7A, &T7B);
    matrix_destroy(&T7A);
    matrix_destroy(&T7B);

    matrix_destroy(&A11);
    matrix_destroy(&A12);
    matrix_destroy(&A21);
    matrix_destroy(&A22);
    matrix_destroy(&B11);
    matrix_destroy(&B12);
    matrix_destroy(&B21);
    matrix_destroy(&B22);

    Matrix C1A = add(&P5, &P4);
    Matrix C1B = add(&C1A, &P6);
    Matrix C11 = sub(&C1B, &P2);
    Matrix C12 = add(&P1, &P2);
    Matrix C21 = add(&P3, &P4);
    Matrix C2A = add(&P5, &P1);
    Matrix C2B = sub(&C2A, &P3);
    Matrix C22 = sub(&C2B, &P7);
    matrix_destroy(&C1A);
    matrix_destroy(&C1B);
    matrix_destroy(&C2A);
    matrix_destroy(&C2B);

    matrix_destroy(&P1);
    matrix_destroy(&P2);
    matrix_destroy(&P3);
    matrix_destroy(&P4);
    matrix_destroy(&P5);
    matrix_destroy(&P6);
    matrix_destroy(&P7);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C.data[i + 0][j + 0] = C11.data[i][j];
            C.data[i + 0][j + k] = C12.data[i][j];
            C.data[k + i][j + 0] = C21.data[i][j];
            C.data[k + i][k + j] = C22.data[i][j];
        }
    }

    matrix_destroy(&C11);
    matrix_destroy(&C12);
    matrix_destroy(&C21);
    matrix_destroy(&C22);

    return C;
}

int main(void)
{
    struct timeval begin, end;
    Matrix A = matrix_create(N);
    Matrix B = matrix_create(N);

    for (int i = 0; i <  N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
            B.data[i][j] = -1.0 + 2.0 * ((double)rand()) / RAND_MAX;
        }
    }

    gettimeofday(&begin, 0);
    Matrix C = strassen_multiply(&A, &B);
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

    printf("Number of large multiplications: %zu\n", cnt_big);
    printf("Number of 1x1 multiplications:   %zu\n", cnt_1x1);
    printf("Number of matrices created:      %zu\n", cnt_create);
    printf("Number of matrices destroyed:    %zu\n", cnt_destroy);
    printf("Number of matrix additions:      %zu\n", cnt_add);
    printf("Number of matrix subtractions:   %zu\n", cnt_sub);
    printf("Total wall time: %f\n", elapsed);
    return 0;
}

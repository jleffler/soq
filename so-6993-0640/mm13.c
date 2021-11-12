/* SO 6993-0640: Multiply 3x3 matrices symbolically */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stderr.h"
#include "emalloc.h"

// SOF - matrix.h
enum { N = 3 };
typedef char *Cell;
typedef Cell Matrix[N][N];

extern void init_matrix(Matrix matrix);
extern void print_matrix(const char *tag, const Matrix matrix);
extern void read_matrix(Matrix matrix);
extern void free_matrix(Matrix matrix);
extern void multiply_matrices(Matrix m1, Matrix m2, Matrix result);
// EOF - matrix.h

void init_matrix(Matrix matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            matrix[i][j] = NULL;
    }
}

static void read_cell(int r, int c, Cell *cell)
{
    char buffer[256];
    if (scanf("%s", buffer) != 1)
        err_error("failed to read value for cell[%d,%d]\n", r, c);
    // validate data in cell?
    if (*cell != 0)
        free(*cell);
    *cell = STRDUP(buffer);
}

void read_matrix(Matrix matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            read_cell(i, j, &matrix[i][j]);
    }
}

void free_matrix(Matrix matrix)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            free(matrix[r][c]);
            matrix[r][c] = NULL;
        }
    }
}

static int max_cell_length(const Matrix matrix)
{
    int maxlen = 0;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (matrix[r][c] == NULL)
                continue;
            int curlen = strlen((char *)matrix[r][c]);
            if (curlen > maxlen)
                maxlen = curlen;
        }
    }
    return maxlen;
}

void print_matrix(const char *tag, const Matrix matrix)
{
    printf("%s:\n", tag);
    int width = max_cell_length(matrix);
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            const char *value = matrix[r][c];
            if (value == NULL)
                value = ".";
            printf("    %*s", width, value);
        }
        putchar('\n');
    }
}

static Cell multiply_row_by_column(int r, int c, Matrix m1, Matrix m2)
{
    const char *pad = "";
    size_t len = N * sizeof("().()");
    for (int k = 0; k < N; k++)
        len += strlen(m1[r][k]) + strlen(m2[k][c]);
    Cell result = MALLOC(len);
    result[0] = '\0';
    size_t reslen = 0;
    for (int k = 0; k < N; k++)
    {
        int nbytes = snprintf(&result[reslen], len - reslen, "%s(%s).(%s)",
                              pad, m1[r][k], m2[k][c]);
        reslen += nbytes;
        pad = "+";
    }
    // result = simplify(result);
    return result;
}

void multiply_matrices(Matrix m1, Matrix m2, Matrix result)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (result[r][c] != NULL)
                free(result[r][c]);
            result[r][c] = multiply_row_by_column(r, c, m1, m2);
        }
    }
}

int main(void)
{
    Matrix m1 = { 0 };
    Matrix m2 = { 0 };
    err_setarg0("3x3 Matrix Multiplication");

    read_matrix(m1);
    read_matrix(m2);

    print_matrix("M1", m1);
    print_matrix("M2", m2);

    Matrix m3;
    init_matrix(m3);

    multiply_matrices(m1, m2, m3);
    print_matrix("M1.M2", m3);

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m3);

    return 0;
}

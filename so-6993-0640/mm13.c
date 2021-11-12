/* SO 6993-0640: Multiply 3x3 matrices symbolically */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stderr.h"
#include "emalloc.h"

// SOF - matrix.h
enum { N = 3 };
typedef unsigned char *Cell;
typedef Cell Matrix[N][N];

extern void init_matrix(Matrix matrix);
extern void print_matrix(const char *tag, const Matrix matrix);
extern void read_matrix(Matrix matrix);
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
    unsigned char buffer[256];
    if (scanf("%s", buffer) != 1)
        err_error("failed to read value for cell[%d,%d]\n", r, c);
    // validate data in cell?
    if (*cell != 0)
        free(*cell);
    *cell = (Cell)STRDUP((char *)buffer);
}

void read_matrix(Matrix matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            read_cell(i, j, &matrix[i][j]);
    }
}

static int max_cell_length(const Matrix matrix)
{
    int maxlen = 0;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            assert(matrix[r][c] != NULL);
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
            printf("    %*s", width, matrix[r][c]);
        putchar('\n');
    }
}

#if 0
static Cell cell_concat(Cell p1, Cell p2)
{
    size_t len1 = strlen(p1);
    size_t len2 = strlen(p2);
    size_t tlen = len1 + len2 + sizeof("()*()");
    Cell result = MALLOC(tlen);
    snprintf(result, tlen, "(%s)*(%s)", p1, p2);
    return result;
}

static Cell mul_add(Cell prefix, Cell c1, Cell c2)
{
    Cell result = NULL;
    if (prefix != 0)
        result = cell_concat(prefix, "+");
    result = cell_multiply(result, c1, c2);
    return result;
}

void multiply_matrices(Matrix m1, Matrix m2, Matrix result)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Cell cell = NULL;
            for (int k = 0; k < N; k++)
            {
                cell = mul_add(cell, m1[i][k], m2[k][j]);
            }
            if (result[i][j] != NULL)
                free(result[i][j]);
            result[i][j] = cell;
        }
    }
}
#endif /* 0 */

int main(void)
{
    Matrix m1 = { 0 };
    Matrix m2 = { 0 };
    //Matrix m3 = { 0 };
    err_setarg0("3x3 Matrix Multiplication");

    read_matrix(m1);
    read_matrix(m2);

    print_matrix("M1", m1);
    print_matrix("M2", m2);

    //init_matrix(m1);
    //init_matrix(m2);
    //init_matrix(m2);
    //multiply_matrices(m1, m2, m3);
    //print_matrix("M1.M2", m3);

    return 0;
}

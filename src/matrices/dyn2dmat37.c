/* SO 6492-2134 */

/* SOF - matrix.h */
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stddef.h>     /* size_t */

enum { MATRIX_MAX_SIZE = 1000 };

typedef struct Matrix Matrix;   /* Opaque type */

extern Matrix *matrix_constructor(size_t rows, size_t cols);
extern void matrix_destructor(Matrix *mtx);
extern int matrix_get_element(const Matrix *mtx, size_t r, size_t c);
extern void matrix_set_element(Matrix *mtx, size_t r, size_t c, int v);
extern size_t matrix_get_cols(const Matrix *mtx);
extern size_t matrix_get_rows(const Matrix *mtx);

#endif /* MATRIX_H_INCLUDED */
/* EOF - matrix.h */

/* SOF - matrix.c */
/*#include "matrix.h"*/
#include <assert.h>
#include <stdlib.h>

struct Matrix
{
    size_t   rows;
    size_t   cols;
    int    **data;
};

/* It is important to prevent memory leaks on allocation failure */
Matrix *matrix_constructor(size_t rows, size_t cols)
{
    assert(rows <= MATRIX_MAX_SIZE && rows > 0);
    assert(cols <= MATRIX_MAX_SIZE && cols > 0);
    Matrix *mtx = malloc(sizeof(*mtx));
    if (mtx == NULL)
        return NULL;
    mtx->data = malloc(sizeof(*mtx->data) * rows);
    if (mtx->data == NULL)
    {
        free(mtx);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++)
    {
        mtx->data[i] = malloc(sizeof(*mtx->data[i]) * cols);
        if (mtx->data[i] == NULL)
        {
            while (i > 0)
                free(mtx->data[--i]);
            free(mtx);
            return NULL;
        }
    }
    mtx->rows = rows;
    mtx->cols = cols;
    return mtx;
}

void matrix_destructor(Matrix *mtx)
{
    assert(mtx != NULL && mtx->data != NULL);
    assert(mtx->rows <= MATRIX_MAX_SIZE && mtx->rows > 0);
    assert(mtx->cols <= MATRIX_MAX_SIZE && mtx->cols > 0);
    for (size_t i = 0; i < mtx->rows; i++)
        free(mtx->data[i]);
    free(mtx->data);
    free(mtx);
}

int matrix_get_element(const Matrix *mtx, size_t r, size_t c)
{
    assert(mtx != NULL && mtx->data != NULL);
    assert(mtx->rows <= MATRIX_MAX_SIZE && mtx->rows > 0);
    assert(mtx->cols <= MATRIX_MAX_SIZE && mtx->cols > 0);
    return mtx->data[r][c];
}

void matrix_set_element(Matrix *mtx, size_t r, size_t c, int v)
{
    assert(mtx != NULL && mtx->data != NULL);
    assert(mtx->rows <= MATRIX_MAX_SIZE && mtx->rows > 0);
    assert(mtx->cols <= MATRIX_MAX_SIZE && mtx->cols > 0);
    mtx->data[r][c] = v;
}

size_t matrix_get_rows(const Matrix *mtx)
{
    assert(mtx != NULL && mtx->data != NULL);
    assert(mtx->rows <= MATRIX_MAX_SIZE && mtx->rows > 0);
    assert(mtx->cols <= MATRIX_MAX_SIZE && mtx->cols > 0);
    return mtx->rows;
}

size_t matrix_get_cols(const Matrix *mtx)
{
    assert(mtx != NULL && mtx->data != NULL);
    assert(mtx->rows <= MATRIX_MAX_SIZE && mtx->rows > 0);
    assert(mtx->cols <= MATRIX_MAX_SIZE && mtx->cols > 0);
    return mtx->cols;
}
/* EOF - matrix.c */

/* SOF - test.matrix.c */
/*#include "matrix.h"*/
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>     /* intmax_t */
#include <stdio.h>
/*#include <stdlib.h>*/
#include <string.h>
#include <time.h>

/* Cannot dereference Matrix pointers here! */

static void matrix_print(const char *tag, const Matrix *mtx, int width)
{
    size_t rows = matrix_get_rows(mtx);
    size_t cols = matrix_get_cols(mtx);
    printf("%s (%zux%zu):\n", tag, rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < cols; c++)
        {
            printf("%s%*d", pad, width, matrix_get_element(mtx, r, c));
            pad = ", ";
        }
        putchar('\n');
    }
}

static void matrix_random(Matrix *mtx)
{
    size_t rows = matrix_get_rows(mtx);
    size_t cols = matrix_get_cols(mtx);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
            matrix_set_element(mtx, r, c, (rand() % (rows * cols) + 1));
    }
}

static int i_log10(size_t n)
{
    if (n < 10)
        return 1;
    int c = 1;
    while (n >= 10)
    {
        n /= 10;
        c++;
    }
    return c;
}

static int i_pow10(int n)
{
    int r = 1;
    while (n-- > 0)
        r *= 10;
    return r;
}

static void matrix_ordered(Matrix *mtx)
{
    size_t rows = matrix_get_rows(mtx);
    size_t cols = matrix_get_cols(mtx);
    int mul = i_pow10(i_log10(cols));
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
            matrix_set_element(mtx, r, c, (r + 1) * mul + c + 1);
    }
}

static void err_exit(const char *fmt, ...)
{
    va_list args;
    int errnum = errno;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
    exit(EXIT_FAILURE);
}

static Matrix *matrix_checked_constructor(const char *tag, size_t rows, size_t cols)
{
    Matrix *mp = matrix_constructor(rows, cols);
    if (mp == NULL)
        err_exit("Failed to construct matrix %s", tag);
    return mp;
}

int main(void)
{
    Matrix *mi5 = matrix_checked_constructor("MI5", 5, 5);
    Matrix *mi6 = matrix_checked_constructor("MI6", 6, 6);
    Matrix *ks69 = matrix_checked_constructor("KS69", 6, 9);
    Matrix *bw1815 = matrix_checked_constructor("BW1815", 18, 15);

    time_t now = time(0);
    srand(now);
    printf("Seed: %jd\n", (intmax_t)now);

    matrix_random(mi5);
    matrix_random(mi6);
    matrix_ordered(ks69);
    matrix_ordered(bw1815);

    matrix_print("MI5", mi5, 2);
    matrix_print("MI6", mi6, 2);
    matrix_print("KS69", ks69, 3);
    matrix_print("BW1815", bw1815, 4);

    matrix_destructor(mi5);
    matrix_destructor(mi6);

    return 0;
}
/* EOF - test.matrix.c */

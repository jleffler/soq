/* SO 4829-1562 */

/*
**  + Enter a square matrix of dimensions n .
**  + Elements below main diagonal sort in ascending order.
**  + Elements above main diagonal sort in descending order.
**  + Elements on main diagonal sort :
**    - first even numbers in ascending order.
**    - then odd numbers in descending order.
*/

/* Timing harness */

#include "emalloc.h"
#include "stderr.h"
#include "timer.h"
#include <stdio.h>
#include <time.h>
#include "time.sort2d-31.h"

static void time_matrix(const char *tag, size_t n, int matrix[n][n], void (*sorter)(size_t n, int matrix[n][n]))
{
    Clock clk;
    clk_init(&clk);
    clk_start(&clk);
    (*sorter)(n, matrix);
    clk_stop(&clk);
    char buffer[32];
    printf("%s sort (%zux%zu) - elapsed: %11s\n",
           tag, n, n, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
    fflush(stdout);
}

static void cmp_matrix(size_t n, int matrix1[n][n], int matrix2[n][n])
{
    for (size_t r = 0; r < n; r++)
    {
        for (size_t c = 0; c < n; c++)
        {
            if (matrix1[r][c] != matrix2[r][c])
                err_remark("Mismatch m1[%zu][%zu] = %d; m2[%zu][%zu] = %d\n",
                        r, c, matrix1[r][c], r, c, matrix2[r][c]);
        }
    }
}

static void dump_matrix(const char *tag, size_t r, size_t c, int matrix[r][c])
{
    printf("%s:\n", tag);
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
            printf(" %3d", matrix[i][j]);
        putchar('\n');
    }
}

static void multiple_small_sorts(void)
{
    int multipliers[] = { 10, 100, };
    enum { NUM_MULTIPLIERS = sizeof(multipliers) / sizeof(multipliers[0]) };
    int verbose = 0;

    for (int i = 0; i < NUM_MULTIPLIERS; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            size_t n = multipliers[i] * j;
            int (*matrix1)[n] = MALLOC(n * n * sizeof(matrix1[0][0]));
            int (*matrix2)[n] = MALLOC(n * n * sizeof(matrix1[0][0]));
            int (*matrix3)[n] = MALLOC(n * n * sizeof(matrix1[0][0]));
            for (size_t r = 0; r < n; r++)
            {
                for (size_t c = 0; c < n; c++)
                {
                    matrix1[r][c] = matrix2[r][c] = rand() % 900 + 100;
                    matrix2[r][c] = matrix1[r][c];
                    matrix3[r][c] = matrix1[r][c];
                }
            }
            if (verbose && n < 100)
                dump_matrix("Before", n, n, matrix1);
            cmp_matrix(n, matrix1, matrix2);
            cmp_matrix(n, matrix1, matrix3);
            time_matrix("Basic", n, matrix1, basic_sort);
            time_matrix("Clean", n, matrix2, clean_sort);
            time_matrix("Quick", n, matrix3, quick_sort);
            if (verbose && n < 100)
                dump_matrix("After", n, n, matrix1);
            cmp_matrix(n, matrix1, matrix2);
            cmp_matrix(n, matrix1, matrix3);
            FREE(matrix1);
            FREE(matrix2);
            FREE(matrix3);
        }
    }
}

static void bigger_quick_sorts(void)
{
    int multipliers[] = { 10, 100, 1000, 10000 };
    enum { NUM_MULTIPLIERS = sizeof(multipliers) / sizeof(multipliers[0]) };
    int verbose = 0;

    for (int i = 0; i < NUM_MULTIPLIERS; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            size_t n = multipliers[i] * j;
            int (*matrix)[n] = MALLOC(n * n * sizeof(matrix[0][0]));
            for (size_t r = 0; r < n; r++)
            {
                for (size_t c = 0; c < n; c++)
                    matrix[r][c] = rand() % 900 + 100;
            }
            if (verbose && n < 100)
                dump_matrix("Before", n, n, matrix);
            time_matrix("Quick", n, matrix, quick_sort);
            if (verbose && n < 100)
                dump_matrix("After", n, n, matrix);
            FREE(matrix);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 0)
        err_setarg0(argv[0]);
    srand(time(0));

    multiple_small_sorts();
    putchar('\n');
    bigger_quick_sorts();

    return 0;
}

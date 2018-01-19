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

#include "stderr.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
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
    printf("%s sort - elapsed (%zux%zu): %s\n", tag, n, n, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
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
            printf("%4d", matrix[i][j]);
        putchar('\n');
    }
}

int main(int argc, char **argv)
{
    if (argc != 0)
        err_setarg0(argv[0]);
    srand(time(0));
    int multipliers[] = { 10, 100, /*1000, 10000*/ };
    enum { NUM_MULTIPLIERS = sizeof(multipliers) / sizeof(multipliers[0]) };
    int verbose = 0;

    for (int i = 0; i < NUM_MULTIPLIERS; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            int n = multipliers[i] * j;
            int (*matrix1)[n] = malloc(n * n * sizeof(matrix1[0][0]));
            int (*matrix2)[n] = malloc(n * n * sizeof(matrix1[0][0]));
            int (*matrix3)[n] = malloc(n * n * sizeof(matrix1[0][0]));
            if (matrix1 == 0 || matrix2 == 0 || matrix3 == 0)
                err_syserr("failed to allocate %zu bytes of memory: ",
                           n * n * sizeof(matrix1[0][0]));
            for (int r = 0; r < n; r++)
            {
                for (int c = 0; c < n; c++)
                {
                    matrix1[r][c] = matrix2[r][c] = rand() % 900 + 100;
                    matrix2[r][c] = matrix1[r][c];
                    matrix3[r][c] = matrix1[r][c];
                }
            }
            if (verbose)
                dump_matrix("Before", n, n, matrix1);
            cmp_matrix(n, matrix1, matrix2);
            cmp_matrix(n, matrix1, matrix3);
            time_matrix("Basic", n, matrix1, basic_sort);
            time_matrix("Quick", n, matrix2, quick_sort);
            time_matrix("Clean", n, matrix3, clean_sort);
            if (verbose)
                dump_matrix("After", n, n, matrix1);
            cmp_matrix(n, matrix1, matrix2);
            cmp_matrix(n, matrix1, matrix3);
            free(matrix1);
            free(matrix2);
            free(matrix3);
        }
    }

    return 0;
}

/* SO 5488-6632 (Fibonacci Pyramid - deleted) */

/*
** Print a Fibonacci Pyramid like this:
**
**   1  
**   1  1  
**   2  1  2  
**   3  2  2  3  
**   5  3  4  3  5  
**   8  5  6  6  5  8  
**  13  8 10  9 10  8 13  
**  21 13 16 15 15 16 13 21  
**  34 21 26 24 25 24 26 21 34  
**  55 34 42 39 40 40 39 42 34 55  
**
** The algorithm for column N appears to be roughly:
**
** Column N first appears on Row N and starts with the Nth Fibonacci
** number; the value in the next row is obtained by treating the prior
** value in the column as 0, so you get the Nth Fibonacci number in the
** N+1th row too; thereafter, the value is the sum of the N-2 and N-1
** rows in that column, as usual for Fibonacci series.
**
** The width calculation is the correct number of digits for the chosen
** number of rows.  The formula is good to 39, but incorrect (too
** narrow) from 40 upwards.
**
** NB: 32-bit signed integers are good up to 46 rows, but the
** calculations overflow at 47 rows.
**
** See also: https://www.fq.math.ca/Scanned/14-2/hosoya.pdf
*/

#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>

/* Allow choice of limits at compile time */
#ifndef MAX_ROWNUM
#define MAX_ROWNUM 20
#endif
#ifndef MIN_ROWNUM
#define MIN_ROWNUM 1
#endif

/* Enforce sensible limits */
#if MIN_ROWNUM < 1
#undef MIN_ROWNUM
#define MIN_ROWNUM 1
#endif
#if MAX_ROWNUM > 45
#undef MAX_ROWNUM
#define MAX_ROWNUM 45
#endif

static void print_row(int row, int *fib0, int fibN[row][2], int width);

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc > 2)
        err_usage("[max]");
    int max = 10;
    if (argc == 2)
        max = atoi(argv[1]);
    if (max > MAX_ROWNUM)
       err_error("Maximum upper bound is at most %d (%d is too large)\n", MAX_ROWNUM, max);
    if (max < MIN_ROWNUM)
       err_error("Minimum upper bound is at least %d (%d is too small)\n", MIN_ROWNUM, max);

    int fib0[max+1];
    int fibN[max+1][2];
    int width = (max + 3) / 5;

    for (int row = 1; row <= max; row++)
        print_row(row, fib0, fibN, width);

    return 0;
}

static void print_row(int row, int fib0[row+1], int fibN[row+1][2], int width)
{
    if (row < 3)
        fib0[row] = 1;
    else
        fib0[row] = fib0[row - 1] + fib0[row - 2];

    for (int col = 1; col <= row; col++)
    {
        int newfib = fibN[col][0] + fibN[col][1];
        if (col == row)
        {
            fibN[col][0] = 0;
            fibN[col][1] = fib0[row];
            newfib = fib0[row];
        }
        else
        {
            fibN[col][0] = fibN[col][1];
            fibN[col][1] = newfib;
        }
        printf(" %*d", width, newfib);
    }
    putchar('\n');
}

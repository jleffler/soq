/* SO 47464803 - Initialize and Transpose as in question */
#include "timer.h"
#include <stdio.h>

enum { DIMENSION = 4000, BLOCKSIZE = 50 };

static double Matrix[DIMENSION][DIMENSION];

static void InitializeMatrixRowwise(void)
{
    int i, j, ii, jj;
    double x;
    x = 0.0;
    for (i = 0; i < DIMENSION; i += BLOCKSIZE)
    {
        for (j = 0; j < DIMENSION; j += BLOCKSIZE)
        {
            for (ii = i; ii < i + BLOCKSIZE && ii < DIMENSION; ii++)
            {
                for (jj = j; jj < j + BLOCKSIZE && jj < DIMENSION; jj++)
                {
                    if (ii >= jj)
                    {
                        Matrix[ii][jj] = x++;
                    }
                    else
                        Matrix[ii][jj] = 1.0;
                }
            }
        }
    }
}

static void TransposeMatrixRowwise(void)
{
    int column, row, i, j;
    double temp;
    for (row = 0; row < DIMENSION; row += BLOCKSIZE)
    {
        for (column = 0; column < DIMENSION; column += BLOCKSIZE)
        {
            for (i = row; i < row + BLOCKSIZE && i < DIMENSION; i++)
            {
                for (j = column; j < column + BLOCKSIZE && j < DIMENSION; j++)
                {
                    if (i > j)
                    {
                        temp = Matrix[i][j];
                        Matrix[i][j] = Matrix[j][i];
                        Matrix[j][i] = temp;
                    }
                }
            }
        }
    }
}

static inline void dump_matrix(const char *tag, int rows, int cols, double matrix[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
            printf(" %8.2f", matrix[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    Clock ck;
    char buffer[32];

    printf("Matrix (%dx%d, blocks %dx%d)\n", DIMENSION, DIMENSION, BLOCKSIZE, BLOCKSIZE);

    clk_init(&ck);
    clk_start(&ck);
    InitializeMatrixRowwise();
    clk_stop(&ck);
    printf("Initialization: %s\n", clk_elapsed_us(&ck, buffer, sizeof(buffer)));

    //clk_init(&ck);
    //clk_start(&ck);
    //dump_matrix("Initialized", DIMENSION, DIMENSION, Matrix);
    //clk_stop(&ck);
    //printf("Print initialization: %s\n", clk_elapsed_us(&ck, buffer, sizeof(buffer)));

    clk_init(&ck);
    clk_start(&ck);
    TransposeMatrixRowwise();
    clk_stop(&ck);
    printf("Transposition: %s\n", clk_elapsed_us(&ck, buffer, sizeof(buffer)));

    clk_init(&ck);
    clk_start(&ck);
    dump_matrix("Transposed", DIMENSION, DIMENSION, Matrix);
    clk_stop(&ck);
    printf("Print transposition: %s\n", clk_elapsed_us(&ck, buffer, sizeof(buffer)));

    return 0;
}

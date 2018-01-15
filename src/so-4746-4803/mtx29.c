/* SO 4746-4803 - Initialize and Transpose avoiding extra pair of loops */
/* This is not the same as the original, though it takes time to spot the difference */
#include "timer.h"
#include <stdio.h>

enum { DIMENSION = 100, BLOCKSIZE = 15 };

static double Matrix[DIMENSION][DIMENSION];

static void InitializeMatrixRowwise(void)
{
    double x = 0.0;
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            if (i >= j)
                Matrix[i][j] = x++;
            else
                Matrix[i][j] = 1.0;
        }
    }
}

static void TransposeMatrixRowwise(void)
{
    for (int i = 0; i < DIMENSION; i++)
    {
        for (int j = i + 1; j < DIMENSION; j++)
        {
            double temp = Matrix[i][j];
            Matrix[i][j] = Matrix[j][i];
            Matrix[j][i] = temp;
        }
    }
}

static void dump_matrix(const char *tag, int rows, int cols, double matrix[rows][cols])
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
    dump_matrix("Initialized", DIMENSION, DIMENSION, Matrix);

    clk_init(&ck);
    clk_start(&ck);
    TransposeMatrixRowwise();
    clk_stop(&ck);
    printf("Transposition: %s\n", clk_elapsed_us(&ck, buffer, sizeof(buffer)));
    dump_matrix("Transposed", DIMENSION, DIMENSION, Matrix);

    return 0;
}

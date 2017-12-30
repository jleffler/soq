/* SO 4692-3548 - Revised A */
#include <stdio.h>
#include <stdlib.h>

static const char *arg0;

static void *matrix_allocate(int rows, int cols)
{
    void *vp = malloc(rows * cols * sizeof(double));
    if (vp == 0)
    {
        fprintf(stderr, "Memory allocation failed for %dx%d matrix\n", rows, cols);
        exit(1);
    }
    return vp;
}

/* Error-checked fopen() for read only */
static FILE *efopen_ro(const char *name)
{
    FILE *fp = fopen(name, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "%s: failed to open file %s for reading\n", arg0, name);
        exit(1);
    }
    return fp;
}

int main(int argc, char *argv[])
{
    arg0 = argv[0];
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s file1 file2\n", arg0);
        exit(1);
    }
    FILE *fptrain = efopen_ro(argv[1]);
    int row, col, i, j;
    fscanf(fptrain, "%d", &col);
    col = col + 1;
    fscanf(fptrain, "%d", &row);
    char ch;

    /* Matrix/vector declarations in the original */
    /*
    double trainX[row][col];
    double trainY[row][1];
    double trainXtrans[col][row];
    double trainXtemp[row][row];
    double trainXinden[col][col * 2];
    double trainXinverse[row][row];
    double trainXinvXt[col][row];
    double weight[row][1];
    double testM[testrows][col];
    double prices[testrows][1];
    */

    // creates the original X and Y matrix
    double (*trainX)[col] = matrix_allocate(row, col);
    double (*trainY)[1]   = matrix_allocate(row, 1);;
    for (i = 0; i < row; i++)
    {
        trainX[i][0] = 1.000000;
        for (j = 1; j < col; j++)
        {
            fscanf(fptrain, "%lf%c", &trainX[i][j], &ch);
        }
        fscanf(fptrain, "%lf%c", &trainY[i][0], &ch);
    }
    fclose(fptrain);

    // creates the X transposed matrix
    double (*trainXtrans)[row] = matrix_allocate(col, row);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXtrans[j][i] = trainX[i][j];
        }
    }

    // multiplies X and X transposed
    double (*trainXtemp)[row] = matrix_allocate(row, row);
    int s;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < col; j++)
        {
            double num = 0.0;
            for (s = 0; s < row; s++)
            {
                num += trainX[s][j] * trainXtrans[i][s];
            }
            trainXtemp[i][j] = num;
        }
    }

    // finds the identity matrix of X times X transposed
    double (*trainXiden)[col * 2] = matrix_allocate(col, col * 2);
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXiden[i][j] = trainXtemp[i][j];
        }
        for (j = col; j < col * 2; j++)
        {
            if (j == i + col)
            {
                trainXiden[i][j] = 1.000000;
            }
            else
            {
                trainXiden[i][j] = 0.000000;
            }
        }
    }

    // finds the inverse of X times X transposed through Gauss Jordan Elimination
    int k;
    for (i = 0; i < col; i++)
    {
        double divscalar = trainXiden[i][i];
        for (j = 0; j < col * 2; j++)
        {
            if (trainXiden[i][j] != 0)
            {
                trainXiden[i][j] = trainXiden[i][j] / divscalar;
            }
        }
        for (k = 0; k < col; k++)
        {
            if (i != k)
            {
                double subscalar = trainXiden[k][i];
                for (j = 0; j < col * 2; j++)
                {
                    trainXiden[k][j] = trainXiden[k][j] - subscalar * trainXiden[i][j];
                }
            }
        }
    }

    double (*trainXinverse)[row] = matrix_allocate(row, row);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXinverse[i][j] = trainXiden[i][j + col];
        }
    }

    double (*trainXinvXt)[row] = matrix_allocate(col, row);
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            double num = 0.0;
            for (s = 0; s < col; s++)
            {
                num += trainXinverse[i][s] * trainXtrans[s][j];
            }
            trainXinvXt[i][j] = num;
        }
    }

    // multiples (trainXinvXt) by Y
    double (*weight)[1] = matrix_allocate(row, 1);
    for (i = 0; i < col; i++)
    {
        for (s = 0; s < row; s++)
        {
            weight[i][0] += trainXinvXt[i][s] * trainY[s][0];
        }
    }

    FILE *fptest = efopen_ro(argv[2]);
    int testrows;
    fscanf(fptest, "%d", &testrows);
    // creates the test file matrix

    double (*testM)[col] = matrix_allocate(testrows, col);
    for (i = 0; i < testrows; i++)
    {
        testM[i][0] = 1.000000;
        for (j = 1; j < col; j++)
        {
            fscanf(fptest, "%lf%c", &testM[i][j], &ch);
        }
    }
    fclose(fptest);

    double (*prices)[1] = matrix_allocate(testrows, 1);
    for (i = 0; i < testrows; i++)
    {
        double num = 0.0;
        for (s = 0; s < col; s++)
        {
            num += testM[i][s] * weight[s][0];
        }
        prices[i][0] = num;
    }

    /* Print result */
    for (i = 0; i < testrows; i++)
    {
        printf("%.0lf\n", prices[i][0]);
    }

    free(trainX);
    free(trainY);
    free(trainXtrans);
    free(trainXtemp);
    free(trainXiden);
    free(trainXinverse);
    free(trainXinvXt);
    free(weight);
    free(testM);
    free(prices);

    return 0;
}

/* SO 4692-3548 - Revised C */
#include <stdio.h>
#include <stdlib.h>

static const char *arg0;
static void *matrix_allocate(int rows, int cols);
static FILE *efopen_ro(const char *name);
static void err_readerr_int(const char *tag);
static void err_readerr(const char *tag, int row, int col);

int main(int argc, char *argv[])
{
    arg0 = argv[0];
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s file1 file2\n", arg0);
        exit(1);
    }
    FILE *fptrain = efopen_ro(argv[1]);
    int row, col;
    if (fscanf(fptrain, "%d", &col) != 1)
        err_readerr_int("col");
    col++;
    if (fscanf(fptrain, "%d", &row) != 1)
        err_readerr_int("row");
    char ch;

    // creates the original X and Y matrix
    double (*trainX)[col] = matrix_allocate(row, col);
    double (*trainY)[1]   = matrix_allocate(row, 1);;
    for (int i = 0; i < row; i++)
    {
        trainX[i][0] = 1.000000;
        for (int j = 1; j < col; j++)
        {
            if (fscanf(fptrain, "%lf%c", &trainX[i][j], &ch) != 2)
                err_readerr("trainX", i, j);
        }
        if (fscanf(fptrain, "%lf%c", &trainY[i][0], &ch) != 2)
            err_readerr("trainY", i, 0);
    }
    fclose(fptrain);

    // creates the X transposed matrix
    double (*trainXtrans)[row] = matrix_allocate(col, row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            trainXtrans[j][i] = trainX[i][j];
        }
    }

    // multiplies X and X transposed
    double (*trainXtemp)[row] = matrix_allocate(row, row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            double num = 0.0;
            for (int s = 0; s < row; s++)
            {
                num += trainX[s][j] * trainXtrans[i][s];
            }
            trainXtemp[i][j] = num;
        }
    }

    // finds the identity matrix of X times X transposed
    double (*trainXiden)[col * 2] = matrix_allocate(col, col * 2);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            trainXiden[i][j] = trainXtemp[i][j];
        }
        for (int j = col; j < col * 2; j++)
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
    for (int i = 0; i < col; i++)
    {
        double divscalar = trainXiden[i][i];
        for (int j = 0; j < col * 2; j++)
        {
            if (trainXiden[i][j] != 0)
            {
                trainXiden[i][j] = trainXiden[i][j] / divscalar;
            }
        }
        for (int k = 0; k < col; k++)
        {
            if (i != k)
            {
                double subscalar = trainXiden[k][i];
                for (int j = 0; j < col * 2; j++)
                {
                    trainXiden[k][j] = trainXiden[k][j] - subscalar * trainXiden[i][j];
                }
            }
        }
    }

    double (*trainXinverse)[row] = matrix_allocate(row, row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            trainXinverse[i][j] = trainXiden[i][j + col];
        }
    }

    double (*trainXinvXt)[row] = matrix_allocate(col, row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            double num = 0.0;
            for (int s = 0; s < col; s++)
            {
                num += trainXinverse[i][s] * trainXtrans[s][j];
            }
            trainXinvXt[i][j] = num;
        }
    }

    // multiples (trainXinvXt) by Y
    double (*weight)[1] = matrix_allocate(row, 1);
    for (int i = 0; i < col; i++)
    {
        for (int s = 0; s < row; s++)
        {
            weight[i][0] += trainXinvXt[i][s] * trainY[s][0];
        }
    }

    FILE *fptest = efopen_ro(argv[2]);
    int testrows;
    if (fscanf(fptest, "%d", &testrows) != 1)
        err_readerr_int("testrows");
    // creates the test file matrix

    double (*testM)[col] = matrix_allocate(testrows, col);
    for (int i = 0; i < testrows; i++)
    {
        testM[i][0] = 1.000000;
        for (int j = 1; j < col; j++)
        {
            if (fscanf(fptest, "%lf%c", &testM[i][j], &ch) != 2)
                err_readerr("testM", i, j);
        }
    }
    fclose(fptest);

    double (*prices)[1] = matrix_allocate(testrows, 1);
    for (int i = 0; i < testrows; i++)
    {
        double num = 0.0;
        for (int s = 0; s < col; s++)
        {
            num += testM[i][s] * weight[s][0];
        }
        prices[i][0] = num;
    }

    /* Print result */
    for (int i = 0; i < testrows; i++)
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

static void err_readerr_int(const char *tag)
{
    fprintf(stderr, "read error for value %s\n", tag);
    exit(1);
}

static void err_readerr(const char *tag, int row, int col)
{
    fprintf(stderr, "read error for matrix %s[%d][%d]\n", tag, row, col);
    exit(1);
}

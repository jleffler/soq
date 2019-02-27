/* SO 4692-3548 - Original */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("error.");
        return 0;
    }
    FILE *fptrain = fopen(argv[1], "r");
    if (fptrain == NULL)
    {
        printf("error.");
        return 0;
    }
    int row, col, i, j;
    if (fscanf(fptrain, "%d", &col) != 1)
        return 1;
    col = col + 1;
    if (fscanf(fptrain, "%d", &row) != 1)
        return 1;
    char ch;
    // creates the original X and Y matrix

    double trainX[row][col];
    double trainY[row][1];
    for (i = 0; i < row; i++)
    {
        trainX[i][0] = 1.000000;
        for (j = 1; j < col; j++)
        {
            if (fscanf(fptrain, "%lf%c", &trainX[i][j], &ch) != 1)
                return 1;
        }
        if (fscanf(fptrain, "%lf%c", &trainY[i][0], &ch) != 1)
            return 1;
    }
    // creates the X transposed matrix
    double trainXtrans[col][row];
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXtrans[j][i] = trainX[i][j];
        }
    }
    // multiplies X and X transposed
    double trainXtemp[row][row];
    int s;
    double num = 0;
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < col; j++)
        {
            for (s = 0; s < row; s++)
            {
                num = num +  trainX[s][j] * trainXtrans[i][s];
            }
            trainXtemp[i][j] = num;
            num = 0;
        }
    }
    // finds the identity matrix of X times X transposed
    double trainXinden[col][col * 2];
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXinden[i][j] = trainXtemp[i][j];
        }
        for (j = col; j < col * 2; j++)
        {
            if (j == i + col)
            {
                trainXinden[i][j] = 1.000000;
            }
            else
            {
                trainXinden[i][j] = 0.000000;
            }
        }
    }
    // finds the inverse of X times X transposed through Gauss Jordan Elimination
    int k;
    double divscalar;
    for (i = 0; i < col; i++)
    {
        divscalar = trainXinden[i][i];
        for (j = 0; j < col * 2; j++)
        {
            if (trainXinden[i][j] != 0)
            {
                trainXinden[i][j] = trainXinden[i][j] / divscalar;
            }
        }
        for (k = 0; k < col; k++)
        {
            if (i != k)
            {
                double subscalar = trainXinden[k][i];
                for (j = 0; j < col * 2; j++)
                {
                    trainXinden[k][j] = trainXinden[k][j] - subscalar * trainXinden[i][j];
                }
            }
        }
    }
    double trainXinverse[row][row];
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            trainXinverse[i][j] = trainXinden[i][j + col];
        }
    }
    double trainXinvXt[col][row];
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            for (s = 0; s < col; s++)
            {
                num = num + trainXinverse[i][s] * trainXtrans[s][j];
            }
            trainXinvXt[i][j] = num;
            num = 0;
        }
    }
    // multiples (trainXinvXt) by Y
    double weight[row][1];
    for (i = 0; i < col; i++)
    {
        for (s = 0; s < row; s++)
        {
            weight[i][0] +=  trainXinvXt[i][s] * trainY[s][0];
        }
    }

    FILE *fptest = fopen(argv[2], "r");
    if (fptest == NULL)
    {
        printf("error.");
        return 0;
    }
    int testrows;
    if (fscanf(fptest, "%d", &testrows) != 1)
        return 1;
    // creates the test file matrix

    double testM[testrows][col];
    for (i = 0; i < testrows; i++)
    {
        testM[i][0] = 1.000000;
        for (j = 1; j < col; j++)
        {
            if (fscanf(fptest, "%lf%c", &testM[i][j], &ch) != 1)
                return 1;
        }
    }


    double prices[testrows][1];
    for (i = 0; i < testrows; i++)
    {
        for (s = 0; s < col; s++)
        {
            num = num + testM[i][s] * weight[s][0];
        }
        prices[i][0] = num;
        num = 0;
    }

    for (i = 0; i < testrows; i++)
    {
        printf("%0.0lf", prices[i][0]);
        printf("\n");
    }
    return 0;
}

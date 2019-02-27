/* SO 1276-2944 - Huge matrix and segmentation fault */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define   lambda   2.0
#define   g        1.0
#define   F0       1.0
#define   h        0.1
#define   e        0.00001

enum { ROWS = 1000, COLS = 200000 };

static double F[ROWS][COLS];

static void Inicio(double D[ROWS][COLS])
{
    int i;
    for (i=399; i<600; i++)
    {
        D[i][0]=F0;
    }
}

static void Iteration (double A[ROWS][COLS])
{
    for (int i = 1; i < COLS; i++)
    {
        A[0][i] = A[0][i-1] + e/(h*h*h*h)*g*g*(A[2][i-1] - 4.0*A[1][i-1] + 6.0*A[0][i-1]-4.0*A[998][i-1] + A[997][i-1]) + 2.0*g*e/(h*h)*(A[1][i-1] - 2*A[0][i-1] + A[998][i-1]) + e*A[0][i-1]*(lambda-A[0][i-1]*A[0][i-1]);
        A[1][i] = A[1][i-1] + e/(h*h*h*h)*g*g*(A[3][i-1] - 4.0*A[2][i-1] + 6.0*A[1][i-1]-4.0*A[0][i-1] + A[998][i-1]) + 2.0*g*e/(h*h)*(A[2][i-1] - 2*A[1][i-1] + A[0][i-1]) + e*A[1][i-1]*(lambda-A[1][i-1]*A[1][i-1]);
        for (int k = 2; k < 997; k++)
        {
            A[k][i] = A[k][i-1] + e/(h*h*h*h)*g*g*(A[k+2][i-1] - 4.0*A[k+1][i-1] + 6.0*A[k][i-1]-4.0*A[k-1][i-1] + A[k-2][i-1]) + 2.0*g*e/(h*h)*(A[k+1][i-1] - 2*A[k][i-1] + A[k-1][i-1]) + e*A[k][i-1]*(lambda-A[k][i-1]*A[k][i-1]);
        }
        A[997][i] = A[997][i-1] + e/(h*h*h*h)*g*g*(A[0][i-1] - 4*A[998][i-1] + 6*A[997][i-1] - 4*A[996][i-1] + A[995][i-1]) + 2.0*g*e/(h*h)*(A[998][i-1] - 2*A[997][i-1] + A[996][i-1]) + e*A[997][i-1]*(lambda-A[997][i-1]*A[997][i-1]);
        A[998][i] = A[998][i-1] + e/(h*h*h*h)*g*g*(A[1][i-1] - 4*A[0][i-1] + 6*A[998][i-1] - 4*A[997][i-1] + A[996][i-1]) + 2.0*g*e/(h*h)*(A[0][i-1] - 2*A[998][i-1] + A[997][i-1]) + e*A[998][i-1]*(lambda-A[998][i-1]*A[998][i-1]);
        A[999][i] = A[0][i];
    }
}

int main(void)
{
    FILE *file = fopen("P1.txt","wt");
    if (file == 0)
        return(1);
    Inicio(F);
    Iteration(F);
    for (int i = COLS-1; i < COLS; i++)
    {
        for (int j=0; j<ROWS; j++)
        {
            fprintf(file,"%lf \t %.4f \t %lf\n", 1.0*j/10.0, 1.0*i, F[j][i]);
        }
    }
    fclose(file);
}


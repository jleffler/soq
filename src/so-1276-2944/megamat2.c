/* SO 12762944 - Huge matrix and segmentation fault */
#include <stdio.h>

#define   lambda   2.0
#define   g        1.0
#define   F0       1.0
#define   h        0.1
#define   e        0.00001

enum { ROWS = 1000, COLS = 200000 };

static double F[ROWS][COLS];

static void Inicio(double D[ROWS][COLS])
{
    for (int i = 399; i < 600; i++) // Magic numbers!!
        D[i][0] = F0;
}

enum { R = ROWS - 1 };

static inline int ko(int k, int n)
{
    int rv = k + n;
    if (rv >= R)
        rv -= R;
    else if (rv < 0)
        rv += R;
    return(rv);
}

static inline void calculate_value(int i, int k, double A[ROWS][COLS])
{
    int ks2 = ko(k, -2);
    int ks1 = ko(k, -1);
    int kp1 = ko(k, +1);
    int kp2 = ko(k, +2);

    A[k][i] = A[k][i-1]
            + e/(h*h*h*h) * g*g * (A[kp2][i-1] - 4.0*A[kp1][i-1] + 6.0*A[k][i-1] - 4.0*A[ks1][i-1] + A[ks2][i-1])
            + 2.0*g*e/(h*h) * (A[kp1][i-1] - 2*A[k][i-1] + A[ks1][i-1])
            + e * A[k][i-1] * (lambda - A[k][i-1] * A[k][i-1]);
}

static void Iteration(double A[ROWS][COLS])
{
    for (int i = 1; i < COLS; i++)
    {
        for (int k = 0; k < R; k++)
            calculate_value(i, k, A);
        A[999][i] = A[0][i];
    }
}

int main(void)
{
    FILE *file = fopen("P2.txt","wt");
    if (file == 0)
        return(1);
    Inicio(F);
    Iteration(F);
    for (int i = COLS-1; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            fprintf(file,"%lf \t %.4f \t %lf\n", 1.0*j/10.0, 1.0*i, F[j][i]);
        }
    }
    fclose(file);
    return(0);
}


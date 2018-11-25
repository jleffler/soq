/* SO 4829-1562 - OP code Mk II reformatted */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static int a[500][500];
    int i, j, l, k, m, b, n, t, d, c;

    printf("Unesite n kvadratne matrice : \n");
    scanf("%d", &n);
    printf("Matrica pre sortiranja \n \n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }


    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i > j) // ispod dijagonale
            {
                for (l = i; l < n; l++)
                {
                    for (k = j; k < l; k++)
                    {
                        if (a[i][j] > a[l][k] && k  < l)
                        {
                            t = a[i][j];
                            a[i][j] = a[l][k];
                            a[l][k] = t;
                        }
                    }
                }
            }
            if (i < j) // iznad dijagonale
            {
                for (m = i; m < n; m++)
                {
                    for (b = j; b < n; b++)
                    {
                        if (a[i][j] < a[m][b] && m < b)
                        {
                            t = a[i][j];
                            a[i][j] = a[m][b];
                            a[m][b] = t;
                        }
                    }
                }
            }
            if (i == j) // dijagonala
            {
                for (d = i; d < n; d++)
                {
                    for (c = d + 1; c < n; c++)
                    {
                        if (a[d][d] % 2 != 0 && a[c][c] % 2 == 0)
                        {
                            t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                    }
                }
                for (d = i; d < n; d++)
                {
                    for (c = d + 1; c < n; c++)
                    {
                        if (a[d][d] % 2 == 0 && a[c][c] % 2 == 0
                            && a[d][d] > a[c][c])
                        {
                            t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                        else if (a[d][d] % 2 != 0 && a[c][c] % 2
                                 != 0 && a[d][d] < a[c][c])
                        {
                            t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                    }
                }
            }
        }
    }

    printf("Posle sortiranja : \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("    %d  ", a[i][j]);
        }
        printf("\n \n");
    }
    return 0;
}

/* SO 4829-1562 - OP code Mk II debugged and fixed */
#include "time.sort2d-31.h"

void inone_sort(size_t n, int a[n][n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i > j) // ispod dijagonale (LT)
            {
                size_t s = j + 1;                                       // JL
                for (size_t l = i; l < n; l++)
                {
                    //for (k = j; k < l; k++)                           // OP
                    for (size_t k = s; k < l; k++)                      // JL
                    {
                        //printf("a[%d][%d] = %d <=> a[%d][%d] %d\n",   // JL
                        //    i, j, a[i][j], l, k, a[l][k]);            // JL
                        //if (a[i][j] > a[l][k] && k < l)               // OP
                        if (a[i][j] > a[l][k])                          // JL
                        {
                            int t = a[i][j];
                            a[i][j] = a[l][k];
                            a[l][k] = t;
                        }
                    }
                    s = 0;                                              // JL
                }
            }
            if (i < j) // iznad dijagonale (UT)
            {
                size_t s = j + 1;                                          // JL
                for (size_t m = i; m < n; m++)
                {
                    //for (b = j; b < n; b++)                           // OP
                    for (size_t b = s; b < n; b++)                             // JL
                    {
                        //printf("a[%d][%d] = %d <=> a[%d][%d] %d\n",   // JL
                        //    i, j, a[i][j], m, b, a[m][b]);            // JL
                        //if (a[i][j] < a[m][b] && m < b)               // OP
                        if (a[i][j] < a[m][b])                          // JL
                        {
                            int t = a[i][j];
                            a[i][j] = a[m][b];
                            a[m][b] = t;
                        }
                    }
                    s = m + 2;                                          // JL
                }
            }
            if (i == j) // dijagonala
            {
                for (size_t d = i; d < n; d++)
                {
                    for (size_t c = d + 1; c < n; c++)
                    {
                        if (a[d][d] % 2 != 0 && a[c][c] % 2 == 0)
                        {
                            int t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                    }
                }
                for (size_t d = i; d < n; d++)
                {
                    for (size_t c = d + 1; c < n; c++)
                    {
                        if (a[d][d] % 2 == 0 && a[c][c] % 2 == 0
                            && a[d][d] > a[c][c])
                        {
                            int t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                        else if (a[d][d] % 2 != 0 && a[c][c] % 2
                                 != 0 && a[d][d] < a[c][c])
                        {
                            int t = a[d][d];
                            a[d][d] = a[c][c];
                            a[c][c] = t;
                        }
                    }
                }
            }
        }
    }
}

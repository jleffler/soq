/* SO 3333-8314 */
#include <stdio.h>
#include "gcd.h"

static void dump_matrix(int m, int n, int source[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%4d", source[i][j]);
        putchar('\n');
    }
}

static void init_matrix(int m, int n, int source[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            source[i][j] = (i + 1) * (j + 2);
    }
}

static void rotate_1col(int n, int vector[n], int z)
{
    z %= n;
    if (z != 0)
    {
        int c = gcd(n, z);
        int s = n / c;
        for (int r = 0; r < c; r++)
        {
            int x = r;
            int t = vector[x];
            for (int i = 0; i < s; i++)
            {
                int j = (x + z) % n;
                int v = vector[j];
                vector[j] = t;
                x = j;
                t = v;
            }
        }
    }
}

static void rotate_cols(int m, int n, int source[m][n], int z)
{
    for (int i = 0; i < m; i++)
        rotate_1col(n, source[i], z);
}

int main(void)
{
    int m = 3;

    for (int n = 2; n < 9; n++)
    {
        int source[m][n];
        for (int z = 0; z <= n; z++)
        {
            init_matrix(m, n, source);
            printf("Initial:\n");
            dump_matrix(m, n, source);
            rotate_cols(m, n, source, z);
            printf("Post-rotate %d:\n", z);
            dump_matrix(m, n, source);
            putchar('\n');
        }
    }

    return 0;
}

/* Code for https://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

static void dezigzag(int out[64], int in[8][8])
{
    int n = 0;
    for (int diag = 0; diag < (8 + 8 - 1); diag++)
    {
        for (int i = max(0, diag - 7); i <= min(7, diag); i++)
        {
            int x = diag % 2 == 0 ? i      : diag-i;
            int y = diag % 2 == 0 ? diag-i : i;
            printf("v[%2d] = m[%d][%d] = %2d (D = %2d)\n", n, y, x, in[y][x], diag);
            out[n++] = diag % 2 == 0 ? in[diag - i][i] : in[i][diag - i];
        }
    }
}

int main(void)
{
    int out[64] = {-1};
    int in[8][8];

    for (int i = 0; i < 64; i++)
        in[i % 8][i / 8] = i;

    puts("Matrix:");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%3d", in[i][j]);
        putchar('\n');
    }

    dezigzag(out, in);

    puts("Vector:");
    for (int i = 0; i < 8 * 8; i++)
    {
        printf("%3d", out[i]);
        if (i % 8 == 7)
            putchar('\n');
    }

    //for (int i = 0; i < 64; i++) {
    //    printf("%d: %d\n", i, out[i]);
    //}

    int tab2[8][8] =
    {
        {  1,  2,  6,  7, 15, 16, 28, 29 },
        {  3,  5,  8, 14, 17, 27, 30, 43 },
        {  4,  9, 13, 18, 26, 31, 42, 44 },
        { 10, 12, 19, 25, 32, 41, 45, 54 },
        { 11, 20, 24, 33, 40, 46, 53, 55 },
        { 21, 23, 34, 39, 47, 52, 56, 61 },
        { 22, 35, 38, 48, 51, 57, 60, 62 },
        { 36, 37, 49, 50, 58, 59, 63, 64 },
    };

    puts("Matrix:");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%3d", tab2[i][j]);
        putchar('\n');
    }

    dezigzag(out, tab2);

    puts("Vector:");
    for (int i = 0; i < 8 * 8; i++)
    {
        printf("%3d", out[i]);
        if (i % 8 == 7)
            putchar('\n');
    }

    return 0;
}

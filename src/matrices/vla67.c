#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* VLA notation using complete * notation in function prototypes */

static void mat_copy(int x, int y, const int src[x][y], int dst[x][y]);
static void mat_list_multiply(int x, int y, const int matlist[*][*][*], int result[*][*]);
static void mat_multiply(int x, int y, int z, const int mat1[*][*], const int mat2[*][*], int result[*][*]);
static void mat_print(const char *tag, int m, int n, const int matrix[*][*]);

int main(void)
{
    int matrices[][4][4] =
    {
        //random -n 48 -- -99 99 | commalist -n 4 -B 12 -b '{ ' -T ' },' -R -W 4
        {
            {   63,  -61,   36,  -27, },
            {   37,  -86,   44,  -14, },
            {   57,   10,   74,   23, },
            {  -74,  -52,  -87,   53, },
        },
        {
            {  -34,   89,  -71,   34, },
            {  -68,  -44,  -89,  -95, },
            {   -4,  -44,    2,   80, },
            {   66,  -33,  -19,  -65, },
        },
        {
            {  -64,   11,   54,   20, },
            {   -7,   75,   -7,  -98, },
            {   52,   48,  -96,   76, },
            {  -38,  -46,  -85,    4, },
        },
    };
    enum { NUM_MATRICES = sizeof(matrices) / sizeof(matrices[0]) };
    int result[4][4];
    mat_list_multiply(3, 4, matrices, result);
    for (int i = 0; i < NUM_MATRICES; i++)
    {
        char name[16];
        snprintf(name, sizeof(name), "%s[%d]", "matrices", i);
        mat_print(name, 4, 4, matrices[i]);
    }
    mat_print("result", 4, 4, result);
    return 0;
}

static void mat_copy(int x, int y, const int src[x][y], int dst[x][y])
{
    memmove(dst, src, x * y * sizeof(src[0][0]));   // sizeof(src) is not OK
}

static void mat_list_multiply(int x, int y, const int matlist[x][y][y], int result[y][y])
{
    int product[y][y];
    mat_copy(y, y, matlist[0], product);
    for (int i = 1; i < x; i++)
    {
        mat_multiply(y, y, y, product, matlist[i], result);
        if (i != x-1)
            mat_copy(y, y, result, product);
    }
}

static void mat_multiply(int x, int y, int z, const int mat1[x][y], const int mat2[y][z], int result[x][z])
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < z; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < y; k++)
                 result[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

static void mat_print(const char *tag, int m, int n, const int matrix[m][n])
{
    printf("%s (%dx%d):\n", tag, m, n);
    for (int i = 0; i < m; i++)
    {
        const char *pad = "";
        for (int j = 0; j < n; j++)
        {
            printf("%s%8d", pad, matrix[i][j]);
            pad = " ";
        }
        putchar('\n');
    }
}

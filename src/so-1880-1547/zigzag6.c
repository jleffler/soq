/* Code for https://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

#include <stdio.h>

static inline int max(int a, int b) { return (a > b) ? a : b; }
static inline int min(int a, int b) { return (a < b) ? a : b; }

static void print_info(int rows, int cols)
{
    int n = rows + cols - 1;
    printf("R = %d, C = %d, N = %d\n", rows, cols, n);
    for (int i = 0; i < n; i++)
    {
        /*
        int max_x = min(i, cols-1);
        int min_x = max(0, i - n + cols);
        int max_y = min(i, rows-1);
        int min_y = max(0, i - n + rows);
        printf("i = %d, min_x = %d, max_x = %d, min_y = %d, max_y = %d\n",
                i, min_x, max_x, min_y, max_y);
        */
        printf("%2d:", i);
        if (i % 2 == 0)
        {
            int max_x = min(i, cols-1);
            int min_x = max(0, i - n + cols);
            for (int j = min_x; j <= max_x; j++)
                /* (col,row) */
                printf(" (%d,%d)", j, i - j);
        }
        else
        {
            int max_y = min(i, rows-1);
            int min_y = max(0, i - n + rows);
            for (int j = min_y; j <= max_y; j++)
                printf(" (%d,%d)", i - j, j);
        }
        putchar('\n');
    }
}

static void zigzag(int rows, int cols, int matrix[rows][cols], int vector[rows*cols])
{
    int n = rows + cols - 1;
    int v = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            int max_x = min(i, cols-1);
            int min_x = max(0, i - n + cols);
            for (int j = min_x; j <= max_x; j++)
                vector[v++] = matrix[i-j][j];
        }
        else
        {
            int max_y = min(i, rows-1);
            int min_y = max(0, i - n + rows);
            for (int j = min_y; j <= max_y; j++)
                vector[v++] = matrix[j][i-j];
        }
    }
}

static void dump_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    printf("%s (%d x %d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%3d", matrix[i][j]);
        putchar('\n');
    }
}

static void dump_vector(const char *tag, int rows, int cols, int vector[rows * cols])
{
    printf("%s (%d : %d):\n", tag, rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        printf("%3d", vector[i]);
        if (i % cols == cols - 1)
            putchar('\n');
    }
}

static void test_8x8(void)
{
    int vector[8*8];
    int matrix[8][8] =
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

    printf("\nTest 8x8\n\n");
    print_info(8, 8);
    dump_matrix("Matrix", 8, 8, matrix);
    zigzag(8, 8, matrix, vector);
    dump_vector("Vector", 8, 8, vector);
}

static void test_9x6(void)
{
    enum { rows = 9 };
    enum { cols = 6 };
    int vector[rows * cols];
    int matrix[rows][cols] =
    {
        {  1,  2,  6,  7, 15, 16, },
        {  3,  5,  8, 14, 17, 27, },
        {  4,  9, 13, 18, 26, 28, },
        { 10, 12, 19, 25, 29, 39, },
        { 11, 20, 24, 30, 38, 40, },
        { 21, 23, 31, 37, 41, 48, },
        { 22, 32, 36, 42, 47, 49, },
        { 33, 35, 43, 46, 50, 53, },
        { 34, 44, 45, 51, 52, 54, },
    };

    printf("\nTest 9x6\n\n");
    print_info(rows, cols);
    dump_matrix("Matrix", rows, cols, matrix);
    zigzag(rows, cols, matrix, vector);
    dump_vector("Vector", rows, cols, vector);
}

int main(void)
{
    test_8x8();
    test_9x6();
    return 0;
}

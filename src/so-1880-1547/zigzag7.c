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
        int max_x = min(i, cols-1);
        int min_x = max(0, i - n + cols);
        int max_y = min(i, rows-1);
        int min_y = max(0, i - n + rows);
        printf("i = %d, min_x = %d, max_x = %d, min_y = %d, max_y = %d\n",
                i, min_x, max_x, min_y, max_y);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%2d:", i);
        if (i % 2 == 0)
        {
            int max_x = min(i, cols-1);
            int min_x = max(0, i - n + cols);
            for (int j = min_x; j <= max_x; j++)
                /* (row,col) */
                printf(" (r=%d,c=%d)", i - j, j);
        }
        else
        {
            int max_y = min(i, rows-1);
            int min_y = max(0, i - n + rows);
            for (int j = min_y; j <= max_y; j++)
                printf(" (r=%d,c=%d)", j, i - j);
        }
        putchar('\n');
    }
}

static void set_zigzag(int rows, int cols, int matrix[rows][cols])
{
    int x = 0;
    int n = rows + cols - 1;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            int max_x = min(i, cols-1);
            int min_x = max(0, i - n + cols);
            for (int j = min_x; j <= max_x; j++)
                matrix[i-j][j] = x++;
        }
        else
        {
            int max_y = min(i, rows-1);
            int min_y = max(0, i - n + rows);
            for (int j = min_y; j <= max_y; j++)
                matrix[j][i-j] = x++;
        }
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

static void test_rows_x_cols(int rows, int cols)
{
    int vector[rows * cols];
    int matrix[rows][cols];

    printf("\nTest %dx%d\n\n", rows, cols);
    print_info(rows, cols);
    set_zigzag(rows, cols, matrix);
    dump_matrix("Matrix", rows, cols, matrix);
    zigzag(rows, cols, matrix, vector);
    dump_vector("Vector", rows, cols, vector);
}

int main(void)
{
    struct
    {
        int rows;
        int cols;
    } test[] =
    {
        { 4, 4 }, { 6, 4 }, { 4, 7 }, { 7, 14 }, { 6, 16 }, { 3, 33 },
    };
    enum { NUM_TEST = sizeof(test) / sizeof(test[0]) };

    for (int i = 0; i < NUM_TEST; i++)
        test_rows_x_cols(test[i].rows, test[i].cols);

    return 0;
}

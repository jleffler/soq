/* SO 4771-9719 - Abuse of VLA definitions (and notations) */
#include <stdio.h>

static int debug = 0;

// Original answer (renamed variables, reordered results, and print row/col + 1)
static void print_sum_rows_cols(int rows, int cols, int array[rows][cols])
{
    for (int r = 0; r < rows; r++)
    {
        int rowsum = 0;
        for (int c = 0; c < cols; c++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", r, c, array[r][c]);
            rowsum += array[r][c];
        }
        if (debug)
            putchar('\n');
        printf("Sum for row %d = %d\n", r + 1, rowsum);
    }
    putchar('\n');
    for (int c = 0; c < cols; c++)
    {
        int colsum = 0;
        for (int r = 0; r < rows; r++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", r, c, array[r][c]);
            colsum += array[r][c];
        }
        if (debug)
            putchar('\n');
        printf("Sum for col %d = %d\n", c + 1, colsum);
    }
}

static int n;   // Rows
static int m;   // Columns

// Adapted print_sum_rows_cols with size from n, m
// Using n, m is unnecessary coupling (and can lead to erroneous results)
static void bogus_sum_rows_cols(int array[n][m], int rows, int cols)
{
    for (int r = 0; r < rows; r++)
    {
        int rowsum = 0;
        for (int c = 0; c < cols; c++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", r, c, array[r][c]);
            rowsum += array[r][c];
        }
        if (debug)
            putchar('\n');
        printf("Sum for row %d = %d\n", r, rowsum);
    }
    putchar('\n');
    for (int c = 0; c < cols; c++)
    {
        int colsum = 0;
        for (int r = 0; r < rows; r++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", r, c, array[r][c]);
            colsum += array[r][c];
        }
        if (debug)
            putchar('\n');
        printf("Sum for col %d = %d\n", c, colsum);
    }
}

// Original answer from OP - bogus results (debug printing added).
// Using n, m is unnecessary coupling (and can lead to erroneous results)
// Using i, j as arguments is bogus; the values passed in are ignored
// The 'sum column' loops are completely bogus.  The outer loop should
// iterate over columns [0..c) and the inner loop over rows [0..r).
// See print_sum_rows_cols() for the correct (minimal) interface.
static void sum_row_column(int array[n][m], int r, int c, int i, int j)
{
    int sumOfColumn = 0;
    int sumOfRow = 0;
    printf("\n");
    for (i = 0; i < r; i++)
    {
        sumOfRow = 0;
        for (j = 0; j < c; j++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", i, j, array[i][j]);
            sumOfRow += array[i][j];
        }
        if (debug)
            putchar('\n');
        printf("Sum of %d.row=%d\n", i + 1, sumOfRow);
    }
    printf("\n");
    for (j = 0; j < r; j++)
    {
        sumOfColumn = 0;
        for (i = 0; i < c; i++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", i, j, array[i][j]);
            sumOfColumn += array[i][j];
        }
        if (debug)
            putchar('\n');
        printf("Sum of %d.column=%d\n", j + 1, sumOfColumn);
    }
}

// Semi-fixed answer from OP - bogus results (debug printing added).
// Using n, m is unnecessary coupling (and can lead to erroneous results)
// Using i, j as arguments is bogus; the values passed in are ignored
// The 'sum column' loops are completely bogus.  The outer loop should
// iterate over columns [0..c) and the inner loop over rows [0..r).
// See print_sum_rows_cols() for the correct (minimal) interface.
static void bogus_sum_row_column(int array[n][m], int r, int c, int i, int j)
{
    int sumOfColumn = 0;
    int sumOfRow = 0;
    printf("\n");
    for (i = 0; i < r; i++)
    {
        sumOfRow = 0;
        for (j = 0; j < c; j++)
        {
            if (debug)
                printf("   a[%d][%d] = %d", i, j, array[i][j]);
            sumOfRow += array[i][j];
        }
        if (debug)
            putchar('\n');
        printf("Sum of %d.row=%d\n", i + 1, sumOfRow);
    }
    printf("\n");
    for (j = 0; j < c; j++)     // c, not r
    {
        sumOfColumn = 0;
        for (i = 0; i < r; i++) // r, not c
        {
            if (debug)
                printf("   a[%d][%d] = %d", i, j, array[i][j]);
            sumOfColumn += array[i][j];
        }
        if (debug)
            putchar('\n');
        printf("Sum of %d.column=%d\n", j + 1, sumOfColumn);
    }
}

static void dump_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    printf("Matrix %s (%dx%d):\n", tag, rows, cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            printf("%3d", matrix[r][c]);
        putchar('\n');
    }
}

static void test_sequence(int v_debug, int v_n, int v_m, const char *tag,
                          int rows, int cols, int matrix[rows][cols])
{
    debug = v_debug;
    n = v_n;
    m = v_m;
    dump_matrix(tag, rows, cols, matrix);
    printf("\nprint_sum_rows_cols():\n");
    print_sum_rows_cols(rows, cols, matrix);
    printf("\nbogus_sum_rows_cols() - (n = %d, m = %d):\n", n, m);
    bogus_sum_rows_cols(matrix, rows, cols);
    printf("\nsum_row_column()(n = %d, m = %d):\n", n, m);
    sum_row_column(matrix, rows, cols, -1, -1);
    printf("\nbogus_sum_row_column()(n = %d, m = %d):\n", n, m);
    bogus_sum_row_column(matrix, rows, cols, -1, -1);
    putchar('\n');
}

static void test_matrix_summation(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    test_sequence(1,    2,    2, tag, rows, cols, matrix);
    test_sequence(0, rows, cols, tag, rows, cols, matrix);
}

int main(void)
{
    int a1[3][4] =
    {
        { 68, 78, 50, 46, },
        { 64, 12, 47,  1, },
        { 86, 10, 84, 62, },
    };
    int a2[5][3] =
    {
        {  4, 30, 19, },
        { 79, 58, 20, },
        { 95, 12, 24, },
        { 20, 37, 72, },
        { 17,  0, 53, },
    };
    int a3[3][3] =
    {
        { 96, 84, 13, },
        { 63, 29, 80, },
        { 97, 98, 48, },
    };

    test_matrix_summation("A1", 3, 4, a1);
    test_matrix_summation("A2", 5, 3, a2);
    test_matrix_summation("A3", 3, 3, a3);

    return 0;
}


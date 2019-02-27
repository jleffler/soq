/* SO 4771-9719 */
#include <stdio.h>

static void print_sum_rows_cols(int r, int c, int array[r][c])
{
    for (int col = 0; col < c; col++)
    {
        int colsum = 0;
        for (int row = 0; row < r; row++)
            colsum += array[row][col];
        printf("Sum for col %d = %d\n", col, colsum);
    }
    for (int row = 0; row < r; row++)
    {
        int rowsum = 0;
        for (int col = 0; col < c; col++)
            rowsum += array[row][col];
        printf("Sum for row %d = %d\n", row, rowsum);
    }
}

static void dump_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            printf("%3d", matrix[r][c]);
        putchar('\n');
    }
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

    dump_matrix("A1", 3, 4, a1);
    print_sum_rows_cols(3, 4, a1);

    dump_matrix("A2", 5, 3, a2);
    print_sum_rows_cols(5, 3, a2);

    return 0;
}


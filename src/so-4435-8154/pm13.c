#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int max_element(int rows, int cols, int matrix[rows][cols])
{
    int max = matrix[0][0];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
    }
    return max;
}

static void print_line(int wid, int cols)
{
    char buffer[wid + 1];
    memset(buffer, '-', wid);
    buffer[wid] = '\0';
    putchar('+');
    for (int i = 0; i < cols; i++)
        printf("%s+", buffer);
    putchar('\n');
}

static void print_row(int width, int cols, int vector[cols])
{
    putchar('|');
    for (int i = 0; i < cols; i++)
        printf(" %*d |", width, vector[i]);
    putchar('\n');
}

static void print_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    printf("\n%s:\n", tag);
    int max = max_element(rows, cols, matrix);
    int width = snprintf(0, 0, "%d", max);

    print_line(width + 2, cols);
    for (int i = 0; i < rows; i++)
    {
        print_row(width, cols, matrix[i]);
        print_line(width + 2, cols);
    }
}

static void test_matrix(int rows, int cols)
{
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] = (1234 * j + i * 81);
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%dx%d matrix", rows, cols);
    print_matrix(buffer, rows, cols, matrix);
}

static void random_matrix(int rows, int cols)
{
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand();
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%dx%d random matrix", rows, cols);
    print_matrix(buffer, rows, cols, matrix);
}

int main(void)
{
    test_matrix(3, 3);
    test_matrix(5, 7);
    test_matrix(11, 7);
    srand(time(0));
    random_matrix(6, 6);
    return 0;
}


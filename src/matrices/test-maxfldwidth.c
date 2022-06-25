#include "maxfldwidth.c"
#include <limits.h>
#include <stdlib.h>

static void fill_data_neg(size_t n, size_t m, int data[n][m], int value1, int value2)
{
    assert(n == 3 && m == 3);
    data[0][0] = -value1;
    data[0][1] = -1;
    data[0][2] = +value2;
    data[1][0] = +1;
    data[1][1] = 0;
    data[1][2] = -1;
    data[2][0] = +value1;
    data[2][1] = +1;
    data[2][2] = -value2;
}

static void fill_data_pos(size_t n, size_t m, int data[n][m], int value1, int value2)
{
    assert(n == 3 && m == 3);
    data[0][0] = abs(value1);
    data[0][1] = 1;
    data[0][2] = abs(value2);
    data[1][0] = 1;
    data[1][1] = 0;
    data[1][2] = 1;
    data[2][0] = abs(value1);
    data[2][1] = 1;
    data[2][2] = abs(value2);
}

static void print_matrix(size_t rows, size_t cols, int data[rows][cols])
{
    int width = max_field_width(rows, cols, data);
    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < cols; c++)
        {
            printf("%s[%*d]", pad, width, data[r][c]);
            pad = " ";
        }
        putchar('\n');
    }
}

int main(void)
{
    enum { DATA_SIZE = 3 };
    int data[DATA_SIZE][DATA_SIZE];

    int xy[][2] =
    {
        { 100, 9999 },
        { 10, 99 },
        { 1, 9 },
        { 1, 999999 },
        { INT_MIN+1, INT_MAX },
    };
    enum { XY_SIZE = sizeof(xy) / sizeof(xy[0]) };

    for (int i = 0; i < XY_SIZE; i++)
    {
        fill_data_neg(DATA_SIZE, DATA_SIZE, data, xy[i][0], xy[i][1]);
        printf("Range %d..%d:\n", xy[i][0], xy[i][1]);
        print_matrix(DATA_SIZE, DATA_SIZE, data);
    }
    fill_data_pos(DATA_SIZE, DATA_SIZE, data, 0, 9);
    printf("Range %d..%d:\n", 0, 9);
    print_matrix(DATA_SIZE, DATA_SIZE, data);
    return 0;
}


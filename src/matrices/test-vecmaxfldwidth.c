#include "vecmaxfldwidth.c"
#include <limits.h>
#include <stdlib.h>

static void fill_data_neg(size_t n, int data[n], int value1, int value2)
{
    assert(n == 9);
    data[0] = -value1;
    data[1] = -1;
    data[2] = +value2;
    data[3] = +1;
    data[4] = 0;
    data[5] = -1;
    data[6] = +value1;
    data[7] = +1;
    data[8] = -value2;
}

static void fill_data_pos(size_t n, int data[n], int value1, int value2)
{
    assert(n == 9);
    data[0] = abs(value1);
    data[1] = 1;
    data[2] = abs(value2);
    data[3] = 1;
    data[4] = 0;
    data[5] = 1;
    data[6] = abs(value1);
    data[7] = 1;
    data[8] = abs(value2);
}

static void print_vector(size_t rows, int data[rows])
{
    int width = max_field_width(rows, data);
    const char *pad = "";
    for (size_t r = 0; r < rows; r++)
    {
        printf("%s[%*d]", pad, width, data[r]);
        pad = " ";
    }
    putchar('\n');
}

int main(void)
{
    enum { DATA_SIZE = 9 };
    int data[DATA_SIZE];

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
        fill_data_neg(DATA_SIZE, data, xy[i][0], xy[i][1]);
        printf("Range %d..%d:\n", xy[i][0], xy[i][1]);
        print_vector(DATA_SIZE, data);
    }
    fill_data_pos(DATA_SIZE, data, 0, 9);
    printf("Range %d..%d:\n", 0, 9);
    print_vector(DATA_SIZE, data);
    return 0;
}


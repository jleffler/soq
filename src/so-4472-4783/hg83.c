/* SO 4472-4783 */
#include <assert.h>
#include <stdio.h>

enum { ARR_SIZE = 6 };

static int hourglass_1(int a[ARR_SIZE][ARR_SIZE], int i, int j)
{
    assert(i >= 0 && i < ARR_SIZE - 2 && j >= 0 && j < ARR_SIZE - 2);
    int sum = a[i+0][j+0] + a[i+0][j+1] + a[i+0][j+2]
                          + a[i+1][j+1] +
              a[i+2][j+0] + a[i+2][j+1] + a[i+2][j+2];
    return sum;
}

static int hourglass_2(int a[ARR_SIZE][ARR_SIZE], int i, int j)
{
    assert(i >= 0 && i < ARR_SIZE - 2 && j >= 0 && j < ARR_SIZE - 2);
    static const int rows[] = { 0, 0, 0, 1, 2, 2, 2 };
    static const int cols[] = { 0, 1, 2, 1, 0, 1, 2 };
    enum { HG_SIZE = sizeof(rows) / sizeof(rows[0]) };
    int sum = 0;
    for (int k = 0; k < HG_SIZE; k++)
        sum += a[rows[k]+i][cols[k]+j];
    return sum;
}

static int hourglass_3(int a[ARR_SIZE][ARR_SIZE], int i, int j)
{
    assert(i >= 0 && i < ARR_SIZE - 2 && j >= 0 && j < ARR_SIZE - 2);
    int sum = 0;
    for (int i1 = 0; i1 < 3; i1++)
    {
        for (int j1 = 0; j1 < 3; j1++)
        {
            if (i1 == 1)
            {
                sum += a[i + i1][j + j1 + 1];
                break;
            }
            else
                sum += a[i + i1][j + j1];
        }
    }
    return sum;
}

static int hourglass_4(int a[ARR_SIZE][ARR_SIZE], int i, int j)
{
    assert(i >= 0 && i < ARR_SIZE - 2 && j >= 0 && j < ARR_SIZE - 2);
    int n = i + 3;
    int m = j + 3;
    int sum = 0;
    for (int i1 = i; i1 < n; i1++)
    {
        for (int j1 = j; j1 < m; j1++)
        {
            if (i1 == n - 2)
            {
                sum += a[i1][j1 + 1];
                break;
            }
            else
                sum += a[i1][j1];
        }
    }
    return sum;
}

typedef int (*HourGlass)(int arr[ARR_SIZE][ARR_SIZE], int i, int j);

static void test_function(int arr[ARR_SIZE][ARR_SIZE], const char *tag, HourGlass function)
{
    int max_sum = 0;
    int max_row = 0;
    int max_col = 0;
    for (int i = 0; i < (ARR_SIZE-2); i++)
    {
        for (int j = 0; j < (ARR_SIZE-2); j++)
        {
            int n = (*function)(arr, i, j);
            if (n > max_sum || (i == 0 && j == 0))
            {
                max_sum = n;
                max_row = i;
                max_col = j;
            }
        }
    }

    printf("%s: %3d at (r=%d,c=%d)\n", tag, max_sum, max_row, max_col);
}

int main(void)
{
    int arr[ARR_SIZE][ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++)
    {
        for (int j = 0; j < ARR_SIZE; j++)
        {
            if (scanf("%d", &arr[i][j]) != 1)
            {
               fprintf(stderr, "Failed to read integer (for row %d, col %d)\n", i, j);
               return 1;
            }
        }
    }

    test_function(arr, "hourglass_1", hourglass_1);
    test_function(arr, "hourglass_2", hourglass_2);
    test_function(arr, "hourglass_3", hourglass_3);
    test_function(arr, "hourglass_4", hourglass_4);

    return 0;
}

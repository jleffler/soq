/* SO 7483-2964 */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void err_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static int userInput(void)
{
    int a;
    printf("Input your number: ");
    if (scanf("%d", &a) != 1)
        err_exit("Failed to read input number\n");
    return a;
}

static void arrayPrint(const char *tag, int wid, int rows, int cols, int arr[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        const char *pad = "";
        for (int j = 0; j < cols; j++)
        {
            printf("%s%*d", pad, wid, arr[i][j]);
            pad = " ";
        }
        putchar('\n');
    }
}

static void arrayInitialize(int row, int col, int arr[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            arr[i][j] = rand() % 100;
    }
}

static void arrayMultiply(int r1, int c1, int arr1[r1][c1],
                          int r2, int c2, int arr2[r2][c2], int arr3[r1][c2])
{
    assert(c1 == r2);
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            int sum = 0;
            for (int a = 0; a < c1; a++)
                sum += arr1[i][a] * arr2[a][j];
            arr3[i][j] = sum;
        }
    }
}

enum { MAX_ROWS = 16, MAX_COLS = 16 };

int main(void)
{
    int r1 = userInput();
    int c1 = userInput();
    if (r1 <= 0 || r1 > MAX_ROWS || c1 <= 0 || c1 > MAX_COLS)
        err_exit("Invalid dimensions (%d, %d) for array1\n", r1, c1);

    int r2 = userInput();
    int c2 = userInput();
    if (r2 <= 0 || r2 > MAX_ROWS || c2 <= 0 || c2 > MAX_COLS)
        err_exit("Invalid dimensions (%d, %d) for array2\n", r2, c2);
    if (c1 != r2)
        err_exit("wrong values of rows or columns (%d, %d) vs (%d, %d): %d != %d\n",
                r1, c1, r2, c2, c1, r2);

    putchar('\n');
    srand(time(NULL));

    int array1[r1][c1];
    int array2[r2][c2];
    int array3[r1][c2];

    arrayInitialize(r1, c1, array1);
    arrayPrint("array1", 3, r1, c1, array1);
    arrayInitialize(r2, c2, array2);
    arrayPrint("array2", 3, r2, c2, array2);
    arrayMultiply(r1, c1, array1, r2, c2, array2, array3);
    arrayPrint("array3", 6, r1, c2, array3);

    return 0;
}

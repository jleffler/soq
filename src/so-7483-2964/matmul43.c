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
    {
        fprintf(stderr, "Failed to read input number\n");
        exit(EXIT_FAILURE);
    }
    return a;
}

// allocate a 2D array
static int **allocate2D(int rows, int cols)
{
    int **arr2D = (int **)malloc(rows * sizeof(int *));
    if (arr2D == NULL)
        err_exit("failed to allocate %zu bytes of memory\n", rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        arr2D[i] = (int *)malloc(cols * sizeof(int));
        if (arr2D[i] == NULL)
            err_exit("failed to allocate %zu bytes of memory\n", cols * sizeof(int));
    }
    return arr2D;
}

static void deallocate2D(int **arr2D, int rows)
{
    for (int i = 0; i < rows; i++)
        free(arr2D[i]);
    free(arr2D);
}

static void arrayPrint(const char *tag, int wid, int **arr, int rows, int cols)
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

static void arrayInitialize(int **array1, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            array1[i][j] = rand() % 100;
    }
}

static void arrayMultiply(int **arr1, int **arr2, int **arr3, int r1, int c1, int r2, int c2)
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
        fprintf(stderr, "Invalid dimensions (%d, %d) for array1\n", r1, c1);

    int r2 = userInput();
    int c2 = userInput();
    if (r2 <= 0 || r2 > MAX_ROWS || c2 <= 0 || c2 > MAX_COLS)
        fprintf(stderr, "Invalid dimensions (%d, %d) for array2\n", r2, c2);

    putchar('\n');
    srand(time(NULL));

    int **array1 = allocate2D(r1, c1);
    int **array2 = allocate2D(r2, c2);
    int **array3 = allocate2D(r1, c2);

    if (c1 == r2)
    {
        arrayInitialize(array1, r1, c1);
        arrayPrint("array1", 3, array1, r1, c1);
        arrayInitialize(array2, r2, c2);
        arrayPrint("array2", 3, array2, r2, c2);
        arrayMultiply(array1, array2, array3, r1, c1, r2, c2);
        arrayPrint("array3", 6, array3, r1, c2);
    }
    else
        fprintf(stderr, "wrong values of rows or columns (%d, %d) vs (%d, %d): %d != %d\n",
                r1, c1, r2, c2, c1, r2);

    deallocate2D(array1, r1);
    deallocate2D(array2, r2);
    deallocate2D(array3, r1);

    return 0;
}

### Stack Overflow Question 7483-2964

[SO 7483-2964](https://stackoverflow.com/q/74832964) &mdash;
HEAP CORRUPTION DETECTED: after normal block CRT detected that the application wrote to memory

### Answer

As I noted in comments:

1. [`srand()` — why call it only
     once?](https://stackoverflow.com/q/7343833/15168)
2. You aren't allocating the correct space for array3.  If you multiply
   an NxM matrix by a PxQ matrix, then M must equal P and the result is
   an NxQ matrix.
3. Your test for whether the two matrices can be multiplied is wrong.
   You should be checking that `c1 == r2` if you are multiplying
   `array1` by `array2`.  It would be perverse to pass `array1` as the
   first argument and `array2` as the second argument and then multiply
   `array2` by `array1`.  Of course, if they're square matrices, there
   won't be a problem, but that's an accident rather than deliberate.

Here is a fairly minimal upgrade to your code that fixes those problems.
It separates the array printing from the initialization and
multiplication functions.  Mixing I/O and arithmetic is rarely a good
idea.  It also checks the memory allocations — which is always
necessary.  And it checks the inputs — which is also always necessary.

```c
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
```

Example run:

```none
Input your number: 3
Input your number: 5
Input your number: 5
Input your number: 4

array1 (3x5):
 62   5  74  71  53
 97  34  47  23  33
 51  85  62  43  57
array2 (5x4):
 29  60   1  54
 38  36  92  76
 22  99  68  44
 23  25  74   6
 13  51  27  68
array3 (3x4):
  5938  15704  12239  11014
  6097  13955   9014  12272
  7803  16240  16808  16076
```

Since the arrays are quite small (the revised code only allows arrays up
to 16x16, so each array is a maximum of 1 KiB on a system where
`sizeof(int) == 4`, there is no particular need to use dynamic memory
allocation even for VLAs (variable-length arrays).  Using VLAs in the
called functions makes for very easy notations.  Here is a version that
uses direct memory allocation:

```c
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
```

And if you are worried about VLAs breaking the stack limit, here's a
variant that uses dynamic memory allocation for the arrays.  The called
functions haven't changed, but the allocation for the arrays and the
function calls have changed.

```c
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

    int (*array1)[r1][c1] = malloc(r1 * c1 * sizeof((*array1)[0][0]));
    if (*array1 == NULL)
        err_exit("failed to allocate %zu bytes of memory\n", (r1 * c1 * sizeof((*array1)[0][0])));
    int (*array2)[r2][c2] = malloc(r2 * c2 * sizeof((*array1)[0][0]));
    if (*array2 == NULL)
        err_exit("failed to allocate %zu bytes of memory\n", (r2 * c2 * sizeof((*array2)[0][0])));
    int (*array3)[r1][c2] = malloc(r1 * c2 * sizeof((*array1)[0][0]));
    if (*array3 == NULL)
        err_exit("failed to allocate %zu bytes of memory\n", (r1 * c2 * sizeof((*array3)[0][0])));

    arrayInitialize(r1, c1, *array1);
    arrayPrint("array1", 3, r1, c1, *array1);
    arrayInitialize(r2, c2, *array2);
    arrayPrint("array2", 3, r2, c2, *array2);
    arrayMultiply(r1, c1, *array1, r2, c2, *array2, *array3);
    arrayPrint("array3", 6, r1, c2, *array3);

    free(*array1);
    free(*array2);
    free(*array3);

    return 0;
}
```

If run from a script with the same inputs and during the same second,
then the three programs produce the same result.  That's a deficiency in
using `time()` as the seed for `srand()` — but it is also convenient
for testing.


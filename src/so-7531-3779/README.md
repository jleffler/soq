### Stack Overflow Question 7531-3779

[SO 7531-3779](https://stackoverflow.com/q/75313779) &mdash;
How do variable length arrays support numeric processing?

### Question

I am reading C The Complete Reference 4th edition by Herbert Schildt.
In Chapter 4 - Arrays and Strings, it mentions "One major reason for the
addition of variable-length arrays to C99 is to support numeric
processing".

My question is: What is numeric processing?  And how do variable-length
arrays support numeric processing?

### Answer

There are three places where variable-length arrays can appear:

1. Automatic local variables.
2. Dynamically allocated arrays.
3. Function parameters.

Automatic local variables can be problematic — they occupy stack
space, and there's no portable way to find out whether there's enough
stack space left to allocate the array you want to create.  If there
isn't enough space, the program will halt unilaterally; there is no way
to recover from the error.  This has many people up in arms against
VLAs.

Dynamically allocated arrays are not problematic — though the notation
is not singularly convenient.  You can tell when an allocation fails and
react appropriately.

Function parameters are where the flexibility comes into play —
especially with 2D arrays (and higher dimensions too).

Prior to the introduction of VLAs, you had to either treat the array as
a 1D vector and calculate the indexes manually or you had to write
different functions for each different size of matrix — or, at least,
for each different number of columns.

You could use:
```
enum { NCOLS = 8 };
static void dump_array(const char *tag, size_t nrows, int array[][NCOLS])
{
    printf("%s: (%zux%d)\n", tag, nrows, NCOLS);  // Note %zu vs %d!
    for (size_t r = 0; r < nrows; r++)
    {
        for (size_t c = 0; c < NCOLS; c++)
            printf(" %5d", array[r][c]);
        putchar('\n');
    }
}
```
That's fine as far as it goes, but if you want matrices with different
numbers of columns, you have to write (and call) different functions.

An alternative was to use a large 1D vector and calculate the 2D
subscripts in your code:
```
static void dump_array(const char *tag, size_t nrows, size_t ncols, int array[])
{
    printf("%s: (%zux%zu)\n", tag, nrows, ncols);
    for (size_t r = 0; r < nrows; r++)
    {
        for (size_t c = 0; c < ncols; c++)
            printf(" %5d", array[r * ncols + c]);
        putchar('\n');
    }
}
```

With VLA notation for the arguments, though, you can write a single
function to print any 2D matrix (of a given base type) and use direct
subscript notation for maximum convenience:
```
static void dump_array(const char *tag, size_t nrows, size_t ncols, int array[nrows][ncols])
{
    printf("%s: (%zux%zu)\n", tag, nrows, ncols);
    for (size_t r = 0; r < nrows; r++)
    {
        for (size_t c = 0; c < ncols; c++)
            printf(" %5d", array[r][c]);
        putchar('\n');
    }
}
```
There isn't much difference in the notation, but the gain in flexibility
is enormous.  You can write a single matrix multiplication function that
will work for any sizes of matrix, for example, whereas before VLAs were
available, only the 1D version could deal with arbitrary sizes of array.

The dynamic allocation is reasonably simple, though not entirely obvious:
```
/* SO 7531-3779 */

#include <stdio.h>
#include <stdlib.h>

static void dump_array(const char *tag, size_t rows, size_t cols, int array[rows][cols])
{
    printf("%s (%zux%zu):\n", tag, rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        printf("%2zu:", r);
        for (size_t c = 0; c < cols; c++)
            printf(" %5d", array[r][c]);
        putchar('\n');
    }
}

int main(void)
{
    size_t rows = 13;
    size_t cols = 8;
    int (*array)[8] = malloc(sizeof(int [rows][cols]));

    for (size_t r = 0; r < rows; r++)
    {
        int sign = -1;
        for (size_t c = 0; c < cols; c++)
        {
            array[r][c] = sign * ((r + 1) * 100 + c + 1);
            sign = -sign;
        }
    }

    dump_array("Array 1", rows, cols, array);

    free(array);
    return 0;
}
```
Output:
```none
Array 1 (13x8):
 0:  -101   102  -103   104  -105   106  -107   108
 1:  -201   202  -203   204  -205   206  -207   208
 2:  -301   302  -303   304  -305   306  -307   308
 3:  -401   402  -403   404  -405   406  -407   408
 4:  -501   502  -503   504  -505   506  -507   508
 5:  -601   602  -603   604  -605   606  -607   608
 6:  -701   702  -703   704  -705   706  -707   708
 7:  -801   802  -803   804  -805   806  -807   808
 8:  -901   902  -903   904  -905   906  -907   908
 9: -1001  1002 -1003  1004 -1005  1006 -1007  1008
10: -1101  1102 -1103  1104 -1105  1106 -1107  1108
11: -1201  1202 -1203  1204 -1205  1206 -1207  1208
12: -1301  1302 -1303  1304 -1305  1306 -1307  1308
```
And the VLA notation can be used with fixed-size arrays — global or
local — too.  That is, ordinary arrays can be passed to functions that
accept a VLA as long as you describe the arrays accurately:
```
/* SO 7531-3779 */

#include <stdio.h>
#include <stdlib.h>

static void dump_array(const char *tag, size_t rows, size_t cols, int array[rows][cols])
{
    printf("%s (%zux%zu):\n", tag, rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        printf("%2zu:", r);
        for (size_t c = 0; c < cols; c++)
            printf(" %5d", array[r][c]);
        putchar('\n');
    }
}

/* Created by: gen_matrix -r 9 -c 5 -L -9999 -H +9999 -x -n matrix1 -w5 -E */
/* Random seed: 0x7F3F1FA0 */
int matrix1[9][5] =
{
    {  9337,  5320,  5059,  1115,    14, },
    { -7514, -1643,  8461,  1613,  6968, },
    {  2469,  8307, -8045,  2327, -7862, },
    {  8174, -7062,   666, -3480,  1836, },
    { -2400, -7863, -1859,  2436, -6840, },
    {  5819, -4112, -2037,  9005, -9748, },
    {   823, -9687,  1245, -2074,  3741, },
    {  4812, -9254, -6365, -1263, -9265, },
    { -9400, -5479, -3756, -7417, -5726, },
};
enum { MATRIX1_ROWS = 9, MATRIX1_COLS = 5 };

int main(void)
{
    /* Created by: gen_matrix -E -r 13 -c 8 -H 999 -L -999 -i -w4 -n matrix2 */
    /* Random seed: 0x64347CFE */
    int matrix2[13][8] =
    {
        {  -27, -268,   73,  112, -148,  407, -411,  418, },
        { -782,  368, -306, -830, -851,    9,  505,   33, },
        { -558, -979,  471,  376, -290, -270, -910,  812, },
        { -374,  201,  454,  966,  -39,  653, -747, -664, },
        {  322,  385, -141, -326,   37,  941, -298, -281, },
        {  529,   68, -995,  -30, -942, -670,  563, -244, },
        {  773,   46, -315, -363,  732,  218,  230,  536, },
        {  566, -164, -493,  568, -256, -196, -635, -387, },
        {  452, -348,   79,  103, -416, -756,  688, -473, },
        { -294, -641,  530, -307,  508,  878, -786, -745, },
        {  427,  462, -229,  253,  116, -804,  -72,  -35, },
        { -776,  290,  158,  154,  662, -621,  576,  388, },
        {  999, -684, -207, -506,  708, -949,  149, -969, },
    };
    enum { MATRIX2_ROWS = 13, MATRIX2_COLS = 8 };

    dump_array("Matrix 1", MATRIX1_ROWS, MATRIX1_COLS, matrix1);
    dump_array("Matrix 2", MATRIX2_ROWS, MATRIX2_COLS, matrix2);

    return 0;
}
```
Output:
```none
Matrix 1 (9x5):
 0:  9337  5320  5059  1115    14
 1: -7514 -1643  8461  1613  6968
 2:  2469  8307 -8045  2327 -7862
 3:  8174 -7062   666 -3480  1836
 4: -2400 -7863 -1859  2436 -6840
 5:  5819 -4112 -2037  9005 -9748
 6:   823 -9687  1245 -2074  3741
 7:  4812 -9254 -6365 -1263 -9265
 8: -9400 -5479 -3756 -7417 -5726
Matrix 2 (13x8):
 0:   -27  -268    73   112  -148   407  -411   418
 1:  -782   368  -306  -830  -851     9   505    33
 2:  -558  -979   471   376  -290  -270  -910   812
 3:  -374   201   454   966   -39   653  -747  -664
 4:   322   385  -141  -326    37   941  -298  -281
 5:   529    68  -995   -30  -942  -670   563  -244
 6:   773    46  -315  -363   732   218   230   536
 7:   566  -164  -493   568  -256  -196  -635  -387
 8:   452  -348    79   103  -416  -756   688  -473
 9:  -294  -641   530  -307   508   878  -786  -745
10:   427   462  -229   253   116  -804   -72   -35
11:  -776   290   158   154   662  -621   576   388
12:   999  -684  -207  -506   708  -949   149  -969
```

/* SO 4152-8342 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dump_array(const char *tag, size_t n_rows, size_t n_cols, int A[n_rows][n_cols]);

enum { COLS  = 3 };

extern int cmp_func (const void *a, const void *b);

int cmp_func(const void *va, const void *vb)
{
    const int *a = *(const int (*)[COLS])va;
    const int *b = *(const int (*)[COLS])vb;

    for (int i = 0; i < COLS; i++)
    {
        char str1[20], str2[20];
        sprintf(str1, "%d", a[i]);
        sprintf(str2, "%d", b[i]);
        int rc = strcmp(str1, str2);
        if (rc != 0)
            return rc;
    }
    return 0;
}

int main(void)
{
    int A[][COLS] =
    {
        { 1, 91, 10 },
        { 1,  9,  9 },
        { 1,  9, 11 },
        { 1,  1,  5 },
        { 1,  9, 10 },
        { 1,  0,  1 },
        { 1,  2,  3 },
        { 1, 91, 10 },
        { 1, 19,  0 },
        { 1, 91,  0 },
        { 1,  2,  0 },
        { 1,  2,  1 },
    };
    enum { ROWS = sizeof(A) / sizeof(A[0]) };

    dump_array("Before", ROWS, COLS, A);
    qsort(A, ROWS, sizeof(A[0]), cmp_func);
    dump_array("After", ROWS, COLS, A);
    return 0;
}

static void dump_array(const char *tag, size_t n_rows, size_t n_cols, int A[n_rows][n_cols])
{
    printf("%s:\n", tag);
    for (size_t r = 0; r < n_rows; r++)
    {
        const char *pad = "{";
        for (size_t c = 0; c < n_cols; c++)
        {
            printf("%s%3d", pad, A[r][c]);
            pad = ",";
        }
        puts(" }");
    }
}

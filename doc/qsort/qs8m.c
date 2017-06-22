/* SO 4348-0000 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stderr.h"
#include "timer.h"
#include <time.h>

enum { ARR_WIDTH = 6 };

static int cmpint(const void *v1, const void *v2)
{
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;
    return (i1 > i2) - (i1 < i2);
}

static int cmpfunc2(const void *a, const void *b)
{
    const int *rowA = *(const int **)a;
    const int *rowB = *(const int **)b;

    for (int i = 0; i < ARR_WIDTH; i++)
    {
        int cmp = (rowA[i] > rowB[i]) - (rowA[i] < rowB[i]);
        if (cmp)
            return cmp;
    }
    return 0;
}

static int cmpfunc1(const void *a, const void *b)
{
    const int *rowA = *(const int **)a;
    const int *rowB = *(const int **)b;

    if (rowA[0] > rowB[0])
        return 1;
    if (rowA[0] < rowB[0])
        return -1;

    if (rowA[1] > rowB[1])
        return 1;
    if (rowA[1] < rowB[1])
        return -1;

    if (rowA[2] > rowB[2])
        return 1;
    if (rowA[2] < rowB[2])
        return -1;

    if (rowA[3] > rowB[3])
        return 1;
    if (rowA[3] < rowB[3])
        return -1;

    if (rowA[4] > rowB[4])
        return 1;
    if (rowA[4] < rowB[4])
        return -1;

    if (rowA[5] > rowB[5])
        return 1;
    if (rowA[5] < rowB[5])
        return -1;

    return 0;
}

static void test_qsort(const char *tag, int lineCount, unsigned seed, int (*cmp)(const void *v1, const void *v2))
{
    printf("%s: number = %d; seed = %u\n", tag, lineCount, seed);
    srand(seed);

    Clock clk;
    clk_init(&clk);

    clk_start(&clk);
    int **allRecords = (int **) malloc(lineCount * sizeof(int *));
    assert(allRecords != 0);
    for (int i = 0; i < lineCount; i++)
    {
        allRecords[i] = (int *) malloc(ARR_WIDTH * sizeof(int));
        assert(allRecords[i] != 0);
        for (int j = 0; j < ARR_WIDTH; j++)
            allRecords[i][j] = rand() % 100;
        qsort(allRecords[i], 6, sizeof(int), cmpint);
    }
    clk_stop(&clk);
    char buffer[32];
    printf("%s: Initialization = %ss\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)));

    clk_start(&clk);
    qsort(allRecords, lineCount, sizeof(int *), cmp);
    clk_stop(&clk);
    printf("%s: Sorting done = %ss\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)));

    clk_start(&clk);
    for (int i = 0; i < lineCount - 1; i++)
        assert(cmp(&allRecords[i], &allRecords[i + 1]) <= 0);
    for (int i = 0; i < lineCount; i++)
        free(allRecords[i]);
    free(allRecords);
    clk_stop(&clk);
    printf("%s: Check and free = %ss\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
}

int main(int argc, char **argv)
{
    unsigned seed = time(0);

    err_setarg0(argv[0]);
    int lineCount = 8 * 1000 * 1000;
    if (argc == 2)
        lineCount = atoi(argv[1]);

    for (int i = 0; i < 10; i++)
    {
        test_qsort("cmpfunc1", lineCount, seed, cmpfunc1);
        test_qsort("cmpfunc2", lineCount, seed, cmpfunc2);
    }

    return 0;
}

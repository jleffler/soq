#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline int lt_index(int r, int c) { assert(r >= c); return r * (r + 1) / 2 + c; }

int main(void)
{
    int matrixsize = 5;

    /* Technique 1 */
    char *lt_matrix1 = malloc(matrixsize * (matrixsize + 1) / 2 * sizeof(*lt_matrix1));
    assert(lt_matrix1 != 0);  // Appalling error checking

    char value = 'a';
    for (int i = 0; i < matrixsize; i++)
    {
        for (int j = 0; j <= i; j++)
            lt_matrix1[lt_index(i, j)] = value++;
    }

    for (int i = 0; i < matrixsize; i++)
    {
        int j;
        for (j = 0; j <= i; j++)
            printf("%-3c", lt_matrix1[lt_index(i, j)]);
        for (; j < matrixsize; j++)
            printf("%-3c", '-');
        putchar('\n');
    }

    free(lt_matrix1);

    /* Technique 2 */
    char **lt_matrix2 = malloc(matrixsize * sizeof(*lt_matrix2));
    assert(lt_matrix2 != 0);
    char *lt_data2 = malloc(matrixsize * (matrixsize + 1) / 2 * sizeof(*lt_matrix1));
    for (int i = 0; i < matrixsize; i++)
        lt_matrix2[i] = &lt_data2[lt_index(i, 0)];

    value = 'A';
    for (int i = 0; i < matrixsize; i++)
    {
        for (int j = 0; j <= i; j++)
            lt_matrix2[i][j] = value++;
    }

    for (int i = 0; i < matrixsize; i++)
    {
        int j;
        for (j = 0; j <= i; j++)
            printf("%-3c", lt_matrix2[i][j]);
        for (; j < matrixsize; j++)
            printf("%-3c", '-');
        putchar('\n');
    }

    free(lt_data2);
    free(lt_matrix2);

    /* Technique 3 */
    void *lt_data3 = malloc(matrixsize * sizeof(int *) + matrixsize * (matrixsize + 1) / 2 * sizeof(int));
    int **lt_matrix3 = lt_data3;
    int *lt_base3 = (int *)((char *)lt_data3 + matrixsize * sizeof(int *));
    assert(lt_matrix2 != 0);
    for (int i = 0; i < matrixsize; i++)
        lt_matrix3[i] = &lt_base3[lt_index(i, 0)];

    value = 1;
    for (int i = 0; i < matrixsize; i++)
    {
        for (int j = 0; j <= i; j++)
            lt_matrix3[i][j] = value++;
    }

    for (int i = 0; i < matrixsize; i++)
    {
        int j;
        for (j = 0; j <= i; j++)
            printf("%-3d", lt_matrix3[i][j]);
        for (; j < matrixsize; j++)
            printf("%-3c", '-');
        putchar('\n');
    }

    free(lt_data3);

    return 0;
}

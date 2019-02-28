/* SO 4885-6272 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/* Should be declared in a header for use in other files */
extern void ***malloc3D(size_t planes, size_t rows, size_t cols, size_t sizeOfType);
extern void free3D(void ****matrix);

void ***malloc3D(size_t planes, size_t rows, size_t cols, size_t sizeOfType)
{
    void   *level3 = malloc(sizeOfType * planes * rows * cols);
    void  **level2 = malloc(sizeof(void *) * planes * rows);
    void ***level1 = malloc(sizeof(void **) * planes);
    //printf("planes = %zu; rows = %zu; cols = %zu; ", planes, rows, cols);
    //printf("level1 = 0x%.12" PRIXPTR "; level2 = 0x%.12" PRIXPTR "; level3 = 0x%.12" PRIXPTR "\n",
    //        (uintptr_t)level1, (uintptr_t)level2, (uintptr_t)level3);
    fflush(stdout);
    if (level3 == NULL || level2 == NULL || level1 == NULL)
    {
        free(level3);
        free(level2);
        free(level1);
        return NULL;
    }
    for (size_t plane = 0; plane < planes; plane++)
    {
        level1[plane] = (void **)((char *)level2 + plane * rows * sizeof(void **));
        //printf("level1[%zu]   = 0x%.12" PRIXPTR "\n", plane, (uintptr_t)level1[plane]);
        for (size_t row = 0; row < rows; ++row)
        {
            level2[plane * rows + row] = (char *)level3 + (plane * rows + row) * cols * sizeOfType;
            //printf("  level2[%zu] = 0x%.12" PRIXPTR "\n",
            //       plane * rows + row, (uintptr_t)level2[plane * rows + row]);
        }
    }
    return level1;
}

void free3D(void ****matrix)
{
    free((*matrix)[0][0]);
    free((*matrix)[0]);
    free((*matrix));
    *matrix = NULL;
}

static void test3D(size_t m3_plns, size_t m3_rows, size_t m3_cols)
{
    printf("planes = %zu; rows = %zu; cols = %zu\n", m3_plns, m3_rows, m3_cols);
    void ***m3 = malloc3D(m3_plns, m3_rows, m3_cols, sizeof(double));
    if (m3 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for 3D array of size %zux%zux%zu doubles\n",
                m3_plns, m3_rows, m3_cols);
        return;
    }

    printf("m3 = 0x%.12" PRIXPTR "; m3[0] = 0x%.12" PRIXPTR "; m3[0][0] = 0x%.12" PRIXPTR "\n",
           (uintptr_t)m3, (uintptr_t)m3[0], (uintptr_t)m3[0][0]);

    for (size_t i = 0; i < m3_plns; i++)
    {
        for (size_t j = 0; j < m3_rows; j++)
        {
            for (size_t k = 0; k < m3_cols; k++)
                ((double *)m3[i][j])[k] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
        }
    }

    for (size_t i = 0; i < m3_plns; i++)
    {
        printf("Plane %zu:\n", i + 1);
        for (size_t j = 0; j < m3_rows; j++)
        {
            for (size_t k = 0; k < m3_cols; k++)
                printf("%4.0f", ((double *)m3[i][j])[k]);
            putchar('\n');
        }
        putchar('\n');
    }

    free3D(&m3);
    printf("m3 = 0x%.16" PRIXPTR "\n", (uintptr_t)m3);
}

int main(void)
{
    test3D(4, 5, 6);
    test3D(3, 4, 10);
    test3D(4, 3, 7);
    test3D(4, 9, 7);
    test3D(30000, 100000, 100000000);  /* 2132 PiB - should fail to allocate on sane systems! */
    return 0;
}

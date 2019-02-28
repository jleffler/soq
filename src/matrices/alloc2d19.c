/* SO 4885-6272 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/* Should be declared in a header for use in other files */
extern void **malloc2D(size_t rows, size_t cols, size_t sizeOfType);
extern void free2D(void ***matrix);

void **malloc2D(size_t rows, size_t cols, size_t sizeOfType)
{
    void *level2 = malloc(sizeOfType * rows * cols);
    void **level1 = malloc(sizeof(void *) * rows);
    if (level2 == NULL || level1 == NULL)
    {
        free(level2);
        free(level1);
        return NULL;
    }
    for (size_t row = 0; row < rows; ++row)
    {
        level1[row] = (char *)level2 + cols * row * sizeOfType;
    }
    return level1;
}

void free2D(void ***matrix)
{
    free((*matrix)[0]);
    free((*matrix));
    *matrix = NULL;
}

static void test2D(size_t m2_rows, size_t m2_cols)
{
    printf("rows = %zu; cols = %zu\n", m2_rows, m2_cols);
    void **m2 = malloc2D(m2_rows, m2_cols, sizeof(double));
    if (m2 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for 2D array of size %zux%zu doubles\n",
                m2_rows, m2_cols);
        return;
    }

    printf("m2 = 0x%.12" PRIXPTR "; m2[0] = 0x%.12" PRIXPTR "\n",
           (uintptr_t)m2, (uintptr_t)m2[0]);

    for (size_t i = 0; i < m2_rows; i++)
    {
        for (size_t j = 0; j < m2_cols; j++)
            ((double *)m2[i])[j] = (i + 1) * 10 + (j + 1);
    }

    for (size_t i = 0; i < m2_rows; i++)
    {
        for (size_t j = 0; j < m2_cols; j++)
            printf("%4.0f", ((double *)m2[i])[j]);
        putchar('\n');
    }

    free2D(&m2);
    printf("m2 = 0x%.16" PRIXPTR "\n", (uintptr_t)m2);
}

int main(void)
{
    test2D(4, 5);
    test2D(10, 3);
    test2D(3, 10);
    test2D(300000000, 1000000000);  /* 2132 PiB - should fail to allocate on sane systems! */
    return 0;
}

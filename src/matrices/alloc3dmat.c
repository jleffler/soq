/* SO 28818521 */
/* Allocate 3D matrix in one big chunk */
#include <stdio.h>
#include <stdlib.h>

typedef double Element;

static Element ***alloc_3d_matrix(size_t imax, size_t jmax, size_t kmax)
{
    size_t i_size = imax * sizeof(Element **);
    size_t j_size = imax * jmax * sizeof(Element *);
    size_t k_size = imax * jmax * kmax * sizeof(Element);

    Element ***matrix = malloc(i_size + j_size + k_size);

    if (matrix == 0)
        return 0;

    printf("i = %zu, j = %zu, k = %zu; sizes: i = %zu, j = %zu, k = %zu; "
           "%zu bytes total\n",
           imax, jmax, kmax, i_size, j_size, k_size, i_size + j_size + k_size);
    printf("matrix          = %p .. %p\n", (void *)matrix,
           (void *)((char *)matrix + i_size + j_size + k_size));

    Element **j_base = (void *)((char *)matrix + imax * sizeof(Element **));
    printf("j_base = %p\n", (void *)j_base);
    for (size_t i = 0; i < imax; i++)
    {
        matrix[i] = &j_base[i * jmax];
        printf("matrix[%zu]       = %p (%p)\n",
               i, (void *)matrix[i], (void *)&matrix[i]);
    }

    Element *k_base = (void *)((char *)j_base + imax * jmax * sizeof(Element *));
    printf("k_base = %p\n", (void *)k_base);
    for (size_t i = 0; i < imax; i++)
    {
        for (size_t j = 0; j < jmax; j++)
        {
            matrix[i][j] = &k_base[(i * jmax + j) * kmax];
            printf("matrix[%zu][%zu]    = %p (%p)\n",
                   i, j, (void *)matrix[i][j], (void *)&matrix[i][j]);
        }
    }

    /* Diagnostic only */
    for (size_t i = 0; i < imax; i++)
    {
        for (size_t j = 0; j < jmax; j++)
        {
            for (size_t k = 0; k < kmax; k++)
                printf("matrix[%zu][%zu][%zu] = %p\n",
                       i, j, k, (void *)&matrix[i][j][k]);
        }
    }

    return matrix;
}

int main(void)
{
    size_t i_max = 3;
    size_t j_max = 4;
    size_t k_max = 5;

    Element ***matrix = alloc_3d_matrix(i_max, j_max, k_max);
    if (matrix == 0)
    {
        fprintf(stderr, "Failed to allocate matrix[%zu][%zu][%zu]\n", i_max, j_max, k_max);
        return 1;
    }

    for (size_t i = 0; i < i_max; i++)
    {
        for (size_t j = 0; j < j_max; j++)
        {
            for (size_t k = 0; k < k_max; k++)
                matrix[i][j][k] = (i + 1) * 100 + (j + 1) * 10 + k + 1;
        }
    }

    for (size_t i = 0; i < i_max; i++)
    {
        for (size_t j = 0; j < j_max; j++)
        {
            for (size_t k = k_max; k > 0; k--)
                printf("[%zu][%zu][%zu] = %6.0f\n", i, j, k-1, matrix[i][j][k-1]);
        }
    }

    free(matrix);
    return 0;
}

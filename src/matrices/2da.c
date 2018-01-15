/* SO 2635-0717 - calloc for an array of array with negative index */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "stderr.h"

typedef struct Matrix
{
    int  *map_base;
    int **map_rows;
    int   x_dim;
    int   y_dim;
    int   extra;
    int **map;
} Matrix;

int main(void)
{
    Matrix m;
    int x_dim = 8;
    int y_dim = 6;
    int extra = 3;

    /* Allocation */
    m.extra = extra;
    m.x_dim = x_dim;
    m.y_dim = y_dim;
    int x_cells = x_dim + 2 * extra;
    int y_cells = y_dim + 2 * extra;
    m.map_base = calloc(x_cells * y_cells, sizeof(**m.map));
    if (m.map_base == 0)
        err_syserr("Failed to allocate %zu bytes memory\n",
                   x_cells * y_cells * sizeof(**m.map));
    m.map_rows = calloc(x_cells, sizeof(*m.map));
    if (m.map_rows == 0)
        err_syserr("Failed to allocate %zu bytes memory\n",
                   x_cells * sizeof(*m.map));
    //printf("Map base: 0x%.8" PRIXPTR "\n", (uintptr_t)m.map_base);
    //printf("Map rows: 0x%.8" PRIXPTR "\n", (uintptr_t)m.map_rows);
    for (int i = 0; i < x_cells; i++)
    {
        m.map_rows[i] = &m.map_base[i * y_cells + extra];
        //printf("Row[%2d]   0x%.8" PRIXPTR "\n", i, (uintptr_t)m.map_rows[i]);
    }
    m.map = &m.map_rows[extra];

    int **map = m.map;
    //printf("Map:      0x%.8" PRIXPTR "\n", (uintptr_t)map);

    /* Initialization */
    int x_min = -extra;
    int y_min = -extra;
    int x_max = x_dim + extra;
    int y_max = y_dim + extra;
    printf("Initialization:\n");
    for (int i = x_min; i < x_max; i++)
    {
        printf("R%2d:", i);
        for (int j = y_min; j < y_max; j++)
        {
            map[i][j] = i * 100 + j;
            printf(" [%2d] = %4d", j, map[i][j]);
        }
        putchar('\n');
    }

    printf("User view:\n");
    for (int i = 0; i < x_dim; i++)
    {
        printf("R%2d:", i);
        for (int j = 0; j < y_dim; j++)
        {
            printf(" [%2d] = %4d", j, map[i][j]);
        }
        putchar('\n');
    }

    printf("Library view:\n");
    for (int i = x_min; i < x_max; i++)
    {
        printf("R%2d:", i);
        for (int j = y_min; j < y_max; j++)
        {
            printf(" [%2d] = %4d", j, map[i][j]);
        }
        putchar('\n');
    }

    /* Deallocation */
    free(m.map_base);
    free(m.map_rows);

    return 0;
}

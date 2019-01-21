/* SO 5428-2732 */

#include <stdio.h>
#include <stdlib.h>

/*
int* array = malloc(n * m * sizeof(int));
//want to convert array into M[n][m]

what I am doing now:

int** M = malloc(n * sizeof(int*));
for(int i = 0; i < n; i++, array += m)
  M[i] = array;
*/

static void print_2dvla(int rows, int cols, int data[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        printf("%2d: ", i);
        for (int j = 0; j < cols; j++)
            printf(" %4d", data[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    int m = 10;
    int n = 12;

    int (*M)[m] = malloc(n * m * sizeof(M[0][0]));
    if (M == NULL)
    {
        fprintf(stderr, "Failed to allocate %zu bytes memory\n", n * m * sizeof(M[0][0]));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            M[i][j] = (i + 1) * 100 + (j + 1);
    }

    print_2dvla(n, m, M);

    free(M);
    return 0;
}

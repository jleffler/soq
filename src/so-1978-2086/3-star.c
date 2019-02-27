/*
** https://stackoverflow.com/questions/19782086
** Allocating memory dynamically to a 2D array of strings
**
** The 3-star solution.
*/
#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char ***ReadNames(int *r, int *c)
{
    int i, j;
    char name[100];
    printf("Number of Rows: ");
    if (scanf("%d", r) != 1)
        return 0;

    printf("Number of Columns: ");
    if (scanf("%d", c) != 1)
        return 0;

    int x;
    while ((x = getchar()) != EOF && x != '\n')
        ;

    char ***Names = (char ***)malloc(sizeof(char ***)*(*r));
    for (i = 0; i < (*r); i++)
        Names[i] = (char **)malloc(sizeof(char **)*(*c));
    for (i = 0; i < (*r); i++)
    {
        for (j = 0; j < (*c); j++)
        {
            if (fgets(name, sizeof(name), stdin) == 0)
            {
                fprintf(stderr, "Unexpected EOF\n");
                exit(1);
            }
            name[strlen(name)-1] = '\0';
            Names[i][j] = strdup(name);
        }
    }
    return Names;
}

static void PrintNames(char ***Names, int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
            printf("%s ", Names[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int rows;
    int cols;
    char ***data = ReadNames(&rows, &cols);

    if (data != 0)
    {
        PrintNames(data, rows, cols);

        printf("Rows = %d, cols = %d.\n", rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                printf("[%d,%d] = <<%s>>\n", i, j, data[i][j]);
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                free(data[i][j]);
            free(data[i]);
        }
        free(data);
    }

    return 0;
}


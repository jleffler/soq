/*
** https://stackoverflow.com/questions/19782086
** Allocating memory dynamically to a 2D array of strings
**
** The 4-star solution.
*/
#include "posixver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void ReadNames(char ****Names, int *rows, int *cols)
{
    char name[100];
    printf("Number of Rows: ");
    if (scanf("%d", rows) != 1)
    {
        *Names = 0;
        return;
    }

    printf("Number of Columns: ");
    if (scanf("%d", cols) != 1)
    {
        *Names = 0;
        return;
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n')
        ;

    *Names = (char ***)malloc(sizeof(char ***) * (*rows));
    for (int i = 0; i < (*rows); i++)
        (*Names)[i] = (char **)malloc(sizeof(char **) * (*cols));

    for (int i = 0; i < (*rows); i++)
    {
        for (int j = 0; j < (*cols); j++)
        {
            printf("R%dC%d: ", i, j);
            if (fgets(name, sizeof(name), stdin) == 0)
            {
                fprintf(stderr, "Unexpected EOF\n");
                exit(1);
            }
            name[strlen(name) - 1] = '\0';    // Zap newline
            (*Names)[i][j] = strdup(name);
        }
    }
}

int main(void)
{
    int rows;
    int cols;
    char ***data = 0;

    ReadNames(&data, &rows, &cols);
    if (data != 0)
    {
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

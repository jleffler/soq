#include "AVL_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    time_t t;
    srand(time(&t));
    struct vertex *root = NULL;
    int i, j, limit = 1000000, incretment = 500000;
    printf("starting insert %d elements with increment %d in next round\n", limit, incretment);
    for (j = 0; j <= 100; j++)
    {
        clock_t start, end;
        start = clock();
        for (i = 0; i < limit; i++)
        {
            int random = rand() % 10;
            printf("inserting %d\n", random);
            insert(&root, random);
        }
        end = clock();
        double total = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%f\n", total);
        clear_tree(&root);
    }
}

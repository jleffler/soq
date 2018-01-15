/* SO 3495-9596 */
#include "AVL_tree.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    long sample[] = { 6, 2, 3 };
    enum { SIZE = sizeof(sample) / sizeof(sample[0]) };
    enum { N_REPS = 3 };

    for (int i = 0; i < SIZE; i++)
    {
        for (int k = 0; k < N_REPS; k++)
        {
            printf("Starting cycle %d.%d\n", i, k);
            struct vertex *root = NULL;
            for (int j = 0; j <= i; j++)
                insert(&root, sample[j]);
            printf("Cleaning cycle %d.%d\n", i, k);
            clear_tree(&root);
            assert(root == NULL);
            printf("Finished cycle %d.%d\n", i, k);
        }
    }

    return(0);
}

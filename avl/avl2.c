#include "AVL_tree.h"
#include <stdio.h>

int main(void)
{
    struct vertex *root = NULL;
    long sample[] = { 6, 2, 3 };
    enum { SIZE = sizeof(sample) / sizeof(sample[0]) };

    for (int j = 0; j < SIZE; j++)
    {
        insert(&root, sample[j]);
    }

    clear_tree(&root);
    return(0);
}

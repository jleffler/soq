#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct BST BST;
struct BST
{
    int  data;
    BST *left;
    BST *right;
};

static int roottoleaf(const BST *tree, int target)
{
    if (tree == 0)
        return 0;
    if (tree->left == 0 && tree->right == 0)
        return(tree->data == target);
    if (tree->data > target)
        return 0;
    if (roottoleaf(tree->left, target - tree->data))
        return 1;
    if (roottoleaf(tree->right, target - tree->data))
        return 1;
    return 0;
}

static int pathtoleaf(const BST *tree, int target)
{
    if (tree == 0)
        return 0;
    if (roottoleaf(tree, target))
        return 1;
    else if (pathtoleaf(tree->left, target))
        return 1;
    else if (pathtoleaf(tree->right, target))
        return 1;
    else
        return 0;
}

static void printtoleaf(const BST *tree)
{
    if (tree == 0)
        return;
//    printf("<<%.2d : 0x%.8" PRIXPTR " : 0x%.8" PRIXPTR " : 0x%.8" PRIXPTR ">>\n",
//           tree->data, (uintptr_t)tree, (uintptr_t)tree->left, (uintptr_t)tree->right);
    putchar('(');
    if (tree->left)
        printtoleaf(tree->left);
    printf("[%d]", tree->data);
    if (tree->right)
        printtoleaf(tree->right);
    putchar(')');
}

static void printtree(const char *tag, const BST *tree)
{
    printf("%s\n", tag);
    printtoleaf(tree);
    putchar('\n');
}

int main(void)
{
    BST tree[8] =
    {
        [0] = {  1,   &tree[1],  &tree[2]   },
        [1] = {  2,   &tree[3],  &tree[4]   },
        [2] = {  3,   &tree[5],  &tree[6]   },
        [3] = {  5,          0,         0   },
        [4] = { 10,          0,         0   },
        [5] = {  4,          0,         0   },
        [6] = { 20,          0,  &tree[7]   },
        [7] = {  2,          0,         0   },
    };

    printtree("Tree", tree);
    for (int i = 1; i < 30; i++)
        printf("Target: %.2d = %d\n", i, pathtoleaf(tree, i));
    return 0;
}

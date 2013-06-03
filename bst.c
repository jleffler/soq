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
    if (tree->left == 0 && tree->right == 0)
        return(tree->data == target);
    if (roottoleaf(tree, target))
        return 1;
    if (pathtoleaf(tree->left, target))
        return 1;
    if (pathtoleaf(tree->right, target))
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
    printf("%s: ", tag);
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

    static const int paths[] =
    {
         [0] = 0,  [1] = 0,  [2] = 1,  [3] = 0,  [4] = 1,
         [5] = 1,  [6] = 0,  [7] = 1,  [8] = 1,  [9] = 0,
        [10] = 1, [11] = 0, [12] = 1, [13] = 1, [14] = 0,
        [15] = 0, [16] = 0, [17] = 0, [18] = 0, [19] = 0,
        [20] = 0, [21] = 0, [22] = 1, [23] = 0, [24] = 0,
        [25] = 1, [26] = 1, [27] = 0, [28] = 0, [29] = 0,
    };

    printtree("Tree", tree);
    int fail = 0;
    for (int i = 1; i < 30; i++)
    {
        int result = pathtoleaf(tree, i);
        const char *passfail = "PASS";
        if (result != paths[i])
        {
            passfail = "FAIL";
            fail++;
        }
        printf("Target: %.2d = %d %s\n", i, result, passfail);
    }
    printf("%s\n", (fail == 0) ? "== PASS ==" : "!! FAIL !!");

    return(fail != 0);
}

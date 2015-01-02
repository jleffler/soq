/* SO 16759337 */
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

static int pathtoleaf(const BST *tree, int local_target, int overall_target)
{
    if (tree == 0)
        return 0;
    if (tree->left == 0 && tree->right == 0)
        return(tree->data == local_target);
    // Path to leaf starts below this node on left
    if (pathtoleaf(tree->left, overall_target, overall_target))
        return 1;
    // Path to leaf starts below this node on right
    if (pathtoleaf(tree->right, overall_target, overall_target))
        return 1;
    // Is there a path including this node?
    if (tree->data > local_target)
        return 0;
    // Path to leaf starts at this node via left
    if (pathtoleaf(tree->left, local_target - tree->data, overall_target))
        return 1;
    // Path to leaf starts at this node via right
    if (pathtoleaf(tree->right, local_target - tree->data, overall_target))
        return 1;
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
        int result = pathtoleaf(tree, i, i);
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

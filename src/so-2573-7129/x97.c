/* SO 25737129 Inorder Predecessor Node in BST */
/*
** See (1):  http://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/
** Also (2): http://exceptional-code.blogspot.co.il/2011/08/binary-search-trees-primer.html
**
** From (1):
**
**  You need to find the inorder successor and predecessor of a given
**  key.  In case the given key is not found in BST, then return the two
**  values between which this key will lie.
**
**  Following is the algorithm to reach the desired result.  It's a
**  recursive method:
**
**  Input: root node, key
**  output: predecessor node, successor node
**
**  1. If root is NULL
**        then return
**  2. if key is found then
**        a. If its left subtree is not null
**           Then predecessor will be the right most
**           child of left subtree or left child itself.
**        b. If its right subtree is not null
**           The successor will be the left most child
**           of right subtree or right child itself.
**        return
**  3. If key is smaller than root node
**        set the successor as root
**        search recursively into left subtree
**     else
**        set the predecessor as root
**        search recursively into right subtree
**
** Process predecessor only this time.
*/

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BST BST;
struct BST
{
    int   data;
    BST  *left;
    BST  *right;
};

static BST *rmc_bst(BST *root)
{
    printf("-->> rmc_bst()\n");
    if (root == 0 || root->left == 0)
        return root;
    else
        return rmc_bst(root->right);
}

/*
static BST *lmc_bst(BST *root)
{
    if (root == 0 || root->right == 0)
        return root;
    else
        return rmc_bst(root->left);
}
*/

static BST *inorder_predecessor(BST *root, BST *node)
{
    assert(root != 0);
    assert(node != 0);
    if (root == 0 || node == 0)
        return 0;
    if (node->data == root->data)
    {
        return rmc_bst(root->left);
        /* successor = lmc_bst(root->right); */
    }
    else if (node->data < root->data)
    {
        /* set successor */
        return inorder_predecessor(root->left, node);
    }
    else if (node->data > root->data)
    {
        return root;
        /* set successor */
    }
    assert(0);
    return 0;
}

static void print_inorder(BST *root)
{
    if (root != 0)
    {
        assert(root->left == 0 || root->left->data < root->data);
        assert(root->right == 0 || root->right->data > root->data);
        print_inorder(root->left);
        printf("[0x%.12" PRIXPTR " (L 0x%.12" PRIXPTR ", R 0x%.12" PRIXPTR") = %2d]\n",
               (uintptr_t)root, (uintptr_t)root->left, (uintptr_t)root->right, root->data);
        print_inorder(root->right);
    }
}

int main(void)
{
    /*
    **                   13
    **                   |
    **          +--------+--------+
    **          |                 |
    **          7                 29
    **          |                 |
    **       +--+--+         +----+----+
    **       |     |         |         |
    **       5     11        19        47
    **                       |         |
    **                    +--+         +--+
    **                    |               |
    **                    17              53
    ** P( 5) = undefined
    ** P( 7) =  5
    ** P(11) =  7
    ** P(13) = 11
    ** P(17) = 13
    ** P(19) = 17
    ** P(29) = 19
    ** P(47) = 29
    ** P(53) = 47
    */
    BST bst[] =
    {
        [0] = { 13, &bst[1], &bst[2] },
        [1] = {  7, &bst[3], &bst[4] },
        [2] = { 29, &bst[5], &bst[6] },
        [3] = {  5,       0,       0 },
        [4] = { 11,       0,       0 },
        [5] = { 19, &bst[7],       0 },
        [6] = { 47,       0, &bst[8] },
        [7] = { 17,       0,       0 },
        [8] = { 53,       0,       0 },
    };
    enum { BST_size = sizeof(bst) / sizeof(bst[0]) };

    print_inorder(bst);
    putchar('\n');

    for (int i = 0; i < BST_size; i++)
    {
        BST *r = inorder_predecessor(&bst[0], &bst[i]);
        printf("Predecessor of %d (%2d) is ", i, bst[i].data);
        if (r == 0)
            printf("%s\n", "undefined");
        else
            printf("%td (%2d)\n", (r - bst), r->data);
    }

    return 0;
}

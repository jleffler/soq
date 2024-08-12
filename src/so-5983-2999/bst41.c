/* SO 5983-2999 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "stderr.h"

typedef struct Tree
{
    int key;
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef void (*Printer)(const Tree *node);

static void bst_print_k_smallest(Tree *tree, int k, int *count, Printer print)
{
    if (tree->left != 0)
        bst_print_k_smallest(tree->left, k, count, print);
    if (*count < k)
    {
        (*count)++;
        print(tree);
    }
    if (*count < k && tree->right != 0)
        bst_print_k_smallest(tree->right, k, count, print);
}

static void bst_print_node(const Tree *node)
{
    if (node != 0)
    {
        printf("Node: 0x%.12" PRIXPTR " - key %3d; left = 0x%.12" PRIXPTR
               ", right = 0x%.12" PRIXPTR "\n",
               (uintptr_t)node, node->key, (uintptr_t)node->left,
               (uintptr_t)node->right);
    }
}

static Tree *bst_newnode(int key)
{
    Tree *node = malloc(sizeof(*node));
    if (node == 0)
        err_syserr("failed to allocate %zu bytes of memory: ", sizeof(*node));
    node->key = key;
    node->left = node->right = 0;
    return node;
}

static Tree *bst_insert(Tree *root, int key)
{
    if (root == NULL)
        root = bst_newnode(key);
    else if (key < root->key)
        root->left = bst_insert(root->left, key);
    else if (key > root->key)
        root->right = bst_insert(root->right, key);
    /* else Repeat - ignore */
    return root;
}

static void bst_free(Tree *tree)
{
    if (tree != 0)
    {
        bst_free(tree->left);
        bst_free(tree->right);
        free(tree);
    }
}

int main(int argc, char **argv)
{
    if (argc > 0)
        err_setarg0(argv[0]);

    Tree *root = NULL;
    root = bst_insert(root,  8);
    root = bst_insert(root,  3);
    root = bst_insert(root, 10);
    root = bst_insert(root,  1);
    root = bst_insert(root,  6);
    root = bst_insert(root, 14);
    root = bst_insert(root,  4);
    root = bst_insert(root,  7);
    root = bst_insert(root, 13);

    int count = 0;
    bst_print_k_smallest(root, 9, &count, bst_print_node);

    bst_free(root);

    return 0;
}

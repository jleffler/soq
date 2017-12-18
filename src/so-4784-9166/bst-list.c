/* SO 4784-9166 */
#include <inttypes.h>
#include <stdio.h>

typedef struct Node Node;
struct Node
{
    int   number;
    Node *left;
    Node *right;
};

static Node *convertToPreOrder(Node *root)
{
    if (root == 0)
        return 0;
    Node *l_list = convertToPreOrder(root->left);
    Node *r_list = convertToPreOrder(root->right);
    root->left = 0;
    /* Add left list */
    root->right = l_list;
    if (l_list != 0)
        l_list->left = root;
    /* Find the end */
    Node **pos = &root;
    while ((*pos)->right != 0)
        pos = &(*pos)->right;
    /* Add right list */
    (*pos)->right = r_list;
    if (r_list != 0)
        r_list->left = *pos;
    return root;
}

static void print_node(Node *node)
{
    if (node != 0)
        printf("Node = 0x%.12" PRIXPTR " - Number = %d - "
               "Left = 0x%.12" PRIXPTR " - Right = 0x%.12" PRIXPTR "\n",
               (uintptr_t)node, node->number, (uintptr_t)node->left, (uintptr_t)node->right);
}

static void print_BST_preorder(Node *root)
{
    if (root == 0)
        return;
    print_node(root);
    print_BST_preorder(root->left);
    print_BST_preorder(root->right);
}

static void print_list(Node *list)
{
    while (list != 0)
    {
        print_node(list);
        list = list->right;
    }
}

static Node *add_bst_node(Node *root, Node *node)
{
    if (root == 0)
        return node;
    if (node->number >= root->number)
        root->right = add_bst_node(root->right, node);
    else
        root->left = add_bst_node(root->left, node);
    return root;
}

static void test_bst_to_list(size_t n_nodes, Node nodes[])
{
    Node *root = 0;
    for (size_t i = 0; i < n_nodes; i++)
        root = add_bst_node(root, &nodes[i]);
    printf("Print BST in pre-order:\n");
    print_BST_preorder(root);
    printf("Convert to list\n");
    Node *list = convertToPreOrder(root);
    printf("Print list:\n");
    print_list(list);
    putchar('\n');
}

int main(void)
{
    Node array1[] =
    {
        { 4, 0, 0 },
        { 2, 0, 0 },
        { 1, 0, 0 },
        { 3, 0, 0 },
        { 6, 0, 0 },
        { 5, 0, 0 },
        { 7, 0, 0 },
    };
    enum { ARRAY1_SIZE = sizeof(array1) / sizeof(array1[0]) };
    test_bst_to_list(ARRAY1_SIZE, array1);

    Node array2[] =
    {
        { 19, 0, 0 },
        { 21, 0, 0 },
        { 20, 0, 0 },
        { 18, 0, 0 },
        { 22, 0, 0 },
        { 24, 0, 0 },
        { 17, 0, 0 },
        { 16, 0, 0 },
        { 23, 0, 0 },
        { 27, 0, 0 },
        { 26, 0, 0 },
        { 25, 0, 0 },
    };
    enum { ARRAY2_SIZE = sizeof(array2) / sizeof(array2[0]) };
    test_bst_to_list(ARRAY2_SIZE, array2);

    Node array3[] =
    {
        { 16, 0, 0 },
        { 11, 0, 0 },
        { 21, 0, 0 },
        { 10, 0, 0 },
        { 22, 0, 0 },
        { 22, 0, 0 },
        { 21, 0, 0 },
        { 27, 0, 0 },
        { 27, 0, 0 },
        { 20, 0, 0 },
        { 22, 0, 0 },
        { 17, 0, 0 },
        { 12, 0, 0 },
    };
    enum { ARRAY3_SIZE = sizeof(array3) / sizeof(array3[0]) };
    test_bst_to_list(ARRAY3_SIZE, array3);

    return 0;
}


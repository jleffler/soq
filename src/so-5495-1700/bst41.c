/* SO 7400-0791 - recursive function numberOfLeaves() */
/* Adapted from code for SO 5495-1700 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

static Node *createNode(int value);
static void freeSubtree(Node *node);
static Node *insertNode(Node *root, int value);
static int numberOfLeaves(Node *N);

int numberOfLeaves(Node *N)
{
    if (N == NULL)
        return 0;  /* This isn't a real node */
    if (N->left == NULL && N->right == NULL)
        return 1;  /* This is a leaf node */
    return numberOfLeaves(N->left) + numberOfLeaves(N->right);
}

Node *insertNode(Node *root, int value)
{
    if (root == NULL)
        root = createNode(value);
    else if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    return root;
}

void freeSubtree(Node *N)
{
    if (N == NULL)
        return;
    freeSubtree(N->right);
    freeSubtree(N->left);
    N->right = NULL;
    N->left = NULL;
    free(N);
}

Node *createNode(int value)
{
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

static void printValueIndented(int level, int value)
{
    for (int i = 0; i < level; i++)
        fputs("    ", stdout);
    printf("%d\n", value);
}

static void printTree(const char *tag, Node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 0 && tag != NULL)
        printf("%s\n", tag);
    printValueIndented(level, root->data);
    printTree(tag, root->left, level + 1);
    printTree(tag, root->right, level + 1);
}

int main(void)
{
    Node *root = 0;
    printf("Sequence:\n");
    for (int i = 0; i < 20; i++)
    {
        int value = i;
        root = insertNode(root, i);
        printf("%2d: Inserted %2d - Number of leaf nodes: %d\n",
               i, value, numberOfLeaves(root));
    }
    printTree("Sequence", root, 0);
    freeSubtree(root);

    printf("Random:\n");
    srand(time(0));
    root = 0;
    for (int i = 0; i < 20; i++)
    {
        int value = rand() % 53;
        root = insertNode(root, value);
        printf("%2d: Inserted %2d - Number of leaf nodes: %d\n",
               i, value, numberOfLeaves(root));
    }
    printTree("Random", root, 0);
    freeSubtree(root);

    printf("Computed:\n");
    root = 0;
    for (int i = 0; i < 20; i++)
    {
        int value = (13 * i + 7) % 47;
        root = insertNode(root, value);
        printf("%2d: Inserted %2d - Number of leaf nodes: %d\n",
               i, value, numberOfLeaves(root));
    }
    printTree("Computed", root, 0);
    freeSubtree(root);

    return 0;
}

/* SO 5495-1700 */
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
    srand(time(0));
    for (int i = 0; i < 20; i++)
        root = insertNode(root, i);
    printTree("Sequence", root, 0);
    freeSubtree(root);
    root = 0;
    for (int i = 0; i < 20; i++)
        root = insertNode(root, rand() % 53);
    printTree("Random", root, 0);
    freeSubtree(root);
    root = 0;
    for (int i = 0; i < 20; i++)
        root = insertNode(root, (13 * i + 7) % 47);
    printTree("Computed", root, 0);
    freeSubtree(root);
    return 0;
}

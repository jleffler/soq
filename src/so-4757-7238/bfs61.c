/* SO 4757-7238 */
/* UNSAFE: does not handle wraparound in the queue */
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *left;
    int ID;
    int Grade;
    struct node *right;
};

struct BfsNode
{
    struct node *parent;
    struct node *child;
    char side[4];           /* "L" or "R" plus padding */
    int level;
};

struct node *newNode(int, int);
struct node *insertNode(struct node *node, int id, int grade);
void printTree(struct node *node);
void printParent(struct node *);

int main(int argc, char **argv)
{
    const char *name = "input.txt";
    if (argc == 2)
        name = argv[1];
    struct node *head = NULL;
    FILE *file = fopen(name, "r");
    if (file == 0)
    {
        fprintf(stderr, "%s: failed to open file %s for reading\n", argv[0], name);
        return 1;
    }
    printf("File: %s\n", name);
    int stdID, grade;
    while (fscanf(file, "%d %d", &stdID, &grade) == 2)
    {
        if (stdID == -1 && grade == -1)
            break;
        printf("Read: %d %d\n", stdID, grade);
        head = insertNode(head, stdID, grade);
        //printf("Tree:\n");
        //printTree(head);
    }
    fclose(file);

    printf("Completed tree:\n");
    printTree(head);
    printf("\n");

    printf("%3d %3d\n", head->ID, head->Grade);
    printf("Parent tree:\n");
    printParent(head);
    printf("\n");

    return 0;
}

struct node *newNode(int id, int grade)
{
    struct node *newnode = malloc(sizeof(struct node));
    newnode->ID = id;
    newnode->Grade = grade;
    newnode->left = newnode->right = NULL;
    return newnode;
}

struct node *insertNode(struct node *node, int id, int grade)
{
    if (node == NULL)
        return newNode(id, grade);
    if (grade < node->Grade)
        node->left = insertNode(node->left, id, grade);
    else if (grade >= node->Grade)
        node->right = insertNode(node->right, id, grade);
    return node;
}

void printTree(struct node *node)
{
    if (node == NULL)
        return;
    printTree(node->left);
    printf("%3d %3d (0x%.12" PRIXPTR ": 0x%.12" PRIXPTR " - 0x%.12" PRIXPTR ")\n",
           node->ID, node->Grade,
           (uintptr_t)node, (uintptr_t)node->left, (uintptr_t)node->right);
    printTree(node->right);
}

void printParent(struct node *node)
{
    if (node == 0)
    {
        printf("Empty tree\n");
        return;
    }

    enum { MAX_QUEUE_SIZE = 100 };
    struct BfsNode q[MAX_QUEUE_SIZE];
    size_t q_head = 0;
    size_t q_tail = 0;
    int level = 0;

    if (node->left)
        q[q_head++] = (struct BfsNode){node, node->left, "L", level + 1};
    if (node->right)
        q[q_head++] = (struct BfsNode){node, node->right, "R", level + 1};
    printf("Level %d: %3d %3d", level, node->ID, node->Grade);

    while (q_tail != q_head)
    {
        struct BfsNode *data = &q[q_tail++];
        if (data->level != level)
        {
            assert(data->level == level + 1);
            putchar('\n');
            level = data->level;
            printf("Level %d:", level);
        }
        struct node *child = data->child;
        if (child->left)
            q[q_head++] = (struct BfsNode){child, child->left, "L", level + 1};
        if (child->right)
            q[q_head++] = (struct BfsNode){child, child->right, "R", level + 1};
        //printf(" %3d %3d (%3d %s)", child->ID, child->Grade, data->parent->ID, data->side);
        printf(" %3d %3d (%3d %s)", child->ID, child->Grade, data->parent->Grade, data->side);
    }
    putchar('\n');
}

/* SO 4757-7238 */
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

/* Structures to manage BFS - breadth-first search */

struct bfs_node
{
    struct node *parent;
    struct node *child;
    char side[4];           /* "L" or "R" plus padding */
    int level;
};

enum { MAX_QUEUE_SIZE = 100 };
struct bfs_queue
{
    struct bfs_node q[MAX_QUEUE_SIZE];
    size_t q_head;
    size_t q_tail;
};

static void bfs_add(struct bfs_queue *q, struct node *parent, struct node *child, int level, char side)
{
    assert(q != 0 && parent != 0 && child != 0);
    assert(parent->left == child || parent->right == child);
    assert(side == 'L' || side == 'R');
    assert(q->q_head < MAX_QUEUE_SIZE && q->q_tail < MAX_QUEUE_SIZE);
    size_t next = (q->q_head + 1) % MAX_QUEUE_SIZE;
    if (next == q->q_tail)
    {
        fprintf(stderr, "Queue is full\n");
        exit(EXIT_FAILURE);
    }
    q->q[q->q_head] = (struct bfs_node){ .parent = parent, .child = child,
                                         .level = level, .side = { side, '\0' } };
    q->q_head = next;
}

static inline void bfs_init(struct bfs_queue *q)
{
    assert(q != 0);
    q->q_head = q->q_tail = 0;
}

static inline int bfs_empty(const struct bfs_queue *q)
{
    assert(q != 0);
    return (q->q_head == q->q_tail);
}

static struct bfs_node *bfs_remove(struct bfs_queue *q)
{
    if (q->q_tail == q->q_head)
    {
        fprintf(stderr, "cannot remove anything from an empty queue\n");
        exit(EXIT_FAILURE);
    }
    assert(q->q_head < MAX_QUEUE_SIZE && q->q_tail < MAX_QUEUE_SIZE);
    size_t curr = q->q_tail;
    q->q_tail = (q->q_tail + 1) % MAX_QUEUE_SIZE;
    return &q->q[curr];
}

void printParent(struct node *node)
{
    if (node == 0)
    {
        printf("Empty tree\n");
        return;
    }

    int level = 0;
    struct bfs_queue q;
    bfs_init(&q);

    if (node->left)
        bfs_add(&q, node, node->left, level + 1, 'L');
    if (node->right)
        bfs_add(&q, node, node->right, level + 1, 'R');

    printf("Level %d: %3d %3d", level, node->ID, node->Grade);

    while (!bfs_empty(&q))
    {
        struct bfs_node *data = bfs_remove(&q);
        assert(data != 0);
        if (data->level != level)
        {
            assert(data->level == level + 1);
            putchar('\n');
            level = data->level;
            printf("Level %d:", level);
        }
        struct node *child = data->child;
        assert(child != 0);
        if (child->left)
            bfs_add(&q, child, child->left, level + 1, 'L');
        if (child->right)
            bfs_add(&q, child, child->right, level + 1, 'R');
        //printf(" %3d %3d (%3d %s)", child->ID, child->Grade, data->parent->ID, data->side);
        printf(" %3d %3d (%3d %s)", child->ID, child->Grade, data->parent->Grade, data->side);
    }
    putchar('\n');
}

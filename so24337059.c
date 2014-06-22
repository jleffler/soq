/* SO 24337059: A very specific tree traversal method */

#include <stdio.h>

enum { MAX_CHILD = 2 };
enum { UP = 1, DOWN = 2 };
typedef struct Node Node;

struct Node
{
    char    name[8];
    int     number;
    Node   *parent;
    Node   *child[MAX_CHILD];
};

static Node data[] =
{
    { "A",     0,        0, { &data[ 1], &data[ 2], }, },
    { "AA",   -3, &data[0], { &data[ 3], &data[ 4], }, },
    { "AB",   +3, &data[0], { &data[ 5], &data[ 6], }, },
    { "AAA",  -4, &data[1], { &data[ 7], &data[ 8], }, },
    { "AAB",  +4, &data[1], { &data[ 9], &data[10], }, },
    { "ABA",  -4, &data[2], { &data[11], &data[12], }, },
    { "ABB",  +4, &data[2], { &data[13], &data[14], }, },
    { "AAAA",  0, &data[3], {         0,         0, }, },
    { "AAAB", +5, &data[3], {         0,         0, }, },
    { "AABA", -5, &data[4], {         0,         0, }, },
    { "AABB", +5, &data[4], {         0,         0, }, },
    { "ABAA", -5, &data[5], {         0,         0, }, },
    { "ABAB", +5, &data[5], {         0,         0, }, },
    { "ABBA", -5, &data[6], {         0,         0, }, },
    { "ABBB", +5, &data[6], {         0,         0, }, },
};
enum { NUM_NODES = sizeof(data) / sizeof(data[0]) };

static void visit(Node *node, int up_down)
{
    printf("%4s: ", up_down == UP ? "UP" : "DOWN");
    printf(" %5s [%2d] N = %p; P = %p\n", node->name, node->number,
            (void *)node, (void *)node->parent);
}

static void print_tree(Node *node)
{
    if (node != 0)
    {
        visit(node, DOWN);
        for (int i = 0; i < MAX_CHILD; i++)
            print_tree(node->child[i]);
    }
}

static void print_preorder(const char *tag, Node *node)
{
    printf("Tree starting from %s:\n", tag);
    print_tree(node);
}

static void dfs_traverse(int up_down, Node *node, Node *skip)
{
    if (node != 0 && node != skip)
    {
        visit(node, up_down);
        for (int i = 0; i < MAX_CHILD; i++)
            dfs_traverse(DOWN, node->child[i], skip);
        if (node->parent != 0 && up_down == UP)
            dfs_traverse(UP, node->parent, node);
    }
}

static void dfs_traversal(const char *tag, int up_down, Node *node, Node *skip)
{
    printf("DFS starting from %s\n", tag);
    dfs_traverse(up_down, node, skip);
}

int main(void)
{
    Node *aaa = &data[3];
    Node *root = &data[0];

    print_preorder("root", root);
    print_preorder("aaa",  aaa);

    dfs_traversal("aaa",  UP, aaa,  0);
    dfs_traversal("root", UP, root, 0);

    for (int i = 0; i < NUM_NODES; i++)
        dfs_traversal(data[i].name, UP, &data[i], 0);

    return 0;
}

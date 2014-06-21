/* SO 24337059: A very specific tree traversal method */

#include <stdio.h>

typedef struct Node Node;

struct Node
{
    char    name[10];
    Node   *parent;
    Node   *sibling;
    Node   *child;
    int     number;
};

static Node data[] =
{
    { "A",    0,                0, &data[ 1],  0 },
    { "AA",   &data[0], &data[ 2], &data[ 3], -3 },
    { "AB",   &data[0],         0, &data[ 5], +3 },
    { "AAA",  &data[1], &data[ 4], &data[ 7], -4 },
    { "AAB",  &data[1],         0, &data[ 9], +4 },
    { "ABA",  &data[2], &data[ 6], &data[11], -4 },
    { "ABB",  &data[2],         0, &data[13], +4 },
    { "AAAA", &data[3], &data[ 8],         0, -5 },
    { "AAAB", &data[3],         0,         0, +5 },
    { "AABA", &data[4], &data[10],         0, -5 },
    { "AABB", &data[4],         0,         0, +5 },
    { "ABAA", &data[5], &data[12],         0, -5 },
    { "ABAB", &data[5],         0,         0, +5 },
    { "ABBA", &data[6], &data[14],         0, -5 },
    { "ABBB", &data[6],         0,         0, +5 },
};
enum { NUM_NODES = sizeof(data) / sizeof(data[0]) };

static void print_tree(const char *tag, int level, Node *node)
{
    if (node != 0)
    {
        if (level == 0)
            printf("Tree starting from %s:\n", tag);
        for (int i = 0; i < level; i++)
            printf("  ");
        printf(" %s [%2d] N = %p; P = %p\n", node->name, node->number,
               (void *)node, (void *)node->parent);
        print_tree(tag, level+1, node->child);
        if (level != 0)
            print_tree(tag, level, node->sibling);
    }
}

static void dfs_traversal(const char *tag, int level, Node *node, Node *skip);

static void dfs_traverse(int level, Node *node, Node *skip)
{
    if (node != 0)
    {
        for (int i = 0; i < level; i++)
            printf("  ");
        if (node != skip)
        {
            printf(" %s [%2d] L = %d\n", node->name, node->number, level);
            dfs_traverse(level + 1, node->child, 0);
        }
        dfs_traversal("Sibling", level, node->sibling, skip);
        if (node->parent != 0)
            dfs_traversal("Going up", level - 1, node->parent, node);
    }
}

static void dfs_traversal(const char *tag, int level, Node *node, Node *skip)
{
    printf("DFS starting from %s\n", tag);
    dfs_traverse(level, node, skip);
}

int main(void)
{
    Node *aaa = &data[3];
    Node *root = &data[0];

    print_tree("root", 0, root);
    print_tree("aaa",  0, aaa);

    dfs_traversal("aaa",  0, aaa,  0);
    dfs_traversal("root", 0, root, 0);

    for (int i = 0; i < NUM_NODES; i++)
        dfs_traversal(data[i].name, 0, &data[i], 0);
}

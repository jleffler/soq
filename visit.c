#include <stdio.h>

static int visited[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct Node
{
    int node;
    struct Node *prev;
};

static void visit(int node, struct Node *prev_node, int size, int const edges[size][size], int end)
{
    struct Node n = { node, prev_node };
    struct Node *p = &n;

    printf("-->> %s\n", __func__);
    if (node == end)
        printf("Solution: ");
    do
        printf("%d%s", p->node + 1, (p->prev != NULL) ?  "->" : "\n");
    while ((p = p->prev) != NULL);

    visited[node] = 1;
    for (int i = 0; i < size; ++i)
    {
        if ((visited[i] == 0) && (edges[node][i] == 1))
        {
            if (node == end)
                printf("Continuing\n");
            visit(i, &n, size, edges, end);
        }
    }
    visited[node] = 0;
    printf("<<-- %s\n", __func__);
}

static void chk_symmetry(int size, int const edges[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (edges[i][j] != edges[j][i])
                printf("E[%d,%d] = %d, E[%d,%d] = %d\n", i, j, edges[i][j], j, i, edges[j][i]);
        }
    }
}

static void prt_links(int size, int const edges[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (edges[i][j])
                printf("%d -> %d\n", i+1, j+1);
        }
    }
}

int main(void)
{
    int const edges[12][12] =
    {
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };

    chk_symmetry(12, edges);
    prt_links(12, edges);
    visit(0, NULL, 12, edges, 11);
    return 0;
}


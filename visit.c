#include <stdio.h>

static int const edges[12][12] =
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

static int visited[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct Node
{
    int node;
    struct Node *prev;
};

static void visit(int node, struct Node *prev_node)
{
    struct Node n = { node, prev_node };
    struct Node *p = &n;

    printf("-->> %s\n", __func__);
    if (node == 11)
        printf("Solution: ");
    do
        printf("%d%s", p->node + 1, (p->prev != NULL) ?  "->" : "\n");
    while ((p = p->prev) != NULL);

    visited[node] = 1;
    for (int i = 0; i < 12; ++i)
    {
        if ((visited[i] == 0) && (edges[node][i] == 1))
        {
            if (node == 11)
                printf("Continuing\n");
            visit(i, &n);
        }
    }
    visited[node] = 0;
    printf("<<-- %s\n", __func__);
}

static void chk_symmetry(void)
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (edges[i][j] != edges[j][i])
                printf("E[%d,%d] = %d, E[%d,%d] = %d\n", i, j, edges[i][j], j, i, edges[j][i]);
        }
    }
}

static void prt_links(void)
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = i; j < 12; j++)
        {
            if (edges[i][j])
                printf("%d -> %d\n", i+1, j+1);
        }
    }
}

int main(void)
{
    chk_symmetry();
    prt_links();
    visit(0, NULL);
    return 0;
}


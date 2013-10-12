#include <assert.h>
#include <stdio.h>

static int visited[64];

struct Node
{
    int node;
    struct Node *prev;
};

static void prt_path_r(struct Node *p)
{
    assert(p != 0);
    if (p->prev == NULL)
        printf("%d", p->node + 1);
    else
    {
        prt_path_r(p->prev);
        printf("->%d", p->node + 1);
    }
}

static void prt_path(struct Node *p)
{
    prt_path_r(p);
    putchar('\n');
}

static void visit(int node, struct Node *prev_node, int size, int edges[size][size], int end)
{
    struct Node n = { node, prev_node };
    struct Node *p = &n;

    printf("-->> %s\n", __func__);
    if (node == end)
    {
        printf("Solution: ");
        prt_path(p);
    }
    else
    {
        prt_path(p);
        visited[node] = 1;
        for (int i = 0; i < size; ++i)
        {
            if ((visited[i] == 0) && (edges[node][i] == 1))
                visit(i, &n, size, edges, end);
        }
        visited[node] = 0;
    }
    printf("<<-- %s\n", __func__);
}

static void chk_array_properties(char const *tag, int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != a[j][i])
                printf("E[%d,%d] = %d, E[%d,%d] = %d\n", i, j, a[i][j], j, i, a[j][i]);
        }
        if (a[i][i] != 0)
            fprintf(stderr, "%s[%d][%d] != 0\n", tag, i, i);
    }
}

static void prt_links(int size, int edges[size][size])
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

static int count_edges(int size, int edges[size][size])
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (edges[i][j])
                count++;
        }
    }
    return count;
}

static void dump_array(char const *fmt, int size, int edges[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf(fmt, edges[i][j]);
        putchar('\n');
    }
}

static void mark_edges(int n, int paths[n][n], int nodes[n][n])
{
    int pathnum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (paths[i][j] == 0)
            {
                nodes[i][j] = 0;
                nodes[j][i] = 0;
            }
            else
            {
                pathnum++;
                nodes[i][j] = pathnum;
                nodes[j][i] = pathnum;
            }
        }
    }
}

static void mark_connections(int prow, int pcol,
                             int npaths, int paths[npaths][npaths],
                             int nedges, int edges[nedges][nedges])
{
    int code = 100 * (prow + 1) + (pcol + 1);
    assert(pcol != prow);
    int r1 = paths[prow][pcol] - 1;
    assert(r1 >= 0 && r1 < nedges);

    /* First record paths to the right on this row */
    for (int i = pcol + 1; i < npaths; i++)
    {
        int r2;
        if ((r2 = paths[prow][i] - 1) >= 0)
        {
            assert(r2 >= 0 && r2 < nedges);
            edges[r1][r2] = code;
            edges[r2][r1] = code;
        }
    }

    /* Second record paths below in this column */
    for (int i = prow + 1; i < npaths; i++)
    {
        int r2;
        if ((r2 = paths[i][pcol] - 1) >= 0)
        {
            assert(r2 >= 0 && r2 < nedges);
            edges[r1][r2] = code;
            edges[r2][r1] = code;
        }
    }
}

static void map_paths_edges(int npaths, int paths[npaths][npaths],
                            int nedges, int edges[nedges][nedges])
{
    int nodes[npaths][npaths];

    mark_edges(npaths, paths, nodes);
    puts("Path numbers:");
    dump_array(" %2d", npaths, nodes);

    for (int i = 0; i < npaths; i++)
    {
        for (int j = i; j < npaths; j++)
        {
            if (nodes[i][j] != 0)
                mark_connections(i, j, npaths, nodes, nedges, edges);
        }
    }
}

static void zero_array(int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    }
}

int main(void)
{
    int paths[12][12] =
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

    puts("Stage 1:");
    chk_array_properties("paths", 12, paths);
    dump_array(" %d", 12, paths);
    prt_links(12, paths);
    visit(0, NULL, 12, paths, 11);

    puts("Stage 2:");
    int n = count_edges(12, paths);
    int edges[n][n];
    zero_array(n, edges);
    map_paths_edges(12, paths, n, edges);
    dump_array(" %4d", n, edges);
    chk_array_properties("edges", n, edges);
    prt_links(n, edges);
    visit(0, NULL, n, edges, n-1);

    return 0;
}


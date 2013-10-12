#include <assert.h>
#include <stdio.h>

struct Node
{
    int node;
    int edge;
    struct Node *prev;
};

static int num_solutions = 0;

typedef void (*Print)(struct Node *p);

static void prt_fwd_path_r(struct Node *p)
{
    char *pad = "";
    assert(p != 0);
    if (p->prev != NULL)
    {
        prt_fwd_path_r(p->prev);
        pad = " ->";
    }
    printf("%s N%d (E%d)", pad, p->node + 1, p->edge);
}

static void prt_fwd_path(struct Node *p)
{
    prt_fwd_path_r(p);
    putchar('\n');
}

static void visit2(int node, struct Node *prev_node, int size, int edges[size][size], int end, int *traversed)
{
    struct Node n = { node, 0, prev_node };
    struct Node *p = &n;

    printf("-->> %s (%d)\n", __func__, node);
    if (node == end)
    {
        printf("Solution %d: ", ++num_solutions);
        prt_fwd_path(p);
    }
    else
    {
        prt_fwd_path(p);
        for (int i = 0; i < size; ++i)
        {
            int e = edges[node][i];
            if (e != 0 && traversed[e] == 0)
            {
                traversed[e] = 1;
                n.edge = e;
                visit2(i, &n, size, edges, end, traversed);
                traversed[e] = 0;
            }
        }
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

static void mark_matrix(int n, int paths[n][n], int nodes[n][n])
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

static void zero_array(int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    }
}

static void zero_vector(int n, int v[n])
{
    for (int i = 0; i < n; i++)
        v[i] = 0;
}

int main(void)
{
    enum { N = 12 };
    int paths[N][N] =
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

    int matrix[N][N];
    int nedges = count_edges(N, paths);
    int edges[nedges + 1];
    zero_array(N, matrix);
    zero_vector(nedges + 1, edges);
    mark_matrix(N, paths, matrix);
    puts("Edges numbered:");
    dump_array(" %2d", N, matrix);
    chk_array_properties("matrix", N, matrix);
    prt_links(N, matrix);
    visit2(0, NULL, N, matrix, N-1, edges);
    printf("%d Solutions found\n", num_solutions);

    return 0;
}


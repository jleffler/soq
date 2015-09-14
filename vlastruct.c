#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int nr, nc;
    void *data;     // Actually double a[nr][nc]
} Matrix;

static double get(Matrix *a, int i, int j)
{
    double (*array)[a->nr][a->nc] = a->data;
    return (*array)[i][j];
}

static void set(Matrix *a, int i, int j, double v)
{
    double (*array)[a->nr][a->nc] = a->data;
    (*array)[i][j] = v;
}

static Matrix *mat_alloc(int nr, int nc)
{
    Matrix *m = malloc(sizeof(*m));
    if (m != 0)
    {
        m->nr = nr;
        m->nc = nc;
        m->data = malloc(nr * nc * sizeof(double));
        if (m->data == 0)
        {
            free(m);
            m = 0;
        }
    }
    return m;
}

static void mat_free(Matrix *m)
{
    free(m->data);
    free(m);
}

int main(void)
{
    int nr = 3;
    int nc = 5;

    Matrix *m = mat_alloc(nr, nc);

    for (int i = 0; i < nr; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            double v = (i * (nc + 1)) + j + 1;
            set(m, i, j, v);
            printf("Set: [%d,%d] = %4.1f\n", i, j, v);
        }
    }

    for (int j = 0; j < nc; j++)
    {
        for (int i = 0; i < nr; i++)
            printf("Get: [%d,%d] = %4.1f\n", i, j, get(m, i, j));
    }

    mat_free(m);
    return 0;
}


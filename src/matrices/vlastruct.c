/* SO 32565694 */
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
    assert(a != 0 && a->nr > 0 && a->nc > 0 && a->data != 0);
    assert(i >= 0 && i < a->nr && j >= 0 && j < a->nc);
    double (*array)[a->nr][a->nc] = a->data;
    return (*array)[i][j];
}

static void set(Matrix *a, int i, int j, double v)
{
    assert(a != 0 && a->nr > 0 && a->nc > 0 && a->data != 0);
    assert(i >= 0 && i < a->nr && j >= 0 && j < a->nc);
    double (*array)[a->nr][a->nc] = a->data;
    (*array)[i][j] = v;
}

static Matrix *mat_alloc(int nr, int nc)
{
    assert(nr > 0 && nc > 0);
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
    if (m != 0)
    {
        assert(m->data != 0 && m->nr > 0 && m->nc > 0);
        free(m->data);
        free(m);
    }
}

static double variant1(int nr, int nc, int r, int c)
{
    assert(nr != 0);
    return (r * nc) + c + 1;
}

static double variant2(int nr, int nc, int r, int c)
{
    return ((nr - r) * nc) + (nc - c) + 1;
}

typedef double (*Initializer)(int nr, int nc, int r, int c);

static void mat_init(Matrix *m, Initializer init)
{
    assert(m != 0 && m->nr > 0 && m->nc > 0 && m->data != 0);
    printf("Set: [%dx%d]\n", m->nr, m->nc);
    for (int i = 0; i < m->nr; i++)
    {
        printf("[%d]:", i);
        for (int j = 0; j < m->nc; j++)
        {
            double v = init(m->nr, m->nc, i, j);
            set(m, i, j, v);
            printf(" %6.1f", v);
        }
        putchar('\n');
    }
}

static Matrix *chk_mat_alloc(int nr, int nc)
{
    Matrix *m = mat_alloc(nr, nc);
    if (m == 0)
    {
        fprintf(stderr, "Matrix allocation for %dx%d matrix failed\n", nr, nc);
        exit(1);
    }
    return m;
}

static void mat_dump(const char *tag, Matrix *m)
{
    assert(m != 0 && m->nr > 0 && m->nc > 0 && m->data != 0);
    printf("Matrix %s: %dx%d\n", tag, m->nr, m->nc);
    for (int i = 0; i < m->nr; i++)
    {
        printf("[%d]:", i);
        for (int j = 0; j < m->nc; j++)
            printf(" %6.1f", get(m, i, j));
        putchar('\n');
    }
}

static Matrix *mat_multiply(Matrix *m1, Matrix *m2)
{
    assert(m1 != 0 && m1->nr > 0 && m1->nc > 0 && m1->data != 0);
    assert(m2 != 0 && m2->nr > 0 && m2->nc > 0 && m2->data != 0);
    assert(m1->nc == m2->nr);

    Matrix *m3 = chk_mat_alloc(m1->nr, m2->nc);
    double (*d1)[m1->nr][m1->nc] = m1->data;
    double (*d2)[m2->nr][m2->nc] = m2->data;
    double (*d3)[m3->nr][m3->nc] = m3->data;

    for (int i = 0; i < m1->nr; i++)
    {
        for (int j = 0; j < m2->nc; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < m1->nc; k++)
                sum += (*d1)[i][k] * (*d2)[k][j];
            (*d3)[i][j] = sum;
        }
    }

    return m3;
}

int main(void)
{

    int r1 = 3;
    int c1 = 5;
    int r2 = 5;
    int c2 = 4;

    Matrix *m1 = chk_mat_alloc(r1, c1);
    Matrix *m2 = chk_mat_alloc(r2, c2);

    printf("m1:\n");
    mat_init(m1, variant1);
    printf("m2:\n");
    mat_init(m2, variant2);

    mat_dump("m1", m1);
    mat_dump("m2", m2);

    Matrix *m3 = mat_multiply(m1, m2);
    mat_dump("m3", m3);

    mat_free(m1);
    mat_free(m2);
    mat_free(m3);
    return 0;
}


/* SO 3259-8224 (originally for SO 3256-5694) */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

static void mat_init(int nr, int nc, double m[nr][nc], Initializer init)
{
    assert(m != 0 && nr > 0 && nc > 0);
    printf("Set: [%dx%d]\n", nr, nc);
    for (int i = 0; i < nr; i++)
    {
        printf("[%d]:", i);
        for (int j = 0; j < nc; j++)
        {
            double v = init(nr, nc, i, j);
            m[i][j] = v;
            printf(" %6.0f", v);
        }
        putchar('\n');
    }
}

static void mat_dump(const char *tag, int nr, int nc, double m[nr][nc])
{
    assert(m != 0 && nr > 0 && nc > 0);
    printf("Matrix %s: %dx%d\n", tag, nr, nc);
    for (int i = 0; i < nr; i++)
    {
        printf("[%d]:", i);
        for (int j = 0; j < nc; j++)
            printf(" %6.0f", m[i][j]);
        putchar('\n');
    }
}

static void mat_multiply(int r1, int c1, double m1[r1][c1],
                         int r2, int c2, double m2[r2][c2],
                         int r3, int c3, double m3[r3][c3])
{
    assert(r1 > 0 && c1 > 0 && r2 > 0 && c2 > 0 && r3 > 0 && c3 > 0);
    printf("m1[%d][%d] x m2[%d][%d] = m3[%d][%d]\n", r1, c1, r2, c2, r3, c3);
    assert(r1 == r3 && c2 == c3 && c1 == r2);

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < c1; k++)
                sum += m1[i][k] * m2[k][j];
            m3[i][j] = sum;
        }
    }
}

int main(int argc, char **argv)
{
    int r1 = 3;
    int c1 = 5;
    int c2 = 4;
    if (argc == 4)
    {
        r1 = atoi(argv[1]);
        c1 = atoi(argv[2]);
        c2 = atoi(argv[3]);
        assert(r1 > 0 && r1 < 100 && c1 > 0 && c1 < 100 && c2 > 0 && c2 < 100);
    }
    int r2 = c1;
    int r3 = r1;
    int c3 = c2;

    double m1[r1][c1];
    double m2[r2][c2];
    double m3[r3][c3];

    printf("m1:\n");
    mat_init(r1, c1, m1, variant1);
    printf("m2:\n");
    mat_init(r2, c2, m2, variant2);

    mat_dump("m1", r1, c1, m1);
    mat_dump("m2", r2, c2, m2);
    mat_multiply(r1, c1, m1, r2, c2, m2, r3, c3, m3);
    mat_dump("m3", r3, c3, m3);

    return 0;
}


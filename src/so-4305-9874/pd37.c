/* SO Q 4305-9874 - closures in C, sort of */
/* SO A 4306-0435 - https://stackoverflow.com/a/43060435 */
/* pd37.c - starting to customize */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*predicate_t)(void *, int);

struct compose_fn_data
{
    predicate_t fn, a, b;
};

static int fn_and(void *data_, int x);

int fn_and(void *data_, int x)
{
    struct compose_fn_data *data = data_;

    return (*data->a)(data->a, x) && (*data->b)(data->b, x);
}

static int fn_or(void *data_, int x)
{
    struct compose_fn_data *data = data_;

    return (*data->a)(data->a, x) || (*data->b)(data->b, x);
}

static int fn_nota_and_b(void *data_, int x)
{
    struct compose_fn_data *data = data_;

    return !(*data->a)(data->a, x) && (*data->b)(data->b, x);
}

static predicate_t *mk_predicate(predicate_t comp_fn, predicate_t a, predicate_t b)
{
    struct compose_fn_data *rv = malloc(sizeof *rv);
    rv->fn = comp_fn;
    rv->a = a;
    rv->b = b;
    return &rv->fn;
}

static int isEven_p(void *vp, int x) { assert(vp != 0); return x % 2 == 0; }
static int isOdd_p(void *vp, int x) { assert(vp != 0); return !isEven_p(vp, x); }
static int isPos_p(void *vp, int x) { assert(vp != 0); return x > 0; }
static int isNeg_p(void *vp, int x) { assert(vp != 0); return x < 0; }

static unsigned count_p(const int *xs, unsigned len, predicate_t *predicate)
{
    int c = 0;
    printf("  =");
    for (unsigned i = 0; i < len; i++)
    {
        if ((**predicate)(predicate, xs[i]))
        {
            printf(" %2d", xs[i]);
            c++;
        }
    }
    printf(" matches predicate: ");
    return c;
}

/* OP's code */
static int isEven(int x) { return x % 2 == 0; }
static int isOdd(int x) { return !isEven(x); }
static int isPos(int x) { return x > 0; }
static int isNeg(int x) { return x < 0; }

static unsigned count(const int *xs, unsigned len, int (*predicate)(int))
{
    int c = 0;
    for (unsigned i = 0; i < len; i++)
    {
        if (predicate(xs[i]))
            c++;
    }
    return c;
}
/* EOP's code */

int main(void)
{
    int xs[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    const unsigned len = sizeof(xs) / sizeof(xs[0]);

    printf("Data:");
    for (unsigned i = 0; i < len; i++)
        printf(" %2d", xs[i]);
    putchar('\n');

    printf("Even: %d\n", count(xs, len, &isEven));
    printf(" Odd: %d\n", count(xs, len, &isOdd));
    printf(" Pos: %d\n", count(xs, len, &isPos));
    printf(" Neg: %d\n", count(xs, len, &isNeg));

    predicate_t *p1 = mk_predicate(fn_and, isEven_p, isPos_p);
    predicate_t *p2 = mk_predicate(fn_and, isEven_p, isNeg_p);
    predicate_t *p3 = mk_predicate(fn_and, isOdd_p, isPos_p);
    predicate_t *p4 = mk_predicate(fn_and, isOdd_p, isNeg_p);

    printf("Even && Positive: %d\n", count_p(xs, len, p1));
    printf("Even && Negative: %d\n", count_p(xs, len, p2));
    printf(" Odd && Positive: %d\n", count_p(xs, len, p3));
    printf(" Odd && Negative: %d\n", count_p(xs, len, p4));
    free(p1); free(p2); free(p3); free(p4);

    predicate_t *o1 = mk_predicate(fn_or, isEven_p, isPos_p);
    predicate_t *o2 = mk_predicate(fn_or, isEven_p, isNeg_p);
    predicate_t *o3 = mk_predicate(fn_or, isOdd_p, isPos_p);
    predicate_t *o4 = mk_predicate(fn_or, isOdd_p, isNeg_p);

    printf("Even || Positive: %d\n", count_p(xs, len, o1));
    printf("Even || Negative: %d\n", count_p(xs, len, o2));
    printf(" Odd || Positive: %d\n", count_p(xs, len, o3));
    printf(" Odd || Negative: %d\n", count_p(xs, len, o4));
    free(o1); free(o2); free(o3); free(o4);

    predicate_t *n1 = mk_predicate(fn_nota_and_b, isEven_p, isPos_p);
    predicate_t *n2 = mk_predicate(fn_nota_and_b, isEven_p, isNeg_p);
    predicate_t *n3 = mk_predicate(fn_nota_and_b, isOdd_p, isPos_p);
    predicate_t *n4 = mk_predicate(fn_nota_and_b, isOdd_p, isNeg_p);

    printf("!Even && Positive: %d\n", count_p(xs, len, n1));
    printf("!Even && Negative: %d\n", count_p(xs, len, n2));
    printf("! Odd && Positive: %d\n", count_p(xs, len, n3));
    printf("! Odd && Negative: %d\n", count_p(xs, len, n4));
    free(n1); free(n2); free(n3); free(n4);

    predicate_t *m1 = mk_predicate(fn_nota_and_b, isPos_p, isEven_p);
    predicate_t *m2 = mk_predicate(fn_nota_and_b, isNeg_p, isEven_p);
    predicate_t *m3 = mk_predicate(fn_nota_and_b, isPos_p, isOdd_p);
    predicate_t *m4 = mk_predicate(fn_nota_and_b, isNeg_p, isOdd_p);

    printf("!Positive && Even: %d\n", count_p(xs, len, m1));
    printf("!Negative && Even: %d\n", count_p(xs, len, m2));
    printf("!Positive &&  Odd: %d\n", count_p(xs, len, m3));
    printf("!Negative &&  Odd: %d\n", count_p(xs, len, m4));
    free(m1); free(m2); free(m3); free(m4);

    return 0;
}

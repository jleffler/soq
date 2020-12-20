#include "genlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static void print_int(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, " %d", *(int *)np->data);
}

static void print_dbl(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, " %7.3f", *(double *)np->data);
}

#ifdef DEBUG
static void print_int_debug(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, "%d (0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR ")\n",
            *(int *)np->data, (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
}

static void print_dbl_debug(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, "%7.3f (0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR ")\n",
            *(double *)np->data, (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
}

static void dump_list(const char *tag, const list *lp, Apply apply)
{
    printf("%s: %zu: 0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR "\n",
           tag, lp->elementSize, (uintptr_t)lp, (uintptr_t)lp->head, (uintptr_t)lp->tail);
    listApplyForward(lp, apply, stdout);
}
#endif /* DEBUG */

static void int_sum(const node *np, void *thunk)
{
    int *sum = thunk;
    *sum += *(int *)np->data;
}

typedef struct DblFun
{
    double val;
    int    idx;
} DblFun;

static void dbl_fun(const node *np, void *thunk)
{
    DblFun *dp = thunk;
    double val = *(double *)np->data;
    if (dp->idx == 0)
        dp->val = val;
    else if (dp->idx % 2 == 1)
        dp->val /= val;
    else
        dp->val *= val;
    dp->idx++;
}

int main(void)
{
    list *l1 = listCreate(sizeof(int));
#ifdef DEBUG
    dump_list("Created", l1, print_int_debug);
#endif /* DEBUG */
    for (int i = 0; i < 10; i++)
    {
        //int j = 300 + i;
        //listPushTail(l1, &j);
        listPushTail(l1, &i);
#ifdef DEBUG
        dump_list("Added", l1, print_int_debug);
#endif /* DEBUG */
        printf("List forward: ");
        listApplyForward(l1, print_int, stdout);
        putchar('\n');
        printf("List reverse: ");
        listApplyReverse(l1, print_int, stdout);
        putchar('\n');
    }
    int sum = 0;
    listApplyForward(l1, int_sum, &sum);
    printf("Sum = %d\n", sum);
    listDestroy(l1);

    list *l2 = listCreate(sizeof(double));
#ifdef DEBUG
    dump_list("Created", l2, print_dbl_debug);
#endif /* DEBUG */
    for (int i = 0; i < 10; i++)
    {
        double d = (rand() % 20000) / 100.0 - 100.0;
        listPushHead(l2, &d);
#ifdef DEBUG
        dump_list("Added", l1, print_dbl_debug);
#endif /* DEBUG */
        printf("List forward: ");
        listApplyForward(l2, print_dbl, stdout);
        putchar('\n');
        printf("List reverse: ");
        listApplyReverse(l2, print_dbl, stdout);
        putchar('\n');
    }
    DblFun d1 = { 0.0, 0 };
    DblFun d2 = { 0.0, 0 };
    listApplyForward(l2, dbl_fun, &d1);
    listApplyReverse(l2, dbl_fun, &d2);
    printf("Fwd: %13.6g, Rev: %13.6g\n", d1.val, d2.val);
    listDestroy(l2);

    return 0;
}

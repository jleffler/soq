/*
** This code would need to be embedded inside genlist.c because it uses
** the internals of the node and list structures.
**
** They were used before the list type was made opaque and the node type
** was hidden completely.  They would need revision before being
** reusable.  In particular, the print_int_debug() and print_dbl_debug()
** functions are no longer passed the const node *np argument but are
** passed only the value of np->data, so they cannot print the pointers
** to next and previous nodes in the list.
**
** They were very useful while debugging the code, but are now relics
** that require alternative 'apply' functions.
*/

#ifdef DEBUG
static void print_int_debug(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, "%d (0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR ")\n",
            *(int *)data, (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
}

static void print_dbl_debug(const node *np, void *thunk)
{
    FILE *fp = thunk;
    fprintf(fp, "%7.3f (0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR ")\n",
            *(double *)data, (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
}

static void dump_list(const char *tag, const list *lp, Apply apply)
{
    printf("%s: %zu: 0x%.12" PRIXPTR ",0x%.12" PRIXPTR ",0x%.12" PRIXPTR "\n",
           tag, lp->elementSize, (uintptr_t)lp, (uintptr_t)lp->head, (uintptr_t)lp->tail);
    listApplyForward(lp, apply, stdout);
}
#endif /* DEBUG */

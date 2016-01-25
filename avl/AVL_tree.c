#include "AVL_tree.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static void dump_pointer(const char *tag, void *vp);
static void dump_tree_inorder(const char *tag, struct vertex *v);
static void dump_tree_inorder_notag(const struct vertex *v);
static void dump_vertex(const char *tag, struct vertex *v);

static inline long
max(long a, long b)
{
    return(((a) > (b)) ? a : b);
}

static long
balance_factor(struct vertex *v)
{
    assert(v != NULL);
    if (v->l == NULL && v->r == NULL)
        return 0;
    else if (v->l == NULL)
        return (-1) - v->r->height;
    else if (v->r == NULL)
        return v->l->height - (-1);

    return(v->l->height - v->r->height);
}

static void
update_height(struct vertex *v)
{
    assert(v != NULL);
    if (v->l == NULL && v->r == NULL)
    {
        v->height = 0;
        return;
    }
    else if (v->l == NULL)
    {
        v->height = v->r->height + 1;
        return;
    }
    else if (v->r == NULL)
    {
        v->height = v->l->height + 1;
        return;
    }
    v->height = max(v->l->height, v->r->height) + 1;
}

static void
right_rotate(struct vertex **v)
{
    if ((*v)->p != NULL)
    {
        if ((*v)->p->l == (*v))
            (*v)->p->l = (*v)->l;
        else
            (*v)->p->r = (*v)->l;
    }
    struct vertex  *tmp = (*v)->l->r;
    (*v)->l->r = (*v);
    (*v)->l->p = (*v)->p;
    (*v)->p = (*v)->l;
    (*v)->l = tmp;
    if (tmp != NULL)
        tmp->p = (*v);

    update_height(*v);
    (*v) = (*v)->p;
    update_height(*v);
}

static void
left_rotate(struct vertex **v)
{
    assert(v != NULL);
    assert(*v != NULL);
    dump_vertex("-->> left_rotate", *v);
    if ((*v)->r == NULL)
        printf("1 r == NULL\n");

    if ((*v)->p != NULL)
    {
        printf("p is not NULL\n");
        if ((*v)->p->r == (*v))
        {
            (*v)->p->r = (*v)->r;
        }
        else if ((*v)->p->l == (*v))
        {
            struct vertex *ov = *v;
            printf("p's l  == v\n");
            dump_pointer("LR1 -  v", v);
            dump_pointer("LR1 - *v", *v);
            dump_vertex("LR1 -  current node", *v);
            dump_vertex("LR1 -   parent node", (*v)->p);
            dump_vertex("LR1 -  parent  left", (*v)->p->l);
            dump_vertex("LR1 - current right", (*v)->r);
            dump_vertex("LR1 -  old vertex *", ov);
            dump_tree_inorder("LR1 - tree from parent", (*v)->p);

            //if ((*v)->r != NULL)
                //printf("WTF r != NULL r %p p %p p->l %p (*v) %p\n", (*v)->r, (*v)->p, (*v)->p->l, (*v));

            printf("Assign (*v)->r (0x%.9" PRIXPTR ") to (*v)->p->l (0x%.9" PRIXPTR ")\n",
                (uintptr_t)(*v)->r, (uintptr_t)(*v)->p->l);
            (*v)->p->l = (*v)->r;

            dump_pointer("LR2 -  v", v);
            dump_pointer("LR2 - *v", *v);
            dump_vertex("LR2 -  current node", *v);
            dump_vertex("LR2 -   parent node", (*v)->p);
            dump_vertex("LR2 -  parent  left", (*v)->p->l);
            dump_vertex("LR2 - current right", (*v)->r);
            dump_vertex("LR2 -  old vertex *", ov);
            // At this point, we don't have a tree
            //dump_tree_inorder("LR2 - tree from parent", (*v)->p);

            //if ((*v)->r == NULL)
                //printf("WTF r == NULL r %p p %p p->l %p (*v) %p\n", (*v)->r, (*v)->p, (*v)->p->l, (*v));
        }
        else
        {
            printf("error case\n");
        }
    }
    else
        dump_vertex("(*v)->p == NULL", (*v)->p);
    printf("get there before\n");

    if ((*v)->r == NULL)
        printf("r == NULL\n");

    assert((*v)->r != NULL);

    struct vertex  *tmp = (*v)->r->l;
    printf("get there after\n");
    (*v)->r->l = (*v);
    printf("get there\n");
    (*v)->r->p = (*v)->p;
    (*v)->p = (*v)->r;
    (*v)->r = tmp;
    printf("get there\n");
    if (tmp != NULL)
        tmp->p = (*v);
    printf("get there\n");
    update_height(*v);
    (*v) = (*v)->p;
    update_height(*v);
    dump_vertex("<<-- left_rotate", *v);
}

static void
insert_fixup(struct vertex *new_vertex)
{
    dump_tree_inorder("insert fixup 0", new_vertex);
    while ((new_vertex->p != NULL)
           && ((new_vertex->height + 1) > new_vertex->p->height))
    {
        update_height(new_vertex->p);
        new_vertex = new_vertex->p;
        if (balance_factor(new_vertex) == 2)
        {
            if (balance_factor(new_vertex->l) == -1)
            {
                printf("double left right rotating\n");
                left_rotate(&new_vertex->l);
                printf("double left right rotating finish\n");
            }
            right_rotate(&new_vertex);
            dump_tree_inorder("insert fixup 1", new_vertex);
            return;
        }
        else if (balance_factor(new_vertex) == -2)
        {
            if (balance_factor(new_vertex->r) == 1)
            {
                printf("double right left rotating\n");
                right_rotate(&new_vertex->r);
                printf("double right rotating finish\n");
            }
            left_rotate(&new_vertex);
            dump_tree_inorder("insert fixup 2", new_vertex);
            return;
        }
    }
    dump_tree_inorder("insert fixup 3", new_vertex);
}

void
insert(struct vertex **tree, int data)
{
    assert(tree != NULL);
    printf("-->> %s: data %d; tree 0x%.9" PRIXPTR "\n", __func__, data, (uintptr_t)*tree);
    struct vertex  *new_vertex = malloc(sizeof(struct vertex));
    assert(new_vertex != NULL);
    new_vertex->data = data;
    new_vertex->height = 0;
    new_vertex->l = NULL;
    new_vertex->r = NULL;
    new_vertex->p = NULL;

    if (tree == NULL)
        return;
    else if (*tree == NULL)
    {
        *tree = new_vertex;
        dump_tree_inorder("insert-1", *tree);
        printf("<<-- %s: data %d; tree 0x%.9" PRIXPTR "\n", __func__, data, (uintptr_t)*tree);
        return;
    }
    struct vertex  *root = *tree;
    while (1)
    {
        if (root->data < data)
        {
            if (root->r != NULL)
                root = root->r;
            else
            {
                root->r = new_vertex;
                new_vertex->p = root;
                break;
            }
        }
        else
        {
            if (root->l != NULL)
                root = root->l;
            else
            {
                root->l = new_vertex;
                new_vertex->p = root;
                break;
            }
        }
    }
    insert_fixup(new_vertex);
    while ((*tree)->p != NULL)
    {
        (*tree) = (*tree)->p;
    }
    dump_tree_inorder("insert-2", *tree);
    printf("<<-- %s: data %d; tree 0x%.9" PRIXPTR "\n", __func__, data, (uintptr_t)*tree);
}

void *
find(struct vertex *v, int data)
{
    while (v != NULL && v->data != data)
    {
        if (v->data < data)
            v = v->r;
        else
            v = v->l;
    }

    return v;
}

static void
free_tree(struct vertex *root)
{
    if (root != NULL)
    {
        free_tree(root->l);
        free_tree(root->r);
        free(root);
    }
}

void
clear_tree(struct vertex **root)
{
    free_tree(*root);
    *root = NULL;
}

/* Debugging aids */

static void dump_pointer(const char *tag, void *vp)
{
    printf("%s: 0x%.9" PRIXPTR "\n", tag, (uintptr_t)vp);
    fflush(stdout);
}

static void dump_vertex(const char *tag, struct vertex *v)
{
    if (v == NULL)
        printf("%s: data  ; height  ; v = 0x%.9" PRIXPTR "\n", tag, (uintptr_t)v);
    else
        printf("%s: data %d; height %ld; v = 0x%.9" PRIXPTR ", l = 0x%.9"
               PRIXPTR ", r = 0x%.9" PRIXPTR ", p = 0x%.9" PRIXPTR "\n",
               tag, v->data, v->height, (uintptr_t)v, (uintptr_t)v->l,
               (uintptr_t)v->r, (uintptr_t)v->p);
    fflush(stdout);
}

static void dump_tree_inorder_notag(const struct vertex *v)
{
    if (v != NULL)
    {
        dump_tree_inorder_notag(v->l);
        printf("data %d; height %ld; v = 0x%.9" PRIXPTR ", l = 0x%.9" PRIXPTR
               ", r = 0x%.9" PRIXPTR ", p = 0x%.9" PRIXPTR "\n",
               v->data, v->height, (uintptr_t)v, (uintptr_t)v->l,
               (uintptr_t)v->r, (uintptr_t)v->p);
        dump_tree_inorder_notag(v->r);
        fflush(stdout);
    }
}

static void dump_tree_inorder(const char *tag, struct vertex *v)
{
    printf("-->> %s: (root 0x%.9" PRIXPTR ")\n", tag, (uintptr_t)v);
    dump_tree_inorder_notag(v);
    printf("<<-- %s:\n", tag);
    fflush(stdout);
}

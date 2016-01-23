#include "AVL_tree.h"
#include <stdio.h>
#include <stdlib.h>

static long
max(long a, long b)
{
    return(((a) > (b)) ? a : b);
}

static long
balance_factor(struct vertex *v)
{
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
    if (v->l == NULL
        && v->r == NULL)
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
    if ((*v)->r == NULL)
        printf("1 r == NULL\n");

    if ((*v)->p != NULL)
    {
        printf(" p is not NULL\n");
        if ((*v)->p->r == (*v))
            (*v)->p->r = (*v)->r;
        else if ((*v)->p->l == (*v))
        {
            printf("p's l  == v\n");

            if ((*v)->r != NULL)
                printf("WTF r != NULL r %p p %p p->l %p (*v) %p \n", (*v)->r, (*v)->p, (*v)->p->l, (*v));

            (*v)->p->l = (*v)->r;
            if ((*v)->r == NULL)
                printf("WTF r == NULL r %p p %p p->l %p (*v) %p \n", (*v)->r, (*v)->p, (*v)->p->l, (*v));
        }
        else
        {
            printf("error case \n");
        }
    }
    printf("get there before\n");

    if ((*v)->r == NULL)
        printf("r == NULL\n");

    struct vertex  *tmp = (*v)->r->l;
    printf("get there after\n");
    (*v)->r->l = (*v);
    printf("get there \n");
    (*v)->r->p = (*v)->p;
    (*v)->p = (*v)->r;
    (*v)->r = tmp;
    printf("get there \n");
    if (tmp != NULL)
        tmp->p = (*v);
    printf("get there \n");
    update_height(*v);
    (*v) = (*v)->p;
    update_height(*v);
}

static void
insert_fixup(struct vertex *new_vertex)
{
    while ((new_vertex->p != NULL)
           && ((new_vertex->height + 1) > new_vertex->p->height))
    {
        update_height(new_vertex->p);
        new_vertex = new_vertex->p;
        if (balance_factor(new_vertex) == 2)
        {
            if (balance_factor(new_vertex->l) == -1)
            {
                printf("double left right rotating \n");
                left_rotate(&new_vertex->l);
            }
            right_rotate(&new_vertex);
            return;
        }
        else if (balance_factor(new_vertex) == -2)
        {
            if (balance_factor(new_vertex->r) == 1)
            {
                printf("double right left rotating \n");
                right_rotate(&new_vertex->r);
                printf("double right rotating finish\n");
            }
            left_rotate(&new_vertex);
            return;
        }
    }
}

void
insert(struct vertex **tree, int data)
{
    struct vertex  *new_vertex = malloc(sizeof(struct vertex));
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
}

void *
find(struct vertex *v, int data)
{
    while (v != NULL && v->data != data)
        if (v->data < data)
            v = v->r;
        else
            v = v->l;

    return v;
}

static void
free_tree(struct vertex *root)
{
    if (root->l != NULL)
        free_tree(root->l);
    if (root->r != NULL)
        free_tree(root->r);

    free(root);
}

void
clear_tree(struct vertex **root)
{
    free_tree(*root);
    *root = NULL;
}

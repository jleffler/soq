#include "genlist.h"
#include <assert.h>     /* DEBUG */

#ifdef DEBUG
#include <inttypes.h>   /* DEBUG */
#include <stdio.h>      /* DEBUG */
#endif /* DEBUG */
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node
{
    void    *data;
    node    *next;
    node    *prev;
};

struct list
{
    node    *head;
    node    *tail;
    size_t  elementSize;
};

static node *nodeCreate(void *data, size_t typeSize)
{
    node *np = malloc(sizeof(node));
    assert(np != NULL);
    np->data = malloc(typeSize);
    assert(np->data != NULL);
    memcpy(np->data, data, typeSize);
    np->prev = np->next = NULL;
#ifdef DEBUG
    printf("Node: %zu: %.12" PRIXPTR ",%.12" PRIXPTR ",%.12" PRIXPTR "\n",
            typeSize, (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
    fflush(stdout);
#endif /* DEBUG */
    return np;
}

list *listCreate(size_t typeSize)
{
    list *lp = malloc(sizeof(*lp));
    assert(lp != NULL);
    lp->head = lp->tail = NULL;
    lp->elementSize = typeSize;
#ifdef DEBUG
    printf("List: %zu: %.12" PRIXPTR ",%.12" PRIXPTR ",%.12" PRIXPTR "\n",
            lp->elementSize, (uintptr_t)lp, (uintptr_t)lp->head, (uintptr_t)lp->tail);
    fflush(stdout);
#endif /* DEBUG */
    return lp;
}

void listDestroy(list *lp)
{
    assert(lp != NULL);
#ifdef DEBUG
    printf("Destroy List: %zu: %.12" PRIXPTR ",%.12" PRIXPTR ",%.12" PRIXPTR "\n",
            lp->elementSize, (uintptr_t)lp, (uintptr_t)lp->head, (uintptr_t)lp->tail);
    fflush(stdout);
#endif /* DEBUG */
    node *np = lp->head;
    while (np != NULL)
    {
#ifdef DEBUG
        printf("Destroy Node: %.12" PRIXPTR ",%.12" PRIXPTR ",%.12" PRIXPTR "\n",
                (uintptr_t)np, (uintptr_t)np->prev, (uintptr_t)np->next);
        fflush(stdout);
#endif /* DEBUG */
        node *next = np->next;
        free(np->data);
        free(np);
        np = next;
    }
    free(lp);
}

void listPushTail(list *lp, void *val)
{
    node *newNode = nodeCreate(val, lp->elementSize);
    if (lp->head == NULL)
    {
        lp->head = newNode;
        lp->tail = newNode;
    }
    else
    {
        lp->tail->next = newNode;
        newNode->prev = lp->tail;
        lp->tail = newNode;
    }
}

void listPushHead(list *lp, void *val)
{
    node *newNode = nodeCreate(val, lp->elementSize);
    if (lp->head == NULL)
    {
        lp->head = newNode;
        lp->tail = newNode;
    }
    else
    {
        lp->head->prev = newNode;
        newNode->next = lp->head;
        lp->head = newNode;
    }
}

void listApplyForward(const list *lp, Apply apply, void *thunk)
{
    node *ptr = lp->head;
    while (ptr != NULL)
    {
        // apply(ptr, thunk);
        (*apply)(ptr->data, thunk);
        ptr = ptr->next;
    }
}

void listApplyReverse(const list *lp, Apply apply, void *thunk)
{
    node *ptr = lp->tail;
    while (ptr != NULL)
    {
        // apply(ptr, thunk);
        (*apply)(ptr->data, thunk);
        ptr = ptr->prev;
    }
}

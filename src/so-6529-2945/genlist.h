#ifndef GENLIST_H_INCLUDED
#define GENLIST_H_INCLUDED

#include <stddef.h>     /* size_t */

typedef struct node
{
    void        *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct list
{
    struct node *head;
    struct node *tail;
    size_t elementSize;
} list;

typedef void (*Apply)(const node *n, void *thunk);

extern list *listCreate(size_t typeSize);
extern void listDestroy(list *l);

extern void listPushHead(list *l, void *val);
extern void listPushTail(list *l, void *val);

extern void listApplyForward(const list *l, Apply apply, void *thunk);
extern void listApplyReverse(const list *l, Apply apply, void *thunk);

#endif /* GENLIST_H_INCLUDED */

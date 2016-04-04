/* SO 32578455 */
/* Swap elements A and B in a doubly-linked list */
/*
** Issues:
** -- Is the list circular?
** -- How is the head tracked?
** -- Is the tail tracked?  If so, how?
*/

/*
**
**    +----+    +---+    +----+    +---+     +----+
** 1  | P1 |    | A |    | P2 |    | B |     | P3 |
**    +----+    +---+    +----+    +---+     +----+
**
**    +----+    +---+    +---+     +----+
** 2  | P1 |    | A |    | B |     | P3 |
**    +----+    +---+    +---+     +----+
**
**    +----+    +---+    +---+
** 3  | P1 |    | A |    | B |
**    +----+    +---+    +---+
**
**    +---+    +---+     +----+
** 4  | A |    | B |     | P3 |
**    +---+    +---+     +----+
**
**    +---+    +---+
** 5  | A |    | B |
**    +---+    +---+
**
** Assuming you know that A appears before B in the list:
** -- For case 1 (A and B are not adjacent to each other):
**    record the entry before A (P1) and after B (P3);
**    delete A and B; insert B after P1; insert A before P3.
** -- For cases 2-5 (A and B are adjacent to each other and A is first):
**    delete A; insert A after B.
**
** How to tell if the two nodes are adjacent?
** -- If A->next == B, the nodes are adjacent and A precedes B.
** -- If B->next == A, the nodes are adjacent and B precedes A.
** -- Else, the nodes are case 1: record P1 (node before A) and P3 (node after B);
**    delete A and B; insert A before P3; insert B after P1.
*/

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stderr.h"

typedef struct List List;
typedef char *Data;

#define PRI_Data    "s"
#define SCN_Data    "s"

struct List
{
    Data    data;
    List   *next;
    List   *prev;
};

typedef void (*Apply)(List *list, void *context);

static List *new_item(Data value);
static inline void  ins_item(List *posn, List *item);
static inline void  add_item(List *posn, List *item);
static inline void  rem_item(List *item);
static inline void  del_item(List *item);
static inline void  prt_item(FILE *fp, List *item);

static inline void  prt_list(FILE *fp, const char *tag, List *list);
static inline void  zap_list(List *list);
static inline void  fwd_list(List *list, Apply apply, void *context);
static inline void  app_item(List *item, void *context);

//static List root = { 0, &root, &root };
//static List *head = &root;

static inline List *new_item(Data value)
{
    List *item = malloc(sizeof(*item));
    if (item == 0)
        err_syserr("Out of memory! ");
    if (value == 0)
        item->data = 0;
    else
        item->data = strdup(value);
    item->next = 0;
    item->prev = 0;
    return item;
}

static inline void  prt_item(FILE *fp, List *item)
{
    if (item != 0)
    {
        fprintf(fp, "I = 0x%.12" PRIXPTR ", P = 0x%.12" PRIXPTR ", N = 0x%.12" PRIXPTR ": ",
                (uintptr_t)item, (uintptr_t)item->prev, (uintptr_t)item->next);
        if (item->data != 0)
            fprintf(fp, "[%" PRI_Data "]", item->data);
        putc('\n', fp);
    }
}

/* Insert item before posn */
static inline void ins_item(List *posn, List *item)
{
    item->prev = posn->prev;
    item->next = posn;
    posn->prev->next = item;
    posn->prev = item;
}

/* Append item after posn */
static inline void add_item(List *posn, List *item)
{
    printf("Before adding:\n");
    prt_item(stdout, posn);
    prt_item(stdout, item);
    item->prev = posn;
    item->next = posn->next;
    posn->next->prev= item;
    posn->next = item;
    printf("After adding:\n");
    prt_item(stdout, posn);
    prt_item(stdout, item);
}

/* Remove item */
static inline void rem_item(List *item)
{
    item->prev->next = item->next;
    item->next->prev = item->prev;
    //if (head == item)
    //    head = item->next;
}

static inline void app_item(List *item, void *context)
{
    prt_item((FILE *)context, item);
}

static inline void fwd_list(List *list, Apply appfun, void *context)
{
    if (list != 0)
    {
        List *item = list;
        while (item->next != list)
        {
            assert(item->next != 0);
            item = item->next;
            (*appfun)(item, context);   /* Beware: arguments can be reversed without a compiler error! */
        }
    }
}

static inline void rev_list(List *list, Apply appfun, void *context)
{
    if (list != 0)
    {
        List *item = list;
        while (item->prev != list)
        {
            assert(item->prev != 0);
            item = item->prev;
            (*appfun)(item, context);   /* Beware: arguments can be reversed without a compiler error! */
        }
    }
}

static inline void prt_list(FILE *fp, const char *tag, List *list)
{
    fprintf(fp, "List: %s (0x%.12" PRIXPTR ")\n", tag, (uintptr_t)list);
    fwd_list(list, app_item, fp);
    fprintf(fp, "EOL\n");
}

static inline void del_item(List *item)
{
    free(item->data);
    free(item);
}

static inline void zap_list(List *list)
{
    if (list != 0)
    {
        printf("Zapping list:\n");
        List *item = list;
        List *next;
        while ((next = item->next) != list)
        {
            prt_item(stdout, item);
            del_item(item);
            item = next;
        }
        del_item(item);
    }
}

static inline void swap_items(List *i1, List *i2)
{
    assert(i1 != 0 && i2 != 0 && i1 != i2);
    if (i1->next == i2)
    {
        rem_item(i1);
        add_item(i2, i1);
    }
    else if (i2->next == i1)
    {
        rem_item(i2);
        add_item(i1, i2);
    }
    else
    {
        List *p1 = i1->prev;
        List *p3 = i2->next;
        rem_item(i1);
        rem_item(i2);
        add_item(p1, i2);
        add_item(p3, i1);
    }
}

int main(void)
{
    List *head = new_item(0);
    List *i1 = new_item("P1");
    List *i2 = new_item("P2");
    List *i3 = new_item("P3");
    List *i4 = new_item("A");
    List *i5 = new_item("B");

    printf("Items created\n");
    assert(head != 0);
    assert(i1 != 0);
    assert(i2 != 0);
    assert(i3 != 0);
    assert(i4 != 0);
    assert(i5 != 0);
    prt_item(stdout, i1);
    prt_item(stdout, i2);
    prt_item(stdout, i3);
    prt_item(stdout, i4);
    prt_item(stdout, i5);

    head->next = head->prev = head;
    prt_item(stdout, head);

    prt_list(stdout, "List 1 Before", head);
    printf("Add i3\n");
    add_item(head, i3);
    prt_list(stdout, "List 1 after i3", head);
    printf("Add i5\n");
    add_item(head, i5);
    prt_list(stdout, "List 1 after i5", head);
    printf("Add i2\n");
    add_item(head, i2);
    prt_list(stdout, "List 1 after i2", head);
    printf("Add i4\n");
    add_item(head, i4);
    prt_list(stdout, "List 1 after i4", head);
    printf("Add i1\n");
    add_item(head, i1);
    prt_list(stdout, "List 1 after i1", head);
    printf("Items added\n");

    //prt_list(stdout, "List 1 Before", head);
    //swap_items(i4, i5);
    //prt_list(stdout, "List 1 After", head);

    zap_list(head);

    return 0;
}


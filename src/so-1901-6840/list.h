#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>

typedef int data_t;

typedef struct node_t node_t;
struct node_t
{
    node_t *next;
    node_t *prev;
    data_t  data;
};

typedef struct list_t list_t;
struct list_t
{
    node_t *head;
    node_t *tail;
    size_t  size;
};

extern node_t *node_construct(data_t data);
extern void    node_destruct(node_t *node);

extern size_t  list_size(list_t *list);
extern void    list_insert_tail(list_t *list, node_t *node);
extern node_t *list_remove_head(list_t *list);
extern void    list_destruct(list_t *list);
extern list_t *list_construct(void);
extern void    dump_list(FILE *fp, const char *tag, list_t *list);

extern void list_sort_merge(list_t *list_ptr);

#endif /* LIST_H_INCLUDED */

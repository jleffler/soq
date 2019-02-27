#include "list.h"
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>

node_t *list_head(list_t *list)
{
    return list->head;
}

node_t *list_tail(list_t *list)
{
    return list->tail;
}


size_t list_size(list_t *list)
{
    return list->size;
}

void list_insert_tail(list_t *list, node_t *node)
{
    assert(list != 0);
    assert(node != 0);
    if (list->tail == 0)
    {
        assert(list->tail == 0 && list->head == 0 && list->size == 0);
        list->tail = node;
        list->head = node;
        node->prev = 0;
        node->next = 0;
        list->size = 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = 0;
        list->size++;
        list->tail = node;
    }
}

node_t *list_remove_head(list_t *list)
{
    assert(list != 0);
    node_t *node = list->head;
    if (list->head != 0)
    {
        assert(list->size > 0);
        list->head = node->next;
        if (node->next != 0)
            node->next->prev = 0;
        node->prev = 0;
        node->next = 0;
        list->size--;
    }
    return node;
}

void list_destruct(list_t *list)
{
    assert(list != 0);
    node_t *next;
    for (node_t *node = list->head; node != 0; node = next)
    {
        next = node->next;
        node_destruct(node);
    }
    free(list);
}

void dump_list(FILE *fp, const char *tag, list_t *list)
{
    assert(list != 0);
    fprintf(fp, "List %s (0x%.12" PRIXPTR ")\n", tag, (uintptr_t)list);
    fprintf(fp, "Head 0x%.12" PRIXPTR ", Tail 0x%.12" PRIXPTR ", Size %zu\n",
            (uintptr_t)list->head, (uintptr_t)list->tail, list->size);
    size_t i = 0;
    for (node_t *node = list->head; node != 0; node = node->next)
        fprintf(fp, "%2zu: Node 0x%.12" PRIXPTR ", Next 0x%.12" PRIXPTR ", Prev 0x%.12" PRIXPTR ", Data %d\n",
            ++i, (uintptr_t)node, (uintptr_t)node->next, (uintptr_t)node->prev, node->data);
}

list_t *list_construct(void)
{
    list_t *list = malloc(sizeof(*list));
    if (list != 0)
    {
        list->head = 0;
        list->tail = 0;
        list->size = 0;
    }
    return list;
}

node_t *node_construct(data_t data)
{
    node_t *node = malloc(sizeof(*node));
    if (node != 0)
    {
        node->data = data;
        node->next = 0;
        node->prev = 0;
    }
    return node;
}

void node_destruct(node_t *node)
{
    free(node);
}

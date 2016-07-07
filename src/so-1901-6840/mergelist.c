#include "list.h"
#include <assert.h>

static void mergelist(list_t *list_ptr, list_t *left_list, list_t *right_list);
static void splitlist(list_t *list_ptr, list_t *left_list, list_t *right_list);

static int comp_proc(data_t d1, data_t d2)
{
    if (d1 > d2)
        return +1;
    else if (d1 < d2)
        return -1;
    else
        return 0;
}

void list_sort_merge(list_t *list_ptr)
{
    if (list_ptr->size > 1)
    {
        dump_list(stdout, "-->>list_sort_merge()", list_ptr);
        list_t *right_list = list_construct();
        list_t *left_list = list_construct();
        splitlist(list_ptr, left_list, right_list);
        dump_list(stdout, "Split-L", left_list);
        dump_list(stdout, "Split-R", right_list);
        list_sort_merge(left_list);
        list_sort_merge(right_list);
        //dump_list(stdout, "Sort-L", left_list);
        //dump_list(stdout, "Sort-R", right_list);
        list_ptr->head = NULL;
        list_ptr->tail = NULL;
        list_ptr->size = 0;
        mergelist(list_ptr, left_list, right_list);
        list_destruct(right_list);
        list_destruct(left_list);
        dump_list(stdout, "<<--list_sort_merge()", list_ptr);
    }
}

static void mergelist(list_t *list_ptr, list_t *left_list, list_t *right_list)
{
    node_t *holder;
    fprintf(stdout, "-->>list_sort_merge()\n");
    dump_list(stdout, "List-L", left_list);
    dump_list(stdout, "List-R", right_list);
    while (left_list->size > 0 && right_list->size > 0)
    {
        assert(left_list->head != 0 && right_list->head != 0);
        /* Sort into descending order */
        if (comp_proc(left_list->head->data, right_list->head->data) > 0)
        {
            holder = list_remove_head(left_list);
            list_insert_tail(list_ptr, holder);
        }
        else
        {
            holder = list_remove_head(right_list);
            list_insert_tail(list_ptr, holder);
        }
    }
    while (left_list->size > 0)
    {
        holder = list_remove_head(left_list);
        list_insert_tail(list_ptr, holder);
    }
    while (right_list->size > 0)
    {
        holder = list_remove_head(right_list);
        list_insert_tail(list_ptr, holder);
    }
    fprintf(stdout, "<<--list_sort_merge()\n");
}

static void splitlist(list_t *list_ptr, list_t *left_list, list_t *right_list)
{
    if (list_ptr->size > 1)
    {
        size_t temp = 0;
        node_t *holder = list_ptr->head;
        right_list->size = list_ptr->size / 2;
        left_list->size = list_ptr->size - right_list->size;

        left_list->head = list_ptr->head;
        right_list->tail = list_ptr->tail;

        while (temp < left_list->size)
        {
            temp++;
            holder = holder->next;
        }

        right_list->head = holder;
        left_list->tail = holder->prev;
        left_list->tail->next = NULL;
        left_list->head->prev = NULL;
        right_list->tail->next = NULL;
        right_list->head->prev = NULL;
    }
}

int main(void)
{
    int values[] = { 1, 3, 9, 2, 7, 5, 8, 6, 0, 4 };
    enum { NUM_VALUES = sizeof(values)/sizeof(values[0]) };
    list_t *list = list_construct();

    //dump_list(stdout, "Empty list", list);
    for (size_t i = 0; i < NUM_VALUES; i++)
    {
        node_t *node = node_construct(values[i]);
        list_insert_tail(list, node);
        //dump_list(stdout, "Inserting", list);
    }

    dump_list(stdout, "Before", list);
    list_sort_merge(list);
    dump_list(stdout, "After", list);

    list_destruct(list);

    return 0;
}

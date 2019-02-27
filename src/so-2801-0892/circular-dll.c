/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Circular Doubly-Linked List
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Product:        :PRODUCT:
*/

/* SO 2801-0892 */

/*TABSTOP=4*/

#include "posixver.h"
#include "circular-dll.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Circular_DLL
{
    const void   *data;
    Circular_DLL *next;
    Circular_DLL *prev;
};

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_circular_dll_c[];
const char jlss_id_circular_dll_c[] = "@(#)$Id$";
#endif /* lint */

static Circular_DLL *cdll_make_item(const void *data)
{
    Circular_DLL *item = (Circular_DLL *)malloc(sizeof(*item)); /*=C++=*/
    if (item != 0)
    {
        item->data = data;
        item->next = 0;
        item->prev = 0;
    }
    return item;
}

Circular_DLL *cdll_add_before(Circular_DLL *list, const void *data)
{
    Circular_DLL *item = cdll_make_item(data);
    if (item == 0)
        return 0;
    if (list == 0)
    {
        item->next = item->prev = item;
    }
    else
    {
        assert(list->next != 0 && list->prev != 0);
        item->next = list;
        item->prev = list->prev;
        list->prev = item;
        item->prev->next = item;
    }
    return item;
}

Circular_DLL *cdll_add_after(Circular_DLL *list, const void *data)
{
    Circular_DLL *item = cdll_make_item(data);
    if (item == 0)
        return 0;
    if (list == 0)
    {
        item->next = item->prev = item;
    }
    else
    {
        assert(list->next != 0 && list->prev != 0);
        item->prev = list;
        item->next = list->next;
        list->next = item;
        item->next->prev = item;
    }
    return item;
}

void cdll_apply(Circular_DLL *list, CDLL_Apply function, void *ctxt)
{
    if (list != 0)
    {
        Circular_DLL *item = list;
        do
        {
            (*function)(item->data, ctxt);
            item = item->next;
        } while (item != list);
    }
}

Circular_DLL *cdll_find(Circular_DLL *list, CDLL_Compare function, const void *data)
{
    if (list != 0)
    {
        Circular_DLL *item = list;
        do
        {
            if ((*function)(item->data, data))
                return item;
            item = item->next;
        } while (item != list);
    }
    return 0;
}

void cdll_destroy(Circular_DLL *list)
{
    if (list != 0)
    {
        Circular_DLL *item = list;
        do
        {
            assert(item != 0 && item->next != 0 && item->prev != 0);
            cdll_dump_item(stderr, "free", item);
            Circular_DLL *next = item->next;
            free(item);
            item = next;
        } while (item != list);
    }
}

Circular_DLL *cdll_remove(Circular_DLL *list)
{
    Circular_DLL *item = list;
    if (item != 0)
    {
        list = item->next;
        assert(item->prev != 0 && item->next != 0);
        item->prev->next = item->next;
        item->next->prev = item->prev;
        item->next = 0;
        item->prev = 0;
        item = list;
    }
    return item;
}

const void *cdll_data(Circular_DLL *list)
{
    const void *data = 0;
    if (list != 0)
        data = list->data;
    return data;
}

Circular_DLL *cdll_next(Circular_DLL *list)
{
    Circular_DLL *item = list;
    if (item != 0)
        item = item->next;
    return item;
}

Circular_DLL *cdll_prev(Circular_DLL *list)
{
    Circular_DLL *item = list;
    if (item != 0)
        item = item->prev;
    return item;
}

static void cdll_print_pointer(FILE *fp, const char *tag, const void *ptr)
{
    fprintf(fp, "%s0x%.8" PRIXPTR, tag, (uintptr_t)ptr);
}

void cdll_dump_item(FILE *fp, const char *tag, const Circular_DLL *item)
{
    fprintf(fp, "%s", tag);
    cdll_print_pointer(fp, ": item = ", item);
    if (item != 0)
    {
        cdll_print_pointer(fp, "; data = ", item->data);
        cdll_print_pointer(fp, "; next = ", item->next);
        cdll_print_pointer(fp, "; prev = ", item->prev);
    }
    putc('\n', fp);
    fflush(fp);
}

#ifdef TEST

/* NB: none of the test code dereferences a Circular_DLL pointer */

#include <string.h>
#include <unistd.h>

static void print_item(const void *data, void *ctxt)
{
    FILE *fp = (FILE *)ctxt;
    const char *info = (const char *)data;
    fprintf(fp, " %s", info);
}

static void print_cdll(const char *tag, Circular_DLL *list)
{
    printf("%s: ", tag);
    if (list == 0)
        printf(" <empty>");
    else
        cdll_apply(list, print_item, stdout);
    putchar('\n');
}

static int item_find(const void *vdata, const void *vword)
{
    const char *data = (const char *)vdata;     /*=C++=*/
    const char *word = (const char *)vword;     /*=C++=*/
    return(strcmp(data, word) == 0);
}

int main(void)
{
    const char *data[] = { "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx" };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };
    struct Inserter
    {
        const char *where;
        Circular_DLL *(*adder)(Circular_DLL *list, const void *data);
    } inserters[] =
    {
        { "Before", cdll_add_before },
        { "After",  cdll_add_after  },
    };
    Circular_DLL *list = 0;

    printf("Creation:\n");
    for (int i = 0; i < NUM_DATA; i++)
    {
        struct Inserter *ins = &inserters[i%2];
        printf("Push: %s - %s\n", data[i], ins->where);
        Circular_DLL *item = (*ins->adder)(list, data[i]);
        cdll_dump_item(stdout, "item", item);
        if (list == 0)
            list = item;
        print_cdll("List", list);
        print_cdll("Item", item);
    }

    printf("Access:\n");
    cdll_dump_item(stdout, "Next", cdll_next(list));
    cdll_dump_item(stdout, "Prev", cdll_prev(list));
    printf("Data: [%s]\n", (char *)cdll_data(list));

    printf("Removal:\n");
    Circular_DLL *item = list;
    list = cdll_remove(list);
    cdll_dump_item(stdout, "Gone", item);
    print_cdll("List", list);
    free(item);

    printf("Search:\n");
    for (int i = 0; i < NUM_DATA; i++)
    {
        printf("Find: %s\n", data[i]);
        Circular_DLL *item = cdll_find(list, item_find, data[i]);
        print_cdll("find", item);
    }

    /*
    ** If the data items on the list need to be destroyed, use
    ** cdll_apply() with a (cover for the) destructor as the function to
    ** be applied before calling cdll_destroy()
    */

    printf("Destruction:\n");
    cdll_destroy(list);

    printf("Finished!\n");
    return 0;
}

#endif /* TEST */

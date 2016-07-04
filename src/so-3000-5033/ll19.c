/* SO 30005033 */
/*
** Doubly-linked list management - code more complete than the question.
** It could be instructive to upgrade apply_backwards and apply_forwards
** so that they could be used by del_list.
*/
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct value value;

struct value
{
    value *prev;
    value *next;
    int value;
};

value *entry_head = NULL;
value *entry_tail = NULL;

static void ins_head(value *ent)
{
    assert(ent != NULL && ent->next == NULL && ent->prev == NULL);
    if (entry_head == NULL)
    {
        assert(entry_tail == NULL);
        entry_head = ent;
        entry_tail = ent;
        //ent->next = NULL;
        //ent->prev = NULL;
    }
    else
    {
        assert(entry_tail != NULL);
        ent->next = entry_head;
        ent->prev = NULL;
        entry_head->prev = ent;
        entry_head = ent;
    }
}

static void ins_tail(value *ent)
{
    assert(ent != NULL && ent->next == NULL && ent->prev == NULL);
    if (entry_tail == NULL)
    {
        assert(entry_head == NULL);
        entry_head = ent;
        entry_tail = ent;
        //ent->next = NULL;
        //ent->prev = NULL;
    }
    else
    {
        assert(entry_head != NULL);
        ent->next = NULL;
        ent->prev = entry_tail;
        entry_tail->next = ent;
        entry_tail = ent;
    }
}

/* insert ent after ref */
static void ins_after(value *ref, value *ent)
{
    assert(ref != NULL && ent != NULL);
    ent->prev = ref;
    ent->next = ref->next;
    if (ref->next != NULL)
        ref->next->prev = ent;
    ref->next = ent;
    if (ent->next == NULL)
        entry_tail = ent;
}

/* insert ent before ref */
static void ins_before(value *ref, value *ent)
{
    assert(ref != NULL && ent != NULL);
    ent->prev = ref->prev;
    ent->next = ref;
    if (ref->prev != NULL)
        ref->prev->next = ent;
    ref->prev = ent;
    if (ent->prev == NULL)
        entry_head = ent;
}

static void del_list(void)
{
    value *node = entry_head;
    while (node != NULL)
    {
        value *next = node->next;
        free(node);
        node = next;
    }
    entry_head = NULL;
    entry_tail = NULL;
}

static void prt_node(FILE *fp, const value *node)
{
    fprintf(fp, "Value: %d (node = 0x%.9" PRIXPTR "; prev = 0x%.9" PRIXPTR
            "; next = 0x%.9" PRIXPTR ")\n", node->value, (uintptr_t)node,
            (uintptr_t)node->prev, (uintptr_t)node->next);
}

static void chk_list(void)
{
    assert((entry_head == NULL && entry_tail == NULL) ||
           (entry_head != NULL && entry_tail != NULL));
    assert(entry_head == NULL || entry_head->next == NULL ||
           entry_head->next->prev == entry_head);
    assert(entry_tail == NULL || entry_tail->prev == NULL ||
           entry_tail->prev->next == entry_tail);
}

static void apply_forwards(void (*function)(value *node, void *data), void *data)
{
    value *node = entry_head;
    chk_list();
    while (node != NULL)
    {
        (*function)(node, data);
        node = node->next;
    }
}

static void apply_backwards(void (*function)(value *node, void *data), void *data)
{
    value *node = entry_tail;
    chk_list();
    while (node != NULL)
    {
        (*function)(node, data);
        node = node->prev;
    }
}

static void prt_apply(value *node, void *data)
{
    FILE *fp = (FILE *)data;
    prt_node(fp, node);
}

static void prt_forwards(const char *tag)
{
    chk_list();
    printf("Forwards: %s\n", tag);
    apply_forwards(prt_apply, stdout);
    printf("End of list.\n");
}

static void prt_backwards(const char *tag)
{
    chk_list();
    printf("Backwards: %s\n", tag);
    apply_backwards(prt_apply, stdout);
    printf("End of list\n");
}

static value *new_node(int val)
{
    value *node = malloc(sizeof(*node));
    if (node == 0)
    {
        fprintf(stderr, "Out of memory (%zu bytes requested)\n", sizeof(*node));
        exit(1);
    }
    node->value = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

int main(void)
{
    value *node1;

    prt_forwards("Empty");

    node1 = new_node(23);
    ins_tail(node1);
    prt_backwards("Tail 23");

    node1 = new_node(29);
    ins_head(node1);
    prt_forwards("Head 29");

    value *node2 = new_node(31);
    ins_head(node2);
    prt_forwards("Head 31");

    node1 = new_node(37);
    ins_after(node2, node1);
    prt_backwards("37 after 31");

    node1 = new_node(41);
    ins_after(node2, node1);
    prt_forwards("41 after 31");

    node1 = new_node(43);
    ins_before(node2, node1);
    prt_forwards("43 before 31");

    node1 = new_node(47);
    ins_before(node2, node1);
    prt_forwards("47 before 31");

    del_list();
    prt_backwards("Empty");

    return 0;
}

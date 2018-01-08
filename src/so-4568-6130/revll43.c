/* SO 4568-6130 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    int data;
    struct node *prev;
    struct node *next;
};

static struct node *reverse(struct node **head_ref)
{
    struct node *current = *head_ref;
    struct node *old_curr = 0;
    while (current != 0)
    {
        struct node *old_next = current->next;
        struct node *old_prev = current->prev;
        current->prev = old_next;
        current->next = old_prev;
        old_curr = current;
        current = old_next;
    }
    *head_ref = old_curr;
    return current;
}

static struct node *create(int key, int data)
{
    struct node *p = malloc(sizeof(*p));
    if (p != 0)
    {
        p->key = key;
        p->data = data;
        p->next = 0;
        p->prev = 0;
    }
    return p;
}

static struct node *insert_head(struct node *head, int key, int data)
{
    struct node *n = create(key, data);
    assert(n != 0);
    if (head != 0)
        head->prev = n;
    n->next = head;
    return n;
}

static void print_list(const char *tag, struct node *head)
{
    printf("%s: [", tag);
    const char *pad = "";
    while (head != 0)
    {
        printf("%s(%d => %d)", pad, head->key, head->data);
        pad = ",";
        head = head->next;
    }
    printf("]\n");
}

static void free_list(struct node *head)
{
    while (head != 0)
    {
        struct node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    for (int size = 0; size < 10; size++)
    {
        struct node *list = 0;
        for (int i = 0; i < size; i++)
            list = insert_head(list, i, (7 * i + 4 + size) % 10);
        print_list("New list", list);
        reverse(&list);
        print_list("Rev list", list);
        free_list(list);
    }
    return 0;
}


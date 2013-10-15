/* http://stackoverflow.com/q/19214293 Unable to modify global variable in C */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

void insert_node(struct node **head, int n);
void print_list(struct node *head);
void free_list(struct node **phead);
void test_insert(struct node **head, int n);

int main(void)
{
    struct node *head = NULL;
    free_list(&head);

    for (int i = 1; i < 5; i++)
        test_insert(&head, i*i);
    test_insert(&head, 0);
    test_insert(&head, 7);
    for (int i = 1; i < 6; i++)
        test_insert(&head, i*i - 3);
    test_insert(&head, 7);
    test_insert(&head, 0);

    print_list(head);
    free_list(&head);
    return 0;
}

void test_insert(struct node **head, int n)
{
    printf("%2d:", n);
    insert_node(head, n);
    print_list(*head);
}

void print_list(struct node *head)
{
    while (head != NULL)
    {
        printf(" %2i", head->data);
        head = head->link;
    }
    putchar('\n');
}

void free_list(struct node **phead)
{
    assert(phead != NULL);
    struct node *head = *phead;
    while (head != NULL)
    {
        struct node *next = head->link;
        free(head);
        head = next;
    }
    *phead = 0;
}

void insert_node(struct node **phead, int n)
{
    struct node *node = malloc(sizeof(*node));

    if (node == NULL)
    {
        fprintf(stderr, "Failed to allocate node for %d\n", n);
        exit(1);
    }

    node->data = n;

    struct node *head = *phead;
    struct node *next = head;
    struct node *prev = NULL;

    while (next != NULL && n >= next->data)
    {
        if (n == next->data)
        {
            free(node);
            return;
        }
        prev = next;
        next = next->link;
    }

    node->link = next;
    if (prev == NULL)
        *phead = node;
    else
        prev->link = node;
}


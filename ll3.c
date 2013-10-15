#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

void insert_node(struct node **head, int n);
void print_list(struct node *head);

int main(void)
{
    struct node *head = NULL;

    for (int i = 1; i < 5; i++)
        insert_node(&head, i*i);
    insert_node(&head, 0);
    insert_node(&head, 7);
    for (int i = 1; i < 5; i++)
        insert_node(&head, i*i - 3);
    insert_node(&head, 7);
    insert_node(&head, 0);

    print_list(head);
    return 0;
}

void print_list(struct node *head)
{
    while (head != NULL)
    {
        printf("%i ", head->data);
        head = head->link;
    }
    putchar('\n');
}

void insert_node(struct node **phead, int n)
{
    struct node N = {n, NULL};
    struct node *node = malloc(sizeof(*node));
    struct node *next, *prev;
    int prev_data = 0;
    struct node *head = *phead;

    if (node == 0)
    {
        fprintf(stderr, "Failed to allocate node for %d\n", n);
        exit(1);
    }
    *node = N;

    if (head == NULL)
    {
        printf("Case 1: create %d\n", node->data);
        *phead = node;
    }
    else if (n < head->data)
    {
        printf("Case 2: insert %d\n", node->data);
        node->link = head;
        *phead = node;
    }
    else
    {
        next = head;

        while (next != NULL)
        {
            if (n == next->data)
            {
                printf("Case 3: double %d == %d\n", n, next->data);
                free(node);
                return;
            }
            prev = next;        // save the current element
            next = next->link;  // look at the next element
        }

        if (n > prev->data)
        {
            printf("Case 4: append %d\n", node->data);
            prev->link = node;
            return;
        }

        // case five: N.data is in between list elements:

        next = head;

        printf("Case 5: middle %d\n", node->data);
        while (next != NULL)
        {
            prev_data = next->data; // save the current element
            prev = next;            // save pointer to current element
            next = next->link;      // look at the next element

            if ((n > prev_data) && (n < next->data))
            {
                prev->link = node;
                node->link = next;
                return;
            }
        }
    }
}


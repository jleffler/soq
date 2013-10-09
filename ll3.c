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

int main(void)
{
    struct node *head = NULL;

    for (int i = 1; i < 5; i++)
        insert_node(&head, i*i);
    insert_node(&head, 0);
    insert_node(&head, 0);
    insert_node(&head, 7);
    insert_node(&head, 7);

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
        printf("Case 1: create (%d)\n", n);
        // case one: list is empty - point head to N, and set N.link to NULL
        *phead = node;
    }
    else if (n < head->data)
    {
        printf("Case 2: before (%d)\n", n);
        // case two: n is less than first element in the list:
        node->link = head;
        *phead = node;
    }
    else
    {
        prev = NULL;
        next = head;

        while (next != NULL)
        {
            if (n == next->data)
            {
                // case three: N.data is equal to existing element, do nothing:
                printf("Case 3: double (%d)\n", n);
                free(node);
                return;
            }
            //if (n < next->data)
            //    break;
            prev = next;        // save the current element
            next = next->link;  // look at the next element
        }

        assert(prev != NULL);
        if (n > prev->data)
        {
            // case four: N.data is greater than last element:
            printf("Case 4: append (%d)\n", n);
            prev->link = node;
            return;
        }

        // case five: N.data is in between list elements:

        next = head;

        printf("Case 5: insert (%d)\n", n);
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


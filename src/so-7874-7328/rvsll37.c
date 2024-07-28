/* SO 7874-7328 */
/* Reverse elements in singly-linked list */

/*
** Closely based on answer by user24714692.
** Test code independently corrected by JL in the same way that the OP
** corrected their code.  Avoid dereferencing a null pointer on failed
** memory allocation.
*/
#include <stdio.h>
#include <stdlib.h>
//#include <inttypes.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

static node *reverse(node *head);
static node *create_node(int n);
static void display(node *head);
static node *add_node(node *head, node *node);
static void destroy(node *head);

static node *create_node(int n)
{
    node *new = (node *)malloc(sizeof(node));
    if (new == NULL)
    {
        fprintf(stderr, "Failed to allocate %zu bytes of memory\n", sizeof(node));
        exit(EXIT_FAILURE);
    }
    new->number = n;
    new->next = NULL;
    return new;
}

static void display(node *head)
{
    while (head != NULL)
    {
        //printf("%s(): 0x%12" PRIXPTR ": %i\n", __func__, (uintptr_t)head, head->number);
        printf("%i\t", head->number);
        head = head->next;
    }
    printf("\n");
}

static node *reverse(node *head)
{
    node *prev = NULL;
    node *curr = head;
    while (curr != NULL)
    {
        node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

static node *add_node(node *head, node *node)
{
    node->next = head;
    return node;
}

static void destroy(node *head)
{
    while (head != NULL)
    {
        //printf("%s(): 0x%12" PRIXPTR ": %i\n", __func__, (uintptr_t)head, head->number);
        node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    int nums[] = { 2, 3, 1, 4, 0, 9, 7 };
    enum { NUM_NUMS = sizeof(nums) / sizeof(nums[0]) };

    for (int r = 0; r <= NUM_NUMS; r++)
    {
        node *head = NULL;
        for (int i = 0; i < r; i++)
            head = add_node(head, create_node(nums[i]));
        printf("List length: %d\n", r);
        display(head);
        head = reverse(head);
        display(head);
        putchar('\n');
        destroy(head);
    }

    return 0;
}

/* SO 7874-7328 */
/* Reverse elements in doubly-linked list */

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#undef PRIXADDR
#define PRIXADDR "0x%.12" PRIXPTR

typedef struct node
{
    int number;
    struct node *next;
    struct node *prev;
} node;

static node *reverse(node *head);
static node *create_node(int n);
static void display(node *head);
static node *add_node_before(node *head, node *node);
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
    new->prev = NULL;
    return new;
}

static inline void pr_node_info(const char *func, const node *item)
{
    printf("%s(): " PRIXADDR " (N = " PRIXADDR ", P = " PRIXADDR "): %d\n",
           func, (uintptr_t)item, (uintptr_t)item->next, (uintptr_t)item->prev, item->number);
}

static void display(node *head)
{
    while (head != NULL)
    {
        pr_node_info(__func__, head);
        //printf("%i\t", head->number);
        head = head->next;
    }
    printf("\n");
}

/*
** Before: P[PP : PV : C] - C[P : CV : N] - N[C : NV : NN]
** After   P[PP : PV : C] - C[N : CV : P] - N[C : NV : NN]
*/

static node *reverse(node *head)
{
    node *curr = head;
    node *prev = NULL;
    node *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        prev = curr->prev;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    return prev;
}

static node *add_node_before(node *head, node *node)
{
    assert(node != NULL);
    node->next = head;
    if (head != NULL)
    {
        node->prev = head->prev;
        head->prev = node;
    }
    return node;
}

static void destroy(node *head)
{
    while (head != NULL)
    {
        pr_node_info(__func__, head);
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
            head = add_node_before(head, create_node(nums[i]));
        printf("List length: %d\n", r);
        display(head);
        head = reverse(head);
        display(head);
        putchar('\n');
        destroy(head);
    }

    return 0;
}

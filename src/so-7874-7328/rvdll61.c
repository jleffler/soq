/* SO 7874-7328 */
/* Reverse elements in doubly-linked list */

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#undef PRIXADDR
#define PRIXADDR "0x%.12" PRIXPTR

#undef PR_NODE_INFO
#ifdef PRINT_NODE_INFO
#define PR_NODE_INFO(tag, node) pr_node_info(tag, node)
#else
#define PR_NODE_INFO(tag, node) ((void)0)
#endif /* PRINT_NODE_INFO */

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

#ifdef PRINT_NODE_INFO
static inline void pr_node_info(const char *tag, const node *item)
{
    printf("%s: " PRIXADDR, tag, (uintptr_t)item);
    if (item != NULL)
        printf(" (P = " PRIXADDR ", N = " PRIXADDR "): %d",
               (uintptr_t)item->prev, (uintptr_t)item->next, item->number);
    putchar('\n');
}
#endif /* PRINT_NODE_INFO */

static void display(node *head)
{
    while (head != NULL)
    {
#ifdef PRINT_NODE_INFO
        PR_NODE_INFO(__func__, head);
#else
        printf("%i\t", head->number);
#endif /* PRINT_NODE_INFO */
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
    while (curr != NULL)
    {
        node *next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    return prev;
}

/*
** W = new, H = head, P = prev
** B:  W[-- : NV : --] - H[-- : HV : HN]
** A:  W[-- : NV : H ] - H[W  : HV : HN]
** B:  P[PP : PV : H ] - W[-- : NV : --] - H[P : HV : HN]
** A:  P[PP : PV : W ] - W[P  : NV : H ] - H[W : HV : HN]
*/

static node *add_node_before(node *head, node *node)
{
    assert(node != NULL);
    node->next = head;
    if (head != NULL)
    {
        if (head->prev != NULL)
            head->prev->next = node;
        node->prev = head->prev;
        head->prev = node;
    }
    return node;
}

static void destroy(node *head)
{
    while (head != NULL)
    {
        PR_NODE_INFO(__func__, head);
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
        printf("List length: %d\n", r);
        node *head = NULL;
        node *prev = NULL;
        for (int i = 0; i < r; i++)
        {
            if (i % 3 != 0)
            {
                if (prev == head)
                    head = prev = add_node_before(prev, create_node(nums[i]));
                else
                    prev = add_node_before(prev, create_node(nums[i]));
            }
            else
            {
                head = add_node_before(head, create_node(nums[i]));
                if (prev == NULL)
                    prev = head;
            }
        }
        printf("Forwards\n");
        display(head);
        head = reverse(head);
        printf("Reversed\n");
        display(head);
        printf("Destroy\n");
        destroy(head);
        putchar('\n');
    }

    return 0;
}

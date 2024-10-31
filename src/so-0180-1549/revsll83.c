/* SO 0180-1549: Reverse a linked list */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

static void print_list(Node *root)
{
    while (root != 0)
    {
        printf("%c ", root->data);
        root = root->next;
    }
    printf("\n");
}

typedef void (*SLL_Apply)(Node *node, void *data);

static void sll_dummy(Node *node, void *data)
{
    assert(node != 0 && data != 0);
    printf("Print  data: %c (%c)\n", node->data, (*(char *)data)++);
}

static void sll_modify(Node *node, void *data)
{
    node->data = toupper(node->data);
    printf("Modify data: %c (%c)\n", node->data, --*(char *)data);
}

static Node *reverse(Node *root, SLL_Apply apply, void *thunk)
{
    Node *new_root = 0;
    while (root != 0)
    {
        (*apply)(root, thunk);
        Node *next = root->next;
        root->next = new_root;
        new_root = root;
        root = next;
    }
    return new_root;
}

int main(void)
{
    Node d = { 'd', 0 };
    Node c = { 'c', &d };
    Node b = { 'b', &c };
    Node a = { 'a', &b };
    char t = 'A';

    Node *root = &a;
    print_list(root);
    root = reverse(root, sll_dummy, &t);
    print_list(root);
    root = reverse(root, sll_modify, &t);
    print_list(root);

    return 0;
}

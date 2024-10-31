/* SO 0180-1549: Reverse a linked list */
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

static Node *reverse(Node *root)
{
    Node *new_root = 0;
    while (root != 0)
    {
        printf("Act on data: %c\n", root->data);
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

    Node *root = &a;
    print_list(root);
    root = reverse(root);
    print_list(root);
    root = reverse(root);
    print_list(root);

    return 0;
}

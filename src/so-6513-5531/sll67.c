#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    int data;
    Node *next;
};

static
Node *getNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

static
// function to delete all the nodes from the list
// that are greater than the specified value x
Node *deleteGreaterNodes(Node* head_ref, int x)
{
    Node **link = &head_ref; // Point to the pointer to the first node.
    Node *cur;

    while ((cur = *link) != NULL) {
        if (cur->data > x) {
            // The current node needs to be deleted from the list.
            // Change the link pointing to the current node to point to the next node.
            *link = cur->next;
            // Delete the current node.
            free(cur);
        } else {
            // The current node is to be kept on the list.
            // Get a pointer to the link to the next node.
            link = &cur->next;
        }
    }
    return head_ref;
}

#if 0
static
Node *deleteGreaterNodes(Node *head_ref, int x)
{
    Node *temp = head_ref, *prev;

    if (temp != NULL && temp->data > x)
    {
        head_ref = temp->next;
        free(temp);
        temp = head_ref;
    }

    while (temp != NULL)
    {
        while (temp != NULL && temp->data <= x)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
            return head_ref;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
    return head_ref;
}
#endif /* 0 */

static
void printList(Node *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main(void)
{
    Node *head = getNode(7);

    head->next = getNode(3);
    head->next->next = getNode(4);
    head->next->next->next = getNode(8);
    head->next->next->next->next = getNode(5);
    head->next->next->next->next->next = getNode(1);

    printf("Original List: ");
    printList(head);
    putchar('\n');

    int x = 3;
    Node *root = deleteGreaterNodes(head, x);

    printf("\nModified List: ");
    printList(root);
    putchar('\n');

    return 0;
}

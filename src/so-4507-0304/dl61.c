/* SO 4507-0304 Mk II */
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node *prev;
    Node *next;
};

static Node *removeNode(Node *head, int d)
{
    Node *curr = head;
    while (curr != NULL)
    {
        if (curr->data != d)
            curr = curr->next;
        else
        {
            if (curr->prev != NULL)
                curr->prev->next = curr->next;
            else
                head = curr->next;
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            free(curr);
            return head;
        }
    }
    return head;
}

static Node *addNodeAtHead(Node *head, int d)
{
    Node *item = malloc(sizeof(*item));
    if (item != 0)
    {
        item->next = head;
        item->prev = NULL;
        if (head != 0)
            head->prev = item;
        item->data = d;
    }
    return item;
}

static void dumpList(const char *tag, Node *head)
{
    printf("%s:", tag);
    while (head != 0)
    {
        printf(" %d", head->data);
        head = head->next;
    }
    putchar('\n');
}

int main(void)
{
    Node *head = 0;
    head = addNodeAtHead(head, 23);
    head = addNodeAtHead(head, 43);
    head = addNodeAtHead(head, 73);
    head = addNodeAtHead(head, 13);
    head = addNodeAtHead(head, 33);
    dumpList("Completed", head);

    head = removeNode(head, 33);
    dumpList("Remove 33", head);
    head = removeNode(head, 23);
    dumpList("Remove 23", head);
    head = removeNode(head, 13);
    dumpList("Remove 13", head);
    head = removeNode(head, 34);
    dumpList("Remove 34", head);
    head = removeNode(head, 43);
    dumpList("Remove 43", head);
    head = removeNode(head, 73);
    dumpList("Remove 73", head);
    head = removeNode(head, 37);
    dumpList("Remove 37", head);

    return 0;
}

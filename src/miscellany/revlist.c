#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

static void add(int n)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == 0)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    temp->data = n;
    temp->next = head;
    head = temp;
}

static void print(const char *tag)
{
    struct node *temp = head;
    int nbytes = printf("%s: ", tag);
    int taglen = nbytes;
    while (temp != NULL)
    {
        nbytes += printf("  %d", temp->data);
        if (nbytes > 70)
            nbytes = printf("\n%*s", taglen, "");
        temp = temp->next;
    }
    putchar('\n');
}

static void reverse(void)
{
    struct node *curr = head;
    struct node *prev = NULL;
    while (curr != NULL)
    {
        struct node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

static void destroy(void)
{
    struct node *curr = head;
    while (curr != NULL)
    {
        struct node *next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void)
{
    add(1003001);
    add(2003002);
    add(3003003);
    add(4003004);
    add(5003005);
    add(6003001);
    add(7003002);
    add(8003003);
    add(9003004);
    add(1003005);
    print("Forward");
    reverse();
    print("Reverse");
    destroy();
    return 0;
}

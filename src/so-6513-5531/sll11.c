#include <stdio.h>
#include <stdlib.h>

typedef struct tagSingleLinkedList
{
    int data;
    struct tagSingleLinkedList *next;
} SLLI;

static void printList(SLLI *head);
static SLLI *addItemToEnd(SLLI *head, int dataToAdd);
static SLLI *addItemToFront(SLLI *head, int dataToAdd);
static SLLI *reverseList(SLLI *head);
static void freeList(SLLI *head);

int main(void)
{
    SLLI *head = NULL;
    int i;

    for (i = 0; i < 10; i++)
        head = addItemToEnd(head, i);

    printf("Print list...\n");
    printList(head);
    printf("----------------------------------\n");

    SLLI *revd = reverseList(head);

    printf("Reversed list:\n");
    printList(revd);

    freeList(head);
    freeList(revd);

    return 0;
}

SLLI *addItemToEnd(SLLI *head, int dataToAdd)
{
    SLLI *last;

    SLLI *pItem = (SLLI *) malloc(sizeof(SLLI));
    if (NULL == pItem)
    {
        printf("Cannot allocate memory for the new item!!!\n");
        exit(1);
    }

    pItem->data = dataToAdd;
    pItem->next = NULL;

    if (NULL == head)
        return pItem;

    last = head;
    while (NULL != last->next)
        last = last->next;

    last->next = pItem;

    return head;
}

static SLLI *reverseList(SLLI *head)
{
    SLLI *newHead = NULL;

    while (head != NULL)
    {
        newHead = addItemToFront(newHead, head->data);
        head = head->next;
    }
    return newHead;
}

static SLLI *addItemToFront(SLLI *head, int dataToAdd)
{
    SLLI *pItem = (SLLI *) malloc(sizeof(SLLI));
    if (NULL == pItem)
    {
        fprintf(stderr, "Cannot allocate memory for the new item!!!\n");
        exit(1);
    }

    pItem->data = dataToAdd;
    pItem->next = head;

    return pItem;
}

static void printList(SLLI *head)
{
    while (head != NULL)
    {
        printf("%d\n", head->data);
        head = head->next;
    }
}

static void freeList(SLLI *head)
{
    while (head != NULL)
    {
        SLLI *next = head->next;
        free(head);
        head = next;
    }
}

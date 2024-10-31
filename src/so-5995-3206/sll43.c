/* SO 5995-3206 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int info;
    struct node *link;
} Tnode;

static void DeleteNode(Tnode *node)
{
    free(node);
}

static Tnode *listDeleteOdd(Tnode *list)
{
    if (list == NULL)
        return NULL;

    if (list->info % 2 == 1)
    {
        Tnode *node = list->link;
        DeleteNode(list);
        return listDeleteOdd(node);
    }
    Tnode *node = listDeleteOdd(list->link);
    list->link = node;
    return list;
}

static void listFree(Tnode *list)
{
    while (list != NULL)
    {
        Tnode *next = list->link;
        DeleteNode(list);
        list = next;
    }
}

static Tnode *listAdd(Tnode *list, int info)
{
    Tnode *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "failed to allocate memory for a node\n");
        exit(EXIT_FAILURE);
    }
    node->info = info;
    node->link = list;
    return node;
}

static void listPrint(const char *tag, Tnode *list)
{
    const char *pad = " ";
    printf("%s:", tag);
    while (list != NULL)
    {
        printf("%s%d", pad, list->info);
        list = list->link;
        pad = " -> ";
    }
    putchar('\n');
}

int main(void)
{
    Tnode *list = NULL;

#if 0
    /* Pick'n'choose which values go in the list where */
    list = listAdd(list, 5);
    list = listAdd(list, 4);
    list = listAdd(list, 3);
    list = listAdd(list, 7);
    list = listAdd(list, 3);
    list = listAdd(list, 2);
    list = listAdd(list, 1);
    list = listAdd(list, 0);
    list = listAdd(list, 0);
    list = listAdd(list, 0);
#else
    /* Alternatively, use a loop to read numbers form standard input */
    int number;
    while (scanf("%d", &number) == 1)
        list = listAdd(list, number);
#endif

    listPrint("Before:", list);
    list = listDeleteOdd(list);
    listPrint("After: ", list);

    listFree(list);

    return 0;
}

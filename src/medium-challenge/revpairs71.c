#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List
{
    int   datum;
    List *next;
};

static List *read_list(void)
{
    List *head = NULL;
    List *tail = NULL;
    int datum;
    while (scanf("%d", &datum) == 1)
    {
        List *next = malloc(sizeof(*next));
        if (next == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        if (head == NULL)
            head = tail = next;
        next->datum = datum;
        next->next  = NULL;
        tail->next = next;
        tail = next;
    }
    return head;
}

static void print_list(const char *tag, List *list)
{
    printf("%-8s", tag);
    while (list != NULL)
    {
        printf(" -> %d", list->datum);
        list = list->next;
    }
    putchar('\n');
}

static void free_list(List *list)
{
    while (list != NULL)
    {
        List *next = list->next;
        free(list);
        list = next;
    }
}

static List *reverse_pairs(List *list)
{
    List head = { 0, list };
    List *prev = &head;
    List *curr = list;
    List *next;

    while (curr != NULL && (next = curr->next) != NULL)
    {
        prev->next = next;
        curr->next = next->next;
        next->next = curr;
        prev = curr;
        curr = curr->next;
    }

    return head.next;
}

int main(void)
{
    List *list = read_list();
    print_list("Before:", list);
    List *revp = reverse_pairs(list);
    print_list("After:", revp);
    free_list(revp);
}

/* Code based on SO 5173-7998 */
/* Reverse singly linked list */
/* SO 5173-7998 did not ask about reversing a linked list */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct student
{
    int ID;
    int age;
    struct student *next;
};

struct student *head = 0;

static void create_list(int ID, int age)
{
    struct student *node = (struct student *)malloc(sizeof(struct student));
    if (node == 0)
    {
        fprintf(stderr, "Failed to allocate %zu bytes\n", sizeof(*node));
        exit(EXIT_FAILURE);
    }
    node->ID = ID;
    node->age = age;
    node->next = 0;
    if (head != 0)
        node->next = head;
    head = node;
}

static void print_list(void)
{
    int counter = 0;
    for (struct student *node = head; node != 0; node = node->next)
    {
        printf("-- Node %2d: ID = %.5d, age = %d\n", ++counter, node->ID, node->age);
    }
    printf("-- No. of nodes in the list = %d\n\n", counter);
}

static void delete_list(int position)
{
    int counter = 0;
    struct student *node = head;
    struct student *prev = 0;
    while (node != 0 && ++counter != position)
    {
        prev = node;
        node = node->next;
    }

    if (node == NULL)
        return;
    if (prev == NULL)
    {
        assert(node == head);
        struct student *old = head;
        head = head->next;
        free(old);
    }
    else
    {
        assert(node != head);
        prev->next = node->next;
        free(node);
    }
}

static struct student *reverse_sll(struct student *begin)
{
    if (begin == 0)
        return begin;
    struct student *tail = begin;
    struct student *prev = 0;
    while (tail->next != 0)
    {
        /* Carefully confusing - but head is not used because of shadowing */
        struct student *next = tail->next;
        tail->next = prev;
        prev = tail;
        tail = next;
    }
    tail->next = prev;
    return tail;
}

static void reverse_list(void)
{
    head = reverse_sll(head);
}

int main(void)
{
    create_list(10102, 19);
    print_list();
    create_list(23147, 20);
    print_list();
    create_list(30001, 21);
    print_list();
    create_list(47721, 18);
    print_list();
    create_list(59286, 20);
    print_list();
    reverse_list();
    print_list();
    delete_list(2);
    print_list();
    delete_list(3);
    print_list();
    delete_list(2);
    print_list();
    delete_list(1);
    print_list();
    delete_list(1);
    print_list();

    create_list(10102, 19);
    print_list();
    reverse_list();
    print_list();
    delete_list(1);
    print_list();

    reverse_list();
    print_list();

    return 0;
}

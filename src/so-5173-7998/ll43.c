/* SO 5173-7998 */
#include <stdio.h>
#include <stdlib.h>

struct student
{
    int ID;
    int age;
    struct student *next;
};

struct student *head = 0;
struct student *first = 0;
struct student *temp = 0;

static void create_list(int ID, int age)
{
    static int counter = 1;
    head = (struct student *)malloc(sizeof(struct student));
    head->ID = ID;
    head->age = age;
    if (first != 0)
    {
        temp->next = head;
        temp = head;
    }
    else
    {
        first = temp = head;
    }

    counter++;
}

static void print_list(void)
{
    temp->next = 0;

    temp = first;
    int counter = 1;
    first = 0;
    while (temp != 0)
    {
        printf("-- Node %d: ID = %d, age = %d\n", counter++, temp->ID, temp->age);
        temp = temp->next;
    }
    printf("-- No. of nodes in the list = %d\n\n", counter - 1);
}

static void delete_list(struct student **head, int position)
{
    if (*head == NULL)
        return;

    struct student* temp = *head;

    if (position == 0)
    {
        *head = temp->next;   
        temp = 0;               
        return;
    }

    for (int i = 0; temp != NULL && i<position - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    struct student *next = temp->next->next;

    temp->next=0;  
    temp->next = next;  
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
    delete_list(&head, 2);
    print_list();
    delete_list(&head, 3);
    print_list();
    delete_list(&head, 2);
    print_list();
    delete_list(&head, 1);
    print_list();
    delete_list(&head, 1);
    print_list();
    return 0;
}

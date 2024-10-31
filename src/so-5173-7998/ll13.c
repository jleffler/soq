/* SO 5173-7998 */
#include <stdio.h>
#include <malloc.h>
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

void create_list()
{
    static int counter = 1;
    head = (struct student *)malloc(sizeof(struct student));
    printf("Enter the student no. %d ID\n",counter);
    scanf_s("%d", &head->ID);
    printf("Enter the student no. %d age\n", counter);
    scanf_s("%d", &head->age);
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

void read_list()
{
    temp->next = 0;

    temp = first;
    int counter = 1;
    first = 0;
    while (temp != 0)
    {
        printf("------------------Node number : %d---------------\n", counter);
        printf("The Student id is : %d\n", temp->ID);
        printf("The Student age is : %d\n", temp->age);
        counter++;
        temp = temp->next;
    }
    printf("NULL\n");
    printf("-------------No. of nodes in the list = %d\n------------------", counter);
}

void delete_list(struct student **head, int position)
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

void main()
{

    int choice = 0;
    while (choice != 99)
    {
        printf("Please enter a choice from the list:\n");
        printf("1- Create Node\n");
        printf("2- Read List\n");
        printf("3- Delete Node\n");
        printf("99- Exit\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1:
            create_list();
            break;
        case 2:
            read_list();
            break;
        case 3:
            delete_list(&head,2);
            break;
        }
    }

}

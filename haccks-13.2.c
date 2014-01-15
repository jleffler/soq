#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REMIND 50   /* maximum number of reminders */
#define MSG_LEN 60      /* max length of reminder message */

typedef struct Reminder
{
    int day;
    int hour;
    int minute;
    char reminder[MSG_LEN];
} Reminder;

static int reminder_cmp(void const *v1, void const *v2)
{
    Reminder const *r1 = v1;
    Reminder const *r2 = v2;
    if (r1->day < r2->day)
        return -1;
    else if (r1->day > r2->day)
        return +1;
    else if (r1->hour < r2->hour)
        return -1;
    else if (r1->hour > r2->hour)
        return +1;
    else if (r1->minute < r2->minute)
        return -1;
    else if (r1->minute > r2->minute)
        return +1;
    else
        return strcmp(r1->reminder, r2->reminder);
}

int read_line(char str[], int n);

static void print_reminders(char const *tag, Reminder const *rem, size_t num)
{
    printf("%s (%zu):\n", tag, num);
    for (size_t i = 0; i < num; i++)
        printf("[%zu]: %2d  %2d:%.2d  %s\n", i, rem[i].day,
               rem[i].hour, rem[i].minute, rem[i].reminder);
}

int main(void)
{
    Reminder reminders[MAX_REMIND];
    int num_remind = 0;

    /* Sorting by time. */
    for (int i = 0; i < MAX_REMIND; i++)
    {
        Reminder new_rem;
        printf("Enter day, time and reminder: ");
        if (scanf("%2d %2d:%2d", &new_rem.day, &new_rem.hour, &new_rem.minute) != 3)
            break;
        read_line(new_rem.reminder, MSG_LEN);
        printf("Read: %2d  %2d:%.2d  %s\n", new_rem.day, new_rem.hour, new_rem.minute, new_rem.reminder);

        int j;
        for (j = 0; j < num_remind; j++)
        {
            if (reminder_cmp(&new_rem, &reminders[j]) < 0)
                break;
        }
        for (int k = num_remind; k > j; k--)
            reminders[k] = reminders[k-1];

        reminders[j] = new_rem;
        num_remind++;
    }

    /* Already in sorted order! */
    print_reminders("Before", reminders, num_remind);

    /* Sort once more, just to be sure */
    qsort(reminders, num_remind, sizeof(Reminder), reminder_cmp);

    /* Still in sorted order */
    print_reminders("After", reminders, num_remind);

    printf("\nDay Reminder\n");
    for (int i = 0; i < num_remind; i++)
        printf("%2d  %2d:%.2d  %s\n", reminders[i].day,
               reminders[i].hour, reminders[i].minute, reminders[i].reminder);

    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;

    while ((ch = getchar()) != EOF && isspace(ch))
        ;
    if (ch != EOF)
        ungetc(ch, stdin);
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (i < n)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

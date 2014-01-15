#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50   /* maximum number of reminders */
#define MSG_LEN 60      /* max length of reminder message */

int read_line(char str[], int n);

int main(void)
{
    char reminders[MAX_REMIND][MSG_LEN + 8];
    char day_str[3], time_str[7], msg_str[MSG_LEN + 1];
    char sorted_day_str[MAX_REMIND][3];
    char temp[MSG_LEN + 8];
    int day, i, j, num_remind = 0;
    int hr, min;

    /* Sorting by time. */
    for ( ; ; )
    {
        if (num_remind == MAX_REMIND)
        {
            printf("-- No space left --\n");
            break;
        }

        printf("Enter day, time and reminder: ");
        scanf("%2d", &day);
        if (day == 0)
            break;
        scanf("%2d:%2d", &hr, &min);
        sprintf(day_str, "%2d", day);
        sprintf(time_str, "%3d:%.2d", hr, min);
        read_line(msg_str, MSG_LEN);

        // printf(" %d\n", day);
        // printf(" %s\n", day_str);

        for (i = 0; i < num_remind; i++)
            if (strcmp(time_str, reminders[i]) < 0)
                break;
        for (j = num_remind; j > i; j--)
        {
            strcpy(reminders[j], reminders[j - 1]);
            strcpy(sorted_day_str[j], sorted_day_str[j - 1]);
        }

        strcpy(reminders[i], time_str);
        strcat(reminders[i], msg_str);
        strcpy(sorted_day_str[i], day_str);

        num_remind++;
    }

    /* Concatenate sorted_day_str to reminders string. */
    for (i = 0; i < num_remind; i++)
    {
        strcpy(temp, reminders[i]);
        strcpy(reminders[i], sorted_day_str[i]);
        strcat(reminders[i], temp);
    }

    /* Sorting by day */
    for (int i = 0; i < num_remind - 1; i++)
    {
        for (int j = 0; j < num_remind - 1 - i; j++)
        {
            if (strcmp(reminders[j], reminders[j + 1]) > 0)
            {
                strcpy(temp, reminders[j]);
                strcpy(reminders[j], reminders[j + 1]);
                strcpy(reminders[j + 1], temp);
            }
        }
    }

    printf("\nDay Reminder\n");
    for (i = 0; i < num_remind; i++)
    {
        printf(" %s\n", reminders[i]);
    }

    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}

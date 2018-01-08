/* SO 4638-6600 */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *getMessage(void *arg);

static char message[4096];
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t condition1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER;

static int who = 1;

struct Control
{
    const char *filename;
    pthread_cond_t *this_cond;
    pthread_cond_t *that_cond;
    int this_who;
    int that_who;
};

int main(void)
{
    struct Control info[] =
    {
        { "Student1", &condition1, &condition2, 1, 2 },
        { "Student2", &condition2, &condition1, 2, 1 },
    };
    pthread_t id0;
    pthread_t id1;

    pthread_create(&id0, NULL, getMessage, &info[0]);
    pthread_create(&id1, NULL, getMessage, &info[1]);

    pthread_join(id0, NULL);
    pthread_join(id1, NULL);

    for (int j = 0; j < 1001 && message[j] != '\0'; j++)
        printf("%c ", message[j]);
    putchar('\n');

    return 0;
}

static void *getMessage(void *arg)
{
    assert(arg != NULL);
    struct Control *cp = (struct Control *)arg;
    FILE *fp = fopen(cp->filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", cp->filename);
        exit(EXIT_FAILURE);
    }

    size_t howManyChars;
    char *placeHolderChars;
    int count = 1;

    while (count < 501)
    {
        placeHolderChars = NULL;
        if (getline(&placeHolderChars, &howManyChars, fp) == -1)
            break;
        int len = strlen(placeHolderChars);
        pthread_mutex_lock(&lock);
        printf("T%d(%d): [%.*s] [%s]\n", cp->this_who, count, len - 1, placeHolderChars, message);
        if (strcmp(placeHolderChars, "0\n") == 0)
        {
            printf("T%d: %d's turn - 1\n", cp->this_who, cp->that_who);
            //pthread_mutex_lock(&lock);
            pthread_cond_signal(cp->that_cond);
            who = cp->that_who;
            while (who == cp->that_who)
            {
                pthread_cond_wait(cp->this_cond, &lock);
            }
            /* My turn - add character? */
            printf("T%d: should add a character here?\n", cp->this_who);
            //pthread_mutex_unlock(&lock);
            free(placeHolderChars);
        }
        else
        {
            //pthread_mutex_lock(&lock);
            if (who == cp->this_who)
            {
                if (strlen(placeHolderChars) > 0)
                    placeHolderChars[1] = '\0';
                printf("T%d: add '%c'\n", cp->this_who, placeHolderChars[0]);
                strcat(message, placeHolderChars);
                free(placeHolderChars);
                who = cp->that_who;
                pthread_cond_signal(cp->that_cond);
            }
            else
                printf("T%d: %d's turn - 2 - can't happen!\n", cp->this_who, cp->that_who);
            //pthread_mutex_unlock(&lock);
        }
        pthread_mutex_unlock(&lock);
        count++;
    }

    fclose(fp);
    return 0;
}


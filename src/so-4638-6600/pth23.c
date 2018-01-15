/* SO 4638-6600 */
#include "posixver.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void *getMessage1(void *arg);
extern void *getMessage2(void *arg);

static char message[4096];

int main(void)
{
    pthread_t id1;
    pthread_t id2;

    pthread_create((&id1), NULL, getMessage1, NULL);
    pthread_create((&id2), NULL, getMessage2, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    for (int j = 0; j < 1001 && message[j] != '\0'; j++)
        printf("%c ", message[j]);
    putchar('\n');

    return 0;
}

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t condition1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER;

static int who = 1;

void *getMessage1(void *arg)
{
    assert(arg == NULL);
    const char filename[] = "Student1";
    FILE *studentOne = fopen(filename, "r");
    if (studentOne == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t howManyChars;
    char *placeHolderChars;
    int count = 1;

    while (count < 501)
    {
        placeHolderChars = NULL;
        if (getline(&placeHolderChars, &howManyChars, studentOne) == -1)
            break;
        printf("M1(%d): [%s]\n", count, placeHolderChars);
        pthread_mutex_lock(&lock);
        if (strcmp(placeHolderChars, "0\n") == 0)
        {
            printf("M1: Two's turn - 1\n");
            pthread_cond_signal(&condition2);
            who = 2;
            while (who == 2)
            {
                pthread_cond_wait(&condition1, &lock);
            }
            free(placeHolderChars);
        }
        else
        {
            if (who == 1)
            {
                if (strlen(placeHolderChars) > 0)
                {
                    placeHolderChars[1] = '\0';
                }
                strcat(message, placeHolderChars);
                free(placeHolderChars);
                who = 2;
                pthread_cond_signal(&condition2);
            }
            else
                printf("M1: Two's turn - 2\n");
        }
        pthread_mutex_unlock(&lock);
        count++;
    }

    fclose(studentOne);
    return 0;
}

void *getMessage2(void *arg)
{
    assert(arg == NULL);
    const char filename[] = "Student2";
    FILE *studentTwo = fopen(filename, "r");
    if (studentTwo == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t howManyChars;
    char *placeHolderChars;
    int count = 0;

    while (count < 501)
    {
        placeHolderChars = NULL;
        if (getline(&placeHolderChars, &howManyChars, studentTwo) == -1)
            break;
        printf("M2(%d): [%s]\n", count, placeHolderChars);
        pthread_mutex_lock(&lock);
        if (strcmp(placeHolderChars, "0\n") == 0)
        {
            printf("M2: One's turn - 1\n");
            pthread_cond_signal(&condition1);
            who = 1;
            while (who == 1)
            {
                pthread_cond_wait(&condition2, &lock);
            }
            free(placeHolderChars);
        }
        else
        {
            if (who == 2)
            {
                if (strlen(placeHolderChars) > 0)
                {
                    placeHolderChars[1] = '\0';
                }
                strcat(message, placeHolderChars);
                free(placeHolderChars);
                who = 1;
                pthread_cond_signal(&condition1);
            }
            else
                printf("M2: One's turn - 2\n");
        }
        pthread_mutex_unlock(&lock);
        count++;
    }

    fclose(studentTwo);
    return 0;
}

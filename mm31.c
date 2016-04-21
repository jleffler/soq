#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct accounting
{
    char **people;
    char **descriptions;
    float *amountMoney;
    int *payers;
    int participants;
    int payments;
};

struct accounting *accountTable;

extern int trip_add_person(const char *name);
extern int trip_find_person(const char *name);
extern void trip_shutdown(void);
extern void trip_initialize(void);
extern int trip_add_expense(const char *descr, float amount, int payer);

void trip_initialize(void)
{
    accountTable = malloc(sizeof(struct accounting));
    assert(accountTable != 0);
    accountTable->people = malloc(sizeof(char *));
    accountTable->descriptions = malloc(sizeof(char *));
    /*accountTable->amountMoney = malloc(sizeof(float *)); // Repeated - leak! */
    accountTable->amountMoney = malloc(sizeof(float *));
    accountTable->payers = malloc(sizeof(int *));
    accountTable->participants = 0;
    accountTable->payments = 0;
    assert(accountTable->people != 0 && accountTable->descriptions != 0 &&
           accountTable->amountMoney != 0 && accountTable->payers != 0);
}

void trip_shutdown(void)
{
    for (int i = 0; i < accountTable->participants; i++)
        free(accountTable->people[i]);
    for (int i = 0; i < accountTable->payments; i++)
        free(accountTable->descriptions[i]);
    free(accountTable->amountMoney);
    free(accountTable->payers);
    free(accountTable->people);
    free(accountTable->descriptions);
    free(accountTable);
}

int trip_add_person(const char *name)
{
    size_t new_num = accountTable->participants + 1;
    char **new_acct = realloc(accountTable->people, new_num * sizeof(*accountTable->people));
    if (new_acct == 0)
    {
        fprintf(stderr, "Out of memory (%zu bytes requested)\n", new_num * sizeof(*accountTable->people));
        return -1;
    }
    accountTable->people = new_acct;
    /*accountTable->people[accountTable->participants] = malloc(sizeof(char *)); // Leak with strdup! */
    accountTable->people[accountTable->participants] = strdup(name);
    return accountTable->participants++;
}

int trip_find_person(const char *name)
{
    for (int i = 0; i < accountTable->participants; i++)
    {
        if (!strcmp(accountTable->people[i], name))
        {
            return i;
        }
    }
    return -1;
}

int trip_add_expense(const char *descr, float amount, int payer)
{
    if (payer < 0 || payer > accountTable->participants)
    {
        return 0;
    }
    size_t new_num = accountTable->payments + 1;
    char **new_desc = realloc(accountTable->descriptions, new_num * sizeof(*accountTable->descriptions));
    if (new_desc == 0)
    {
        fprintf(stderr, "Out of memory (%zu bytes requested)\n", new_num * sizeof(*accountTable->descriptions));
        return 0;
    }
    accountTable->descriptions = new_desc;
    float *new_money = realloc(accountTable->amountMoney, new_num * sizeof(*accountTable->amountMoney));
    if (new_money == 0)
    {
        fprintf(stderr, "Out of memory (%zu bytes requested)\n", new_num * sizeof(*accountTable->amountMoney));
        return 0;
    }
    accountTable->amountMoney = new_money;
    int *new_payers = realloc(accountTable->payers, new_num * sizeof(*accountTable->payers));
    if (new_payers == 0)
    {
        fprintf(stderr, "Out of memory (%zu bytes requested)\n", new_num * sizeof(*accountTable->payers));
        return 0;
    }
    accountTable->payers = new_payers;
    accountTable->descriptions[accountTable->payments] = strdup(descr);
    accountTable->amountMoney[accountTable->payments] = amount;
    accountTable->payers[accountTable->payments] = payer;
    accountTable->payments++;
    return 1;
}

int main(void)
{
    trip_initialize();
    int who_1 = trip_add_person("Original Poster");
    int who_2 = trip_add_person("Question Answerer");
    int who_3 = trip_add_person("Antibody");
    if (who_1 == -1 || who_2 == -1 || who_3 == -1)
        fprintf(stderr, "Oops - Adding people!\n");
    if (trip_add_expense("Deposit", 200.0, who_1) == 0 ||
        trip_add_expense("Deposit", 200.0, who_2) == 0 ||
        trip_add_expense("Deposit", 200.0, who_3) == 0)
        fprintf(stderr, "Oops - adding expenses!\n");

    trip_shutdown();
}


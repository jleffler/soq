#include <stdio.h>

typedef struct
{
    char name[3];
    int population;
} State;

enum { MAX_STATES = 10 };

int main(void)
{
    State myStates[MAX_STATES];

    int i, j;

    for (i = 0; i < MAX_STATES; i++)
    {
        if (scanf("%2s %d\n", myStates[i].name, &myStates[i].population) != 2)
            break;
    }

    for (j = 0; j < i; j++)
    {
        if (myStates[j].population >= 10)
        {
            printf("%s %d\n", myStates[j].name, myStates[j].population);
        }
    }

    return 0;
}

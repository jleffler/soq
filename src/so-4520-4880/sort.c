#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[3];
    int population;
} State;

static int cmp(const void *v1, const void *v2)
{
    const State *s1 = (State *)v1;
    const State *s2 = (State *)v2;
    return strcmp(s1->name, s2->name);
}

enum { MAX_STATES = 10 };

int main(void)
{
    State myStates[MAX_STATES];

    int count = 0;

    for (int i = 0; i < MAX_STATES; i++)
    {
        if (scanf("%s %d", myStates[i].name, &myStates[i].population) != 2)
            break;
        count++;
    }

    qsort(myStates, count, sizeof(myStates[0]), cmp);

    for (int i = 0; i < count; i++)
    {
        printf("%s\n", myStates[i].name);
    }

    return 0;
}

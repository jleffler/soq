/* Demonstrating a FAM of fixed size strings */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VLA
{
    int num;
    char vla[][32];
} VLA;

int main(void)
{
    int num = 10;
    VLA *vla = malloc(sizeof(VLA) + num * sizeof(vla->vla[0]));
    assert(vla != 0);       // Lousy test mechanism!
    for (int i = 0; i < num; i++)
        strcpy(vla->vla[i], "Arbitrary medium length string");
    vla->num = num;

    for (int i = 0; i < vla->num; i++)
        printf("%d: [%s]\n", i, vla->vla[i]);

    free(vla);
    return 0;
}

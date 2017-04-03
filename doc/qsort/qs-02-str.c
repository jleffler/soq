#include <stdio.h>
#include <stdlib.h>

/* For sorting an array of char */
static int cmpchr(const void *v1, const void *v2)
{
    return(*(unsigned char *)v1 - *(unsigned char *)v2);
}

int main(void)
{
    char str0[] = "a quick brown fox jumps over the lazy dog";
    enum { NUM_STR0 = sizeof(str0) / sizeof(str0[0]) - 1 }; // Not sorting the null byte!

    printf("str0 - before: [%s]\n", str0);
    qsort(str0, NUM_STR0, sizeof(str0[0]), cmpchr);
    printf("str0 - after:  [%s]\n", str0);

    return 0;
}

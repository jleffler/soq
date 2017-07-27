#include <stddef.h>
#include <stdio.h>

struct fam1 { double d; char c; char fam[]; };

int main(void)
{
    printf("sizeof(struct fam1)        = %zu\n", sizeof(struct fam1));
    printf("offsetof(struct fam1, fam) = %zu\n", offsetof(struct fam1, fam));
    return 0;
}

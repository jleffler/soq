#include <stdio.h>

struct fam
{
    int     fam_number;
    char    fam_name[16];
    double  fam_values[];
};

struct no_fam
{
    int     fam_number;
    char    fam_name[16];
};

int main(void)
{
    /* On a Mac, x86_64 in 64-bit, sizeof(fam) == 24 and sizeof(no_fam) == 20 */
    /* On a Mac, x86_64 in 32-bit, sizeof(fam) == 20 and sizeof(no_fam) == 20 */
    printf("sizeof(struct    fam) = %zu\n", sizeof(struct fam));
    printf("sizeof(struct no_fam) = %zu\n", sizeof(struct no_fam));
    return 0;
}


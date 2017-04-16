#include <stdio.h>

struct fam
{
    int     fam_number;
    char    fam_name[16];
    double  fam_values[];
};

extern struct fam family;

struct fam family = { 3, "Partridge", { 2.45, 3.91, 6.72 } };

static void dump_fam(const char *tag, const struct fam *fam)
{
    printf("FAM: %s\n", tag);
    printf("Name: %s; number = %d\n", fam->fam_name, fam->fam_number);
    const char *pad = "";
    int w = (fam->fam_number > 10) ? 2 : 1;
    int i;
    for (i = 0; i < fam->fam_number; i++)
    {
        printf("%s(%*d: %.2f)", pad, w, i, fam->fam_values[i]);
        pad = ", ";
        if (i % 5 == 4)
        {
            putchar('\n');
            pad = "";
        }
    }
    if (i % 5 != 0)
        putchar('\n');
}

int main(void)
{
    static struct fam famine =
    {
        23, "Isaacson",
        {
            // random -n 23 -f -F '%4:2f' -- 10.00 99.99 | commalist -b '        ' -w -n 10
            29.66, 85.42, 32.17, 84.64, 24.65, 46.16, 47.66, 51.68, 51.81, 57.55,
            38.42, 32.60, 16.64, 43.62, 24.81, 26.70, 81.07, 26.05, 51.24, 61.95,
            10.71, 50.12, 12.66,
        }
    };

    dump_fam("External", &family);
    dump_fam("Internal", &famine);
    return 0;
}


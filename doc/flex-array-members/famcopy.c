#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fam
{
    int     fam_number;
    char    fam_name[16];
    double  fam_values[];
};

static inline void safer_copy(char *dst, size_t dst_size, const char *src)
{
    strncpy(dst, src, dst_size - 1);
    dst[dst_size-1] = '\0';
}

static int dbl_cmp(const void *vp1, const void *vp2)
{
    double d1 = *(double *)vp1;
    double d2 = *(double *)vp2;
    if (d1 < d2)
        return -1;
    else if (d1 > d2)
        return +1;
    else
        return 0;
}

static struct fam *new_fam(const char *name, int num, double *values)
{
    struct fam *new_fam = malloc(sizeof(*new_fam) + num * sizeof(new_fam->fam_values[0]));
    if (new_fam != 0)
    {
        new_fam->fam_number = num;
        safer_copy(new_fam->fam_name, sizeof(new_fam->fam_name), name);
        for (int i = 0; i < num; i++)
            new_fam->fam_values[i] = values[i];
    }
    return new_fam;
}

static void dump_fam(const char *tag, const struct fam *fp)
{
    printf("FAM: %s\n", tag);
    printf("Size = %d; Name = %s\n", fp->fam_number, fp->fam_name);
    for (int i = 0; i < fp->fam_number; i++)
        printf("  %d: %6.2f\n", i, fp->fam_values[i]);
}

static inline void sort_fam(struct fam *fp)
{
    qsort(fp->fam_values, fp->fam_number, sizeof(fp->fam_values[0]), dbl_cmp);
}

int main(void)
{
    double v1[] = { 0.51, 0.09, 0.58, 0.45, 0.38, 0.72, 0.36, 0.58 };
    enum { NUM_V1 = sizeof(v1) / sizeof(v1[0]) };
    double v2[] = { 8.80, 7.92, 4.40, 4.13, 7.16 };
    enum { NUM_V2 = sizeof(v2) / sizeof(v2[0]) };

    /* Should check that f1, f2 are not null */
    struct fam *f1 = new_fam("Sample 103-2", NUM_V1, v1);
    struct fam *f2 = new_fam("Sample 195-A", NUM_V2, v2);

    if (f1 != NULL && f2 != NULL)
    {
        dump_fam("Before: f1", f1);
        dump_fam("Before: f2", f2);
        sort_fam(f1);
        sort_fam(f2);
        dump_fam("Sorted: f1", f1);
        dump_fam("Sorted: f2", f2);

        /* Note that a structure copy does nothing with the FAM */
        *f1 = *f2;
        dump_fam("After: f1", f1);
        dump_fam("After: f2", f2);
    }

    /* One advantages of FAM over other techniques is the ease of freeing */
    /* Even if either or both allocations failed, the calls to free are OK */
    free(f1);
    free(f2);
    return 0;
}


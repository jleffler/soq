/* SO 4515-2411 - 2017-07-17 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printStr(char **data, size_t num);
static void printDbl(double *data, size_t num);
static void printInt(int *data, size_t num);
static void print2Ds(char (*data)[6], size_t num);

int compareInt(const void *a, const void *b);
int compareDbl(const void *a, const void *b);
int compareStr(const void *a, const void *b);   // array of char *
int compare2Ds(const void *a, const void *b);   // array of char[6]

void *maxElement(void *arr, size_t number, size_t size, int (*comp)(const void *, const void *));

void *maxElement(void *arr, size_t number, size_t size, int (*comp)(const void *, const void *))
{
    char *base = arr;
    void *max = base;

    for (size_t i = 1; i < number; i++)
    {
        if (comp(&base[i * size], max) > 0)
            max = &base[i * size];
    }

    return max;
}

int compareInt(const void *a, const void *b)
{
    int i1 = *(int *)a;
    int i2 = *(int *)b;

    return(i1 > i2);
}

int compareDbl(const void *a, const void *b)
{
    double d1 = *(double *)a;
    double d2 = *(double *)b;

    return(d1 > d2);
}

int compareStr(const void *a, const void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    int rc = 0;
    if (strcmp(s1, s2) > 0)
        rc = 1;
    return rc;
}

int compare2Ds(const void *a, const void *b)
{
    char (*s1)[6] = (char (*)[6])a;
    char (*s2)[6] = (char (*)[6])b;

    int rc = 0;
    if (strcmp(*s1, *s2) > 0)
        rc = 1;
    return rc;
}

int main(void)
{
    int     i_array[4] = { 11, 3, 7, 0 };
    double  d_array[4] = { 1.23, 6.57, 9.89, 11.56 };
    char   *s_array[5] = { "jess", "ron", "tom", "mia", "alex" };
    char    t_array[5][6] = { "Jess", "Ron", "Tom", "Mia", "Alex" };

    printInt(i_array, 4);
    int i_max = *(int *)maxElement(i_array, 4, sizeof(i_array[0]), &compareInt);
    printDbl(d_array, 4);
    double d_max = *(double *)maxElement(d_array, 4, sizeof(d_array[0]), &compareDbl);
    printStr(s_array, 5);
    char *s_max = *(char **)maxElement(s_array, 5, sizeof(s_array[0]), &compareStr);
    print2Ds(t_array, 5);
    char *t_max = *(char (*)[6])maxElement(t_array, 5, sizeof(t_array[0]), &compare2Ds);
    printf("Max integer: %d\n", i_max);
    printf("Max double:  %.2f\n", d_max);
    printf("Max string:  [%s]\n", s_max);
    printf("Max string:  [%s]\n", t_max);
    return 0;
}

static void printStr(char **data, size_t num)
{
    const char *pad = "Strings:";
    for (size_t i = 0; i < num; i++)
    {
        printf("%s %s", pad, data[i]);
        pad = ",";
    }
    putchar('\n');
}

static void print2Ds(char (*data)[6], size_t num)
{
    const char *pad = "Strings:";
    for (size_t i = 0; i < num; i++)
    {
        printf("%s %s", pad, data[i]);
        pad = ",";
    }
    putchar('\n');
}

static void printDbl(double *data, size_t num)
{
    const char *pad = "Doubles:";
    for (size_t i = 0; i < num; i++)
    {
        printf("%s %.2f", pad, data[i]);
        pad = ",";
    }
    putchar('\n');
}

static void printInt(int *data, size_t num)
{
    const char *pad = "Integers:";
    for (size_t i = 0; i < num; i++)
    {
        printf("%s %d", pad, data[i]);
        pad = ",";
    }
    putchar('\n');
}

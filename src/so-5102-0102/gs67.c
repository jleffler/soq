/* SO 5102-0102 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sort(void *arr, int size, int sizeType, int (*f)(void *, void *));

/* Changed (simplified) function signature */
static void gSortAll(int n, int m, int (*cmp)(void *, void *), ...)
{
    void *item;
    va_list param;

    /* How many arrays? */
    va_start(param, cmp);
    size_t num_arrays = 0;
    while ((item = va_arg(param, void *)) != 0)
        num_arrays++;
    va_end(param);

    if (num_arrays == 0)
        return;

    void *arr = malloc(num_arrays * n * m);
    if (arr == 0)
        return;

    /* Copy data into allocated array */
    va_start(param, cmp);
    void *data = arr;
    while ((item = va_arg(param, void *)) != 0)
    {
        memmove(data, item, n * m);
        data = (char *)data + n * m;
    }
    va_end(param);

    sort(arr, n * num_arrays, m, cmp);

    /* Copy data from allocated array */
    va_start(param, cmp);
    data = arr;
    while ((item = va_arg(param, void *)))
    {
        memmove(item, data, n * m);
        data = (char *)data + n * m;
    }
    va_end(param);

    free(arr);
}

static int cmpInt(void *a, void *b)
{
    return *(int *)a > *(int *)b;
}

static void swap(void *p, void *q, int size)
{
    char *pt = (char *)p;
    char *qt = (char *)q;
    char c;
    while (size--)
    {
        c = *pt;
        *pt = *qt;
        *qt = c;
        pt++;
        qt++;
    }
}

static void sort(void *arr, int size, int sizeType, int (*f)(void *, void *))
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (f((char *)arr + j * sizeType, (char *)arr + j * sizeType + sizeType) > 0)
            {
                swap((char *)arr + j * sizeType, (char *)arr + j * sizeType + sizeType,
                     sizeType);
            }
        }
    }
}

/* Non-generic code */
static void dump_array(const char *tag, size_t size, int data[size])
{
    printf("%s (%zu):  ", tag, size);
    for (size_t i = 0; i < size; i++)
        printf("%5d", data[i]);
    putchar('\n');
}

int main(void)
{
    int a[] = {17, 2, 7, 8, 1};
    int b[] = {3, 6, 5, 14, 11};
    int c[] = {12, 9, 10, 1, 4};

    printf("Before\n");
    dump_array("A", 5, a);
    dump_array("B", 5, b);
    dump_array("C", 5, c);

    gSortAll(sizeof(a) / sizeof(a[0]), sizeof(a[0]), *cmpInt, a, b, c, NULL);

    printf("After\n");
    dump_array("A", 5, a);
    dump_array("B", 5, b);
    dump_array("C", 5, c);

    /* random -n 12 10 99 | commalist -B 4 -w -W3 -n 12 -b 'int w[] = { ' -T ' };' */
    int w[] = {  86,  86,  48,  40,  39,  29,  69,  71,  30,  15,  46,  19, };
    int x[] = {  21,  43,  11,  85,  82,  81,  41,  46,  33,  32,  15,  43, };
    int y[] = {  91,  19,  82,  33,  25,  83,  36,  85,  75,  65,  37,  57, };
    int z[] = {  39,  61,  65,  83,  26,  82,  30,  81,  30,  34,  22,  82, };

    printf("Before\n");
    dump_array("W", 12, w);
    dump_array("X", 12, x);
    dump_array("Y", 12, y);
    dump_array("Z", 12, z);

    gSortAll(sizeof(w) / sizeof(w[0]), sizeof(w[0]), *cmpInt,
             (void *)w, (void *)x, (void *)y, (void *)z, (void *)NULL);

    printf("After\n");
    dump_array("W", 12, w);
    dump_array("X", 12, x);
    dump_array("Y", 12, y);
    dump_array("Z", 12, z);

    return 0;
}

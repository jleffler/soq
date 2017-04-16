/* SO 4335-0957 */
#include <stdio.h>
#include <stdlib.h>

void sort_arr(int num, int **list);
void print_arr(int num, int **list);

int main(void)
{
    int arr1[] = { 3, 9, 6, 7 };
    int arr2[] = { 2, 5, 5 };
    int arr3[] = { 0 };
    int arr4[] = { 1, 6 };
    int arr5[] = { 4, 5, 6, 2, 1 };
    int arr6[] = { 4, 2, 7, 1, 5 };
    int arr7[] = { 4, 2, 5, 1, 6 };
    int arr8[] = { 9, 12, 19, 18, 10, 28, 27, 15, 15, 27 };
    int arr9[] = { 4, 2, 5, 1, 5 };

    int *list[] = { arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9 };
    enum { NUM_LIST = sizeof(list) / sizeof(list[0]) };

    printf("Unsorted:\n");
    print_arr(NUM_LIST, list);
    sort_arr(NUM_LIST, list);
    printf("Sorted:\n");
    print_arr(NUM_LIST, list);
    return 0;
}

static int cmpintasc(const void *v1, const void *v2)
{
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;
    return (i1 > i2) - (i1 < i2);
}

static inline int min(int x, int y) { return (x < y) ? x : y; }

static int cmpintptrasc(const void *v1, const void *v2)
{
    int *i1 = *(int **)v1;
    int *i2 = *(int **)v2;
    int max = min(i1[0], i2[0]) + 1;
    for (int i = 1; i < max; i++)
    {
        if (i1[i] != i2[i])
            return (i1[i] > i2[i]) - (i1[i] < i2[i]);
    }
    return (i1[0] > i2[0]) - (i1[0] < i2[0]);
}

#if 0
static int cmpintptrasc(const void *v1, const void *v2)
{
    int *i1 = *(int **)v1;
    int *i2 = *(int **)v2;
    return (i1[0] > i2[0]) - (i1[0] < i2[0]);
}
#endif

void sort_arr(int num, int **list)
{
    /* Sort each array in turn */
    for (int k = 0; k < num; k++)
        qsort(&list[k][1], list[k][0], sizeof(list[k][0]), cmpintasc);
    /* Sort the whole list */
    qsort(list, num, sizeof(list[0]), cmpintptrasc);
}

void print_arr(int num, int **list)
{
    for (int k = 0; k < num; k++)
    {
        printf("%d: [%d]  ", k, list[k][0]);
        for (int c = 1; c < (list[k][0] + 1); c++)
            printf("%d ", list[k][c]);
        printf("\n");
    }
}

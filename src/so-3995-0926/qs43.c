#include <stdio.h>

// Swapping algorithm
static inline
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void dump_list(const char *tag, int *ptr, int left, int right)
{
    printf("%15s [%d..%d]: ", tag, left, right);
    for (int i = left; i <= right; i++)
        printf(" %3d", ptr[i]);
    putchar('\n');
}

// Partitioning algorithm
static
int partition(int *L, int left, int right)
{
    int pivot = left;
    int p_val = L[pivot];

    while (left < right)
    {
        while (L[left] <= p_val)
            left++;
        while (L[right] > p_val)
            right--;
        if (left < right)
            swap(&L[left], &L[right]);
    }
    swap(&L[pivot], &L[right]);
    return right;
}

// Quicksort recursion
static
void quicksort(int *L, int start, int end)
{
    if (start >= end)
        return;
    //dump_list("PRE-PARTITION", L, start, end);
    int splitPoint = partition(L, start, end);
    //dump_list("POST-PARTITION", L, start, end);
    //printf("Split point: %d\n", splitPoint);
    quicksort(L, start, splitPoint - 1);
    quicksort(L, splitPoint + 1, end);
}

int main(void)
{
    int myList[] = {12, 43, -16, 0, 2, 5, 1, 13, 2, 2, -1};
    dump_list("UNSORTED LIST", myList, 0, 9);
    quicksort(myList, 0, 9);
    dump_list("SORTED LIST", myList, 0, 9);
}

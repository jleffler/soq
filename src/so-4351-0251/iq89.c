/* SO 4351-0251 */
/* C implementation QuickSort */
#include <stdio.h>
#include <stdlib.h>

// A utility function to swap two elements
static inline void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
static int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
static void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* Function to print an array */
static void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
int main(void)
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array:\n");
    printArray(arr, n);
    quickSort(arr, 0, n-1);
    printf("Sorted array:\n");
    printArray(arr, n);

    enum { ALT_SIZE = 20 };
    int alt[ALT_SIZE];
    for (int i = 0; i < ALT_SIZE; i++)
        alt[i] = rand() % 100;
    printf("Unsorted array:\n");
    printArray(alt, ALT_SIZE);
    quickSort(alt, 0, ALT_SIZE-1);
    printf("Sorted array:\n");
    printArray(alt, ALT_SIZE);

    enum { BIG_SIZE = 40 };
    int big[BIG_SIZE];
    for (int i = 0; i < BIG_SIZE; i++)
        big[i] = rand() % 100;
    printf("Unsorted array:\n");
    printArray(big, BIG_SIZE);
    quickSort(big, 0, BIG_SIZE-1);
    printf("Sorted array:\n");
    printArray(big, BIG_SIZE);

    return 0;
}

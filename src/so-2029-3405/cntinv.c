/* SO 2029-3405 - Counting inversions */
/* Code from: http://www.geeksforgeeks.org/counting-inversions/ */

#include <stdio.h>
#include <stdlib.h>

static int MergeSort(int arr[], int temp[], int left, int right);
static int Merge(int arr[], int temp[], int left, int mid, int right);

/* Sorts input array and return the number of inversions in the unsorted array */
static int CountInversions1(int arr[], int array_size)
{
    int temp[array_size];
    int count = MergeSort(arr, temp, 0, array_size - 1);
    return count;
}

/* An auxiliary recursive function that sorts the input array and
   returns the number of inversions in the array. */
static int MergeSort(int arr[], int temp[], int left, int right)
{
    int mid, inv_count = 0;
    if (right > left)
    {
        /* Divide the array into two parts and call MergeSort() and Merge()
           for each of the parts */
        mid = (right + left)/2;

        /* Inversion count will be sum of inversions in left-part and in
           right-part and number of inversions in merging */
        inv_count += MergeSort(arr, temp, left, mid);
        inv_count += MergeSort(arr, temp, mid+1, right);

        /* Merge the two parts*/
        inv_count += Merge(arr, temp, left, mid+1, right);
    }
    return inv_count;
}

/* Merge two sorted arrays and return inversion count in the arrays.*/
static int Merge(int arr[], int temp[], int left, int mid, int right)
{
    int inv_count = 0;
    int i = left;   /* i is index for left subarray */
    int j = mid;    /* j is index for right subarray */
    int k = left;   /* k is index for resultant merged subarray */

    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            /* this is tricky -- see above explanation/diagram for Merge()*/
            inv_count += (mid - i);
        }
    }

    /* Copy the remaining elements of left subarray to temp */
    while (i <= mid - 1)
        temp[k++] = arr[i++];

    /* Copy the remaining elements of right subarray to temp */
    while (j <= right)
        temp[k++] = arr[j++];

    /* Copy back the merged elements to original array */
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

/* O(N*N) - slow on large arrays */
static int CountInversions2(int arr[], int n)
{
    int inv_count = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (arr[i] > arr[j])
                inv_count++;
        }
    }

    return inv_count;
}

#include <time.h>
#include <string.h>
#define WRAPPED_HEADER "timer.h"
#include "wraphead.h"

static int *generate(int n)
{
    int *a = (int *)malloc(n * sizeof(*a));    /*=C++=*/
    if (a != 0)
    {
        for (int i = 0; i < n; i++)
            a[i] = rand();
    }
    return a;
}

static int *copy(int *a, int n)
{
    int *b = (int *)malloc(n * sizeof(*b));    /*=C++=*/
    if (b != 0)
        memmove(b, a, n * sizeof(*b));
    return b;
}

/* Driver program to test above functions */
int main(void)
{
    // Performance cross-over is between 100 and 200 (around 150)
    for (int i = 100; i < 200; i += 10)
    //for (int i = 100; i < 100000; i *= 2)
    {
        int *a1 = generate(i);
        int *a2 = copy(a1, i);

        Clock clk1;
        clk_init(&clk1);
        clk_start(&clk1);
        int c1 = CountInversions1(a1, i);
        clk_stop(&clk1);

        Clock clk2;
        clk_init(&clk2);
        clk_start(&clk2);
        int c2 = CountInversions2(a2, i);
        clk_stop(&clk2);

        char buff1[32];
        char buff2[32];

        printf("n = %6d MS C1 = %12d  T1 = %16s\n", i, c1, clk_elapsed_us(&clk1, buff1, sizeof(buff1)));
        printf("n = %6d NL C2 = %12d  T2 = %16s\n", i, c2, clk_elapsed_us(&clk2, buff2, sizeof(buff2)));
        free(a1);
        free(a2);
    }
    return 0;
}


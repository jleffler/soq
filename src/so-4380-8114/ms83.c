#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>   // gettimeofday()
#include <unistd.h>     // fork()
#include <sys/wait.h>   // wait()

#define N 100

struct Sort
{
    int *data;
    int  lo;
    int  hi;
};

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
static
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
static
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

static
void *mergeSort2(void *args)
{
    struct Sort *newargs = args;
    int *data = newargs->data;
    int l = newargs->lo;
    int r = newargs->hi;

    pthread_t thread1, thread2;
    int ans1, ans2;

    if (l < r)
    {
        int m = (r + l) / 2;
        struct Sort newArgs1 = {data, l, m};
        struct Sort newArgs2 = {data, m + 1, r};
        ans1 = pthread_create(&thread1, NULL, mergeSort2, &newArgs1);
        ans2 = pthread_create(&thread2, NULL, mergeSort2, &newArgs2);
        if (ans1 != 0 || ans2 != 0)
            exit(1);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        merge(data, l, m, r);
    }
    return 0;
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
static
void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

static void print_timestamp(void)
{
    time_t now = time(0);
    struct tm *utc = gmtime(&now);
    char iso8601[32];
    strftime(iso8601, sizeof(iso8601), "%Y-%m-%d  %H:%M:%S", utc);
    printf("%s\n", iso8601);
}

/* Driver program to test above functions */
int main(void)
{
    int min = -1000, max = 1000;
    enum { ARRAY_SIZE = 500 };
    int arr[ARRAY_SIZE], arr2[ARRAY_SIZE], arr3[ARRAY_SIZE];
    int i, r;
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int id1, id2;
    struct Sort args = { arr3, 0, arr_size - 1};
    struct timeval tvalBefore, tvalAfter;
    struct timeval tvalBefore1, tvalAfter1;
    // Threads init
    pthread_t thread1;
    int ans1;

    srand(time(NULL));

    for (i = 0; i < arr_size; i++)
    {
        r = rand() % (max - min + 1);
        arr[i] = r;
        arr2[i] = r;
        arr3[i] = r;
    }
    printf("Given array is \n");
    printArray(arr, arr_size);
    fflush(stdout);

    if ((id1 = fork()) == 0)
    {
        printf("Child1: \n");
        gettimeofday(&tvalBefore, NULL);
        mergeSort(arr2, 0, arr_size - 1);
        gettimeofday(&tvalAfter, NULL);
        printArray(arr2, arr_size);
        print_timestamp();

        printf("Time in microseconds for sorting CHILD 1: %ld microseconds\n",
               ((tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L
                + tvalAfter.tv_usec) - tvalBefore.tv_usec);
    }
    else if ((id2 = fork()) == 0)
    {
        printf("Child2: \n");
        gettimeofday(&tvalBefore1, NULL);
        ans1 = pthread_create(&thread1, NULL, mergeSort2, &args);
        if (ans1 == 0)
            pthread_join( thread1, NULL );
        gettimeofday(&tvalAfter1, NULL);
        print_timestamp();
        printArray(arr3, arr_size);
        printf("Time in microseconds for sorting CHILD 2: %ld microseconds\n",
               ((tvalAfter1.tv_sec - tvalBefore1.tv_sec) * 1000000L
                + tvalAfter1.tv_usec) - tvalBefore1.tv_usec);
    }
    else
    {
        wait(0);
        wait(0);
        printf("Parent:\n");
        gettimeofday(&tvalBefore, NULL);
        mergeSort(arr, 0, arr_size - 1);
        gettimeofday(&tvalAfter, NULL);
        printArray(arr, arr_size);
        print_timestamp();

        printf("Time in microseconds for sorting Parent: %ld microseconds\n",
               ((tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L
                + tvalAfter.tv_usec) - tvalBefore.tv_usec);
    }
    return 0;
}

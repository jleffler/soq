#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
static int partition(int *A, int start, int end);

static
void generateDescendingArray(int *arr, int n) {

    for(int i = n - 1; i >= 0; i--) {
       arr[n-i-1] = rand() % n;
    }
}

static
void quickSort(int *A, int start, int end) {
    if(end > start) {
       int s = partition(A, start, end); //split position
       quickSort(A, start, s - 1); //sort before the split
       quickSort(A, s + 1, end); //sort after the split
    }
}

static
int partition(int *A, int start, int end) {

    int pivot = A[start];
    int i = start;
    int j = end + 1;

    do
    {

        do { i++;
        } while(pivot > A[i]);

        do { j--;
        } while(pivot < A[j]);

        swap(&A[i], &A[j]);

    } while (j > i);
    swap(&A[i], &A[j]); //undo last swap when i >= j
    swap(&A[start], &A[j]);

    return j;
}

enum { NUM_PER_LINE = 10 };

static void print_data(const char *tag, const int *A, int num)
{
    printf("%s (%d):\n", tag, num);
    const char *pad = "";
    int i;
    for (i = 0; i < num; i++)
    {
        printf("%s%d", pad, A[i]);
        pad = " ";
        if (i % NUM_PER_LINE == NUM_PER_LINE - 1)
        {
            putchar('\n');
            pad = "";
        }
    }
    if (i % NUM_PER_LINE != 0)
        putchar('\n');
}

int main(void) {
   srand(time(0));
   for (int n = 1; n < 24; n++)
   {
       int A[n];
       generateDescendingArray(A, n);
       print_data("Unsorted", A, n);
       quickSort(A, 0, n-1);
       print_data("Sorted", A, n);
   }

   return 0;
}

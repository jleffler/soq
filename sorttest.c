#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"

static size_t swap_count = 0;
static size_t comp_count = 0;

static void swap(int *a, int *b)
{
    swap_count++;
    int t = *a;
    *a = *b;
    *b = t;
}

static void kvik_sort(int a[], int l, int d)
{
    if (l >= d)
        return;

    int k = l;
    swap(&a[l], &a[(l + d) / 2]);

    for (int i = l + 1; i <= d; i++)
    {
        comp_count++;
        if (a[i] < a[l])
            swap(&a[++k], &a[i]);
    }
    swap(&a[l], &a[k]);

    kvik_sort(a, l, k-1);
    kvik_sort(a, k+1, d);
}

static void quick_sort(int a[], int n)
{
    kvik_sort(a, 0, n-1);
}

static void selection_sort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            comp_count++;
            if (a[j] < a[min])
                min = j;
        }
        comp_count++;
        if (min != i)
            swap(&a[min], &a[i]);
    }
}

static void insertion_sort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        //for (int j = i + 1; j > 0 && a[j] < a[j-1]; j--)
        //    swap(&a[j], &a[j-1]);
        for (int j = i + 1; j > 0; j--)
        {
            comp_count++;
            if (a[j] < a[j-1])
                swap(&a[j], &a[j-1]);
            else
                break;
        }
    }
}

static void bubble_sort(int a[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            comp_count++;
            if (a[j] > a[j+1])
                swap(&a[j], &a[j+1]);
        }
    }
}

static void fill_random(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

static void fill_ascending(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

static void fill_descending(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = -i;
}

static void fill_fwdorganpipe(int a[], int n)
{
    int m = n / 2;
    for (int i = 0; i < m; i++)
    {
        a[i] = i;
        a[n-i-1] = i;
    }
    if (n %2 == 1)
        a[m] = m;
}

static void fill_revorganpipe(int a[], int n)
{
    int m = n / 2;
    for (int i = 0; i < m; i++)
    {
        a[i] = m - i;
        a[n-i-1] = m - i;
    }
    if (n %2 == 1)
        a[m] = 0;
}

static void fill_uniform(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = 1;
}

static int check_sort(int a[], int n)
{
    int rc = 0;
    for (int i = 0; i < n-1; i++)
    {
        if (a[i] > a[i+1])
        {
            printf("Sort fail: a[%d] = %d; a[%d] = %d\n", i, a[i], i+1, a[i+1]);
            rc = 1;
        }
    }
    return rc;
}

typedef void (*Function)(int a[], int n);

typedef struct FuncInfo
{
    const char *name;
    Function    func;
} FuncInfo;

static FuncInfo fillers[] =
{
    { "Random",             fill_random        },
    { "Ascending",          fill_ascending     },
    { "Descending",         fill_descending    },
    { "Forward Organ Pipe", fill_fwdorganpipe  },
    { "Reverse Organ Pipe", fill_revorganpipe  },
    { "Uniform",            fill_uniform       },
};
enum { NUM_FILLERS = sizeof(fillers) / sizeof(fillers[0]) };

static FuncInfo sorters[] =
{
    { "Quick",      quick_sort      },
    { "Bubble",     bubble_sort     },
    { "Insertion",  insertion_sort  },
    { "Selection",  selection_sort  },
};
enum { NUM_SORTERS = sizeof(sorters) / sizeof(sorters[0]) };

static int sizes[] =
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 50, 100, 300, 1000, 3000, 10000, 30000, 100000, 300000, 1000000
};
enum { NUM_SIZES = sizeof(sizes) / sizeof(sizes[0]) };

int main(void)
{
    Clock clk;
    clk_init(&clk);
    printf("%7s %18s %9s %14s %14s %4s %11s\n",
           "Number", "Filler", "Sorter", "Compares", "Swaps", "", "Time");

    for (int i = 0; i < NUM_SIZES; i++)
    {
        size_t nbytes = sizes[i] * sizeof(int);
        int *a0 = malloc(nbytes);
        int *a1 = malloc(nbytes);
        for (int j = 0; j < NUM_FILLERS; j++)
        {
            (*fillers[j].func)(a0, sizes[i]);
            for (int k = 0; k < NUM_SORTERS; k++)
            {
                char buffer[32];
                memmove(a1, a0, nbytes);
                swap_count = 0;
                comp_count = 0;
                clk_start(&clk);
                (*sorters[k].func)(a1, sizes[i]);
                clk_stop(&clk);
                int rc = check_sort(a1, sizes[i]);
                printf("%7d %18s %9s %14zu %14zu %4s %11s\n",
                    sizes[i], fillers[j].name, sorters[k].name, comp_count, swap_count,
                    (rc == 0) ? "PASS" : "FAIL",
                    clk_elapsed_us(&clk, buffer, sizeof(buffer)));
            }
        }
        free(a0);
        free(a1);
    }
    return(0);
}


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
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
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 50, 100, 300, 1000, 3000, 10000, 30000,
    // 100000, 300000, 1000000
};
enum { NUM_SIZES = sizeof(sizes) / sizeof(sizes[0]) };

static void test1(void)
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
}

//  for n in { 100, 1023, 1024, 1025 }
//      for (m = 1; m < 2*n; m *= 2)
//          for dist in { sawtooth, rand, stagger, plateau, shuffle }
//              for (i = j = 0, k = 1; i < n; i++)
//                  switch (dist)
//                      case sawtooth: x[i] = i % m
//                      case rand:     x[i] = rand() % m
//                      case stagger:  x[i] = (i*m + i) % n
//                      case plateau:  x[i] = min(i, m)
//                      case shuffle:  x[i] = rand()%m? (j+=2): (k+=2)
//              for type in { int, double }
//                  test copy(x)             /* work on a copy of x */
//                  test reverse(x, 0, n)    /* on a reversed copy */
//                  test reverse(x, 0, n/2)  /* front half reversed */
//                  test reverse(x, n/2, n)  /* back half reversed */
//                  test sort(x)             /* an ordered copy */
//                  test dither(x)           /* add i%5 to x[i] */

typedef void (*ExtraFiller)(int a[], int n, int m);

typedef struct SortType
{
    ExtraFiller  filler_func;
    const char  *filler_name;
    Function     sorter_func;
    const char  *sorter_name;
    const char  *tag;
    int          m_param;
} SortType;

static void framework2(int a[], int n, const SortType *sort)
{
    Clock clk;
    clk_init(&clk);
//    printf("%7s %18s %9s %14s %14s %4s %11s\n",
//            "Number", "Filler", "Sorter", "Compares", "Swaps", "", "Time");

    char buffer[32];
    swap_count = 0;
    comp_count = 0;
    clk_start(&clk);
    (*sort->sorter_func)(a, n);
    clk_stop(&clk);
    int rc = check_sort(a, n);
//    printf("%7d %18s %9s %14zu %14zu %4s %11s\n",
//            sizes[i], fillers[j].name, sorters[k].name, comp_count, swap_count,
//            (rc == 0) ? "PASS" : "FAIL",
//            clk_elapsed_us(&clk, buffer, sizeof(buffer)));
//    printf("%7s %18s %18s %13s %6s %14s %14s %4s %11s\n",
//            "Number", "Sorter", "Filler", "Extra", "M", "Compares", "Swaps", "", "Time");
    printf("%7d %18s %18s %13s %6d %14zu %14zu %4s %11s\n",
            n, sort->sorter_name, sort->filler_name, sort->tag, sort->m_param,
            comp_count, swap_count, (rc == 0) ? "PASS" : "FAIL",
            clk_elapsed_us(&clk, buffer, sizeof(buffer)));
}

static void test_copy(int x[], int n, const SortType *sort)
{
    int a[n];
    for (int i = 0; i < n; i++)
        a[i] = x[i];
    framework2(a, n, sort);
}

static void test_reverse(int x[], int lo, int hi, const SortType *sort)
{
    int n = hi - lo;
    assert(n > 0);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[n-1-i] = x[i];
    }
    framework2(a, n, sort);
}

static void test_dither(int x[], int n, const SortType *sort)
{
    int a[n];
    for (int i = 0; i < n; i++)
        a[i] = x[i] + (i % 5);
    framework2(a, n, sort);
}

static void fill_sawtooth(int a[], int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = i % m;
}

static void fill_randmod(int a[], int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % m;
}

static void fill_stagger(int a[], int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = (i * m + i) % n;
}

static void fill_plateau(int a[], int n, int m)
{
    for (int i = 0; i < n; i++)
        a[i] = (i < m) ? i : m;  // min(i, m);
}

static void fill_shuffle(int a[], int n, int m)
{
    int j = 0;
    int k = 1;
    for (int i = 0; i < n; i++)
        a[i] = rand() % m ? (j += 2) : (k += 2);
}

enum modes { randmod, sawtooth, stagger, plateau, shuffle };

typedef struct ExtraInfo
{
    char        *name;
    ExtraFiller  func;
} ExtraInfo;

static ExtraInfo xfiller[] =
{
    [randmod]  = { "Random Modulo", fill_randmod  },
    [sawtooth] = { "Sawtooth",      fill_sawtooth },
    [stagger]  = { "Stagger",       fill_stagger  },
    [plateau]  = { "Plateau",       fill_plateau  },
    [shuffle]  = { "Shuffle",       fill_shuffle  },
};
enum { NUM_XFILLERS = sizeof(xfiller) / sizeof(xfiller[0]) };

static void test2(void)
{
    int  sizes[] = { 1000, 10239, 10240, 10241 };
    enum { NUM_SIZES = sizeof(sizes) / sizeof(sizes[0]) };
    int x[1025];
    SortType sort;

    printf("%7s %18s %18s %13s %6s %14s %14s %4s %11s\n",
            "Number", "Sorter", "Filler", "Extra", "M", "Compares", "Swaps", "", "Time");

    for (int i = 0; i < NUM_SORTERS; i++)
    {
        sort.sorter_func = sorters[i].func;
        sort.sorter_name = sorters[i].name;
        for (int n0 = 0; n0 < NUM_SIZES; n0++)
        {
            int n = sizes[n0];
            for (int m = 1; m < 2 * n; m *= 2)
            {
                sort.m_param = m;
                for (int d0 = 0; d0 < NUM_XFILLERS; d0++)
                {
                    printf("Sample Size: %d\n", n);
                    sort.filler_func = xfiller[d0].func;
                    sort.filler_name = xfiller[d0].name;
                    (*sort.filler_func)(x, n, m);
                    sort.tag = "Full Plain";
                    test_copy(x, n, &sort);          /* work on a copy of x */
                    sort.tag = "Full Reversed";
                    test_reverse(x, 0, n, &sort);    /* on a reversed copy */
                    sort.tag = "1st Half Revd";
                    test_reverse(x, 0, n/2, &sort);  /* front half reversed */
                    sort.tag = "2nd Half Revd";
                    test_reverse(x, n/2, n, &sort);  /* back half reversed */
                    //test_sort(x, n, &sort);        /* an ordered copy */
                    sort.tag = "Full Dithered";
                    test_dither(x, n, &sort);        /* add i%5 to x[i] */
                }
            }
        }
    }
}

int main(void)
{
    if (0)
        test1();
    if (1)
        test2();
    return(0);
}

/* J L Bentley and M D McIlroy */
/* Engineering a Sort Function */
/* SOFTWARE—PRACTICE AND EXPERIENCE, VOL. 23(11), 1249–1265 (NOVEMBER 1993) */

//  for n in { 100, 1023, 1024, 1025 }
//      for (m = 1; m < 2*n; m *= 2)
//          for dist in { sawtooth, rand, stagger, plateau, shuffle }
//              for (i = j = 0, k = 1; i < n; i++)
//                  switch (dist)
//                      case sawtooth: x[i] = i % m
//                      case rand:     x[i] = rand() % m
//                      case stagger:  x[i] = (i*m + i) % n
//                      case plateau:  x[i] = min(i, m)
//                      case shuffle:  x[i] = rand()%m? (j+=2): (k+=2)
//              for type in { int, double }
//                  test copy(x)             /* work on a copy of x */
//                  test reverse(x, 0, n)    /* on a reversed copy */
//                  test reverse(x, 0, n/2)  /* front half reversed */
//                  test reverse(x, n/2, n)  /* back half reversed */
//                  test sort(x)             /* an ordered copy */
//                  test dither(x)           /* add i%5 to x[i] */

#if 0
static void iswap(int i, int j, int a[])
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
    swap_count++;
}

static void iisort(int *a, int n)
{
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && ++comp_count && a[j-1] > a[j]; j--)
            iswap(j, j-1, a);
}

static void iqsort0(int *a, int n)
{
    int i, j;
    if (n <= 1) return;
    for (i = 1, j = 0; i < n; i++)
    {
        comp_count++;
        if (a[i] < a[0])
            swap(++j, i, a);
    }
    swap(0, j, a);
    iqsort0(a, j);
    iqsort0(a+j+1, n-j-1);
}

static void iqsort1(int *a, int n)
{
    int i, j;
    if (n <= 1) return;
    i = rand() % n;
    swap(0, i, a);
    i = 0;
    j = n;
    for (;;) {
        do i++; while (i < n && ++comp_count && a[i] < a[0]);
        do j--; while (++comp_count && a[j] > a[0]);
        if (j < i) break;
        swap(i, j, a);
    }
    swap(0, j, a);
    iqsort1(a, j);
    iqsort1(a+j+1, n-j-1);
}

static char *med3(char *a, char *b, char *c, int (*cmp)())
{
    return cmp(a, b) < 0
        ? (cmp(b, c) < 0 ? b : cmp(a, c) < 0 ? c : a)
        : (cmp(b, c) > 0 ? b : cmp(a, c) > 0 ? c : a);
}

void iqsort2(int *x, int n)
{
    int a, b, c, d, l, h, s, v;
    if (n <= 1) return;
    v = x[rand() % n];
    a = b = 0;
    c = d = n-1;
    for (;;) {
        while (b <= c && x[b] <= v) {
            if (x[b] == v) iswap(a++, b, x);
            b++;
        }
        while (c >= b && x[c] >= v) {
            if (x[c] == v) iswap(d--, c, x);
            c--;
        }
        if (b > c) break;
        iswap(b++, c--, x);
    }
    s = min(a, b-a);
    for(l = 0, h = b-s; s; s--) iswap(l++, h++, x);
    s = min(d-c, n-1-d);
    for(l = b, h = n-s; s; s--) iswap(l++, h++, x);
    iqsort2(x, b-a);
    iqsort2(x + n-(d-c), d-c);
}

/* Final qsort() - Program 7 */

typedef long WORD;
#define W sizeof(WORD) /* must be a power of 2 */
#define SWAPINIT(a, es) swaptype = (a-(char*)0 | es) % W ? 2 : es > W ? 1 : 0

#define exch(a, b, t) (t = a, a = b, b = t)
#define swap(a, b) \
    swaptype != 0 ? swapfunc(a, b, es, swaptype) : \
    (void)exch(*(WORD*)(a), *(WORD*)(b), t)
#define vecswap(a, b, n) if (n > 0) swapfunc(a, b, n, swaptype)

#define PVINIT(pv, pm) \
    if (swaptype != 0) pv = a, swap(pv, pm); \
    else pv = (char*)&v, v = *(WORD*)pm

#include <stddef.h>
static void swapfunc(char *a, char *b, size_t n, int swaptype)
{
    if (swaptype <= 1) {
        WORD t;
        for( ; n > 0; a += W, b += W, n -= W)
            exch(*(WORD*)a, *(WORD*)b, t);
    } else {
        char t;
        for( ; n > 0; a += 1, b += 1, n -= 1)
            exch(*a, *b, t);
    }
}

void qsort(char *a, size_t n, size_t es, int (*cmp)())
{
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn, *pv;
    int r, swaptype;
    WORD t, v;
    size_t s;
    SWAPINIT(a, es);
    if (n < 7) { /* Insertion sort on smallest arrays */
        for (pm = a + es; pm < a + n*es; pm += es)
            for (pl = pm; pl > a && cmp(pl-es, pl) > 0; pl -= es)
                swap(pl, pl-es);
        return;
    }
    pm = a + (n/2)*es; /* Small arrays, middle element */
    if (n > 7) {
        pl = a;
        pn = a + (n-1)*es;
        if (n > 40) { /* Big arrays, pseudomedian of 9 */
            s = (n/8)*es;
            pl = med3(pl, pl+s, pl+2*s, cmp);
            pm = med3(pm-s, pm, pm+s, cmp);
            pn = med3(pn-2*s, pn-s, pn, cmp);
        }
        pm = med3(pl, pm, pn, cmp); /* Mid-size, med of 3 */
    }
    PVINIT(pv, pm); /* pv points to partition value */
    pa = pb = a;
    pc = pd = a + (n-1)*es;
    for (;;) {
        while (pb <= pc && (r = cmp(pb, pv)) <= 0) {
            if (r == 0) { swap(pa, pb); pa += es; }
            pb += es;
        }
        while (pc >= pb && (r = cmp(pc, pv)) >= 0) {
            if (r == 0) { swap(pc, pd); pd -= es; }
            pc -= es;
        }
        if (pb > pc) break;
        swap(pb, pc);
        pb += es;
        pc -= es;
    }
    pn = a + n*es;
    s = min(pa-a, pb-pa ); vecswap(a, pb-s, s);
    s = min(pd-pc, pn-pd-es); vecswap(pb, pn-s, s);
    if ((s = pb-pa) > es) qsort(a, s/es, es, cmp);
    if ((s = pd-pc) > es) qsort(pn-s, s/es, es, cmp);
}

#endif

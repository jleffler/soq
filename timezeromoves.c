#include <string.h>

#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

extern void shunt_zeroes(int *list, size_t n);
extern void pushbackzeros(int *list, size_t n);
extern void pushbackzeros2(int *list, size_t n);
extern void shufflezeroes(int *list, size_t n);
extern void RemoveDead(int *list, size_t n);
extern void list_compact(int *arr, size_t cnt);

void list_compact(int *arr, size_t cnt)
{
    size_t dst,src,pos;

    /* Skip leading filled area; find start of blanks */
    for (pos=0; pos < cnt; pos++) {
        if ( !arr[pos] ) break;
    }
    if (pos == cnt) return;

    for(dst= pos; ++pos < cnt; ) { 
        /* Skip blanks; find start of filled area */
        if ( !arr[pos] ) continue;

        /* Find end of filled area */
        for(src = pos; ++pos < cnt; ) {
            if ( !arr[pos] ) break;
        }   
        if (pos > src) {
            memmove(arr+dst, arr+src, (pos-src) * sizeof arr[0] );
            dst += pos-src;
        }   
    }
}

/* Cannot change j to size_t safely; algorithm relies on it going negative */
void RemoveDead(int *list, size_t n)
{
    int i, j = n - 1;
    for (; j >= 0 && list[j] == 0; --j)
        ;
    for (i = 0; i <= j; ++i)
    {   
        if (list[i])
            continue;
        memcpy(&(list[i]), &(list[j]), sizeof(int));
        list[j] = 0;
        for (; j >= 0 && list[j] == 0; --j);
        if (i == j)
            break;
    }   
}

void shufflezeroes(int *list, size_t n)
{
    for (size_t i = 0; i < n; ++i) 
    {    
        if (list[i])
            continue;
        size_t j;
        for (j = i + 1; j < n && !list[j]; ++j)
            ;
        size_t z;
        for (z = j + 1; z < n && list[z]; ++z)
            ;
        if (j == n)
            break;
        memmove(&(list[i]), &(list[j]), sizeof(int) * (z - j));
        size_t s = z - j + i;
        for(j = s; j < z; ++j) 
            list[j] = 0;
        i = s - 1;
    } 
}

static int nextZero(int* list, size_t start, size_t n){
   size_t i = start;
   while(i < n && list[i])
        i++;
   return i;
}

static int nextNonZero(int* list, size_t start, size_t n){
   size_t i = start;
   while(i < n && !list[i])
        i++;
   return i;
}

void pushbackzeros(int* list, size_t n){
    size_t i = 0;
    size_t j = 0;
    while(i < n && j < n){
         i = nextZero(list,i, n);
         j = nextNonZero(list,i, n);
         if(i >= n || j >=n)
             return;
         list[i] = list[j];
         list[j] = 0;
    }
}

/* Amended algorithm */
void pushbackzeros2(int* list, size_t n){
    size_t i = 0;
    size_t j = 0;
    while(i < n && j < n){
         i = nextZero(list, i, n);
         j = nextNonZero(list, MAX(i,j), n);
         if(i >= n || j >=n)
             return;
         list[i] = list[j];
         list[j] = 0;
    }
}

void shunt_zeroes(int *list, size_t n)
{
    if (n > 1)
    {
        size_t tail = n;
        for (size_t i = 0; i < tail - 1; i++)
        {
            if (list[i] == 0)
            {
                while (--tail > i + 1 && list[tail] == 0)
                    ;
                if (tail > i)
                {
                    int t = list[i];
                    list[i] = list[tail];
                    list[tail] = t;
                }
            }
        }
    }
}

/* Test Harness */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define DIM(x)      (sizeof(x)/sizeof(*(x)))

typedef void (*Shunter)(int *list, size_t n);

typedef struct FUT      /* FUT = Function Under Test */
{
    Shunter function;
    const char *name;
    const char *author;
} FUT;

static int tflag = 1;   /* timing */
static int cflag = 1;   /* checking */
static size_t maxsize = 1000000;

static void dump_list(const char *tag, int *list, size_t n)
{
    printf("%-8s", tag);
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", list[i]);
    }
    putchar('\n');
    fflush(0);
}

static void test_list(int *list, size_t n, Shunter s)
{
    dump_list("Before:", list, n);
    (*s)(list, n);
    dump_list("After:", list, n);
}

static void list_of_tests(const FUT *f)
{
    int list1[] = { 1, 0, 2, 0, 3, 0, 4, 0, 5 };
    int list2[] = { 1, 2, 2, 0, 3, 0, 4, 0, 0 };
    int list3[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int list4[] = { 0, 1 };
    int list5[] = { 0, 0 };
    int list6[] = { 0 };

    test_list(list1, DIM(list1), f->function);
    test_list(list2, DIM(list2), f->function);
    test_list(list3, DIM(list3), f->function);
    test_list(list4, DIM(list4), f->function);
    test_list(list5, DIM(list5), f->function);
    test_list(list6, DIM(list6), f->function);
}

static void test_timer(int *list, size_t n, const FUT *f)
{
    Clock t;
    clk_init(&t);
    clk_start(&t);
    f->function(list, n);
    clk_stop(&t);
    char buffer[32];
    printf("%-15s  %7zu  %10s\n", f->name, n, clk_elapsed_us(&t, buffer, sizeof(buffer)));
    fflush(0);
}

static void gen_test(size_t n, const FUT *f)
{
    int list[n];
    for (size_t i = 0; i < n/2; i += 2)
    {
        list[2*i+0] = i;
        list[2*i+1] = 0;
    }   
    test_timer(list, n, f);
}

static void timed_run(const FUT *f)
{
    printf("%s (%s)\n", f->name, f->author);
    if (cflag)
        list_of_tests(f);
    if (tflag)
    {
        for (size_t n = 100; n <= maxsize; n *= 10)
            gen_test(n, f);
    }
}

static const char optstr[] = "cm:n:t";
static const char usestr[] = "[-ct][-m maxsize][-n iterations]";

int main(int argc, char **argv)
{
    FUT functions[] =
    {
        { shunt_zeroes,   "shunt_zeroes:",   "Jonathan"    },   /* O(N) */
        { RemoveDead,     "RemoveDead:",     "Patrik"      },   /* O(N) */
        { pushbackzeros2, "pushbackzeros2:", "UmNyobe"     },   /* O(N) */
        { list_compact,   "list_compact:",   "Wildplasser" },   /* O(N) */
        { shufflezeroes,  "shufflezeroes:",  "Patrik"      },   /* O(N^2) */
        { pushbackzeros,  "pushbackzeros:",  "UmNyobe"     },   /* O(N^2) */
    };
    enum { NUM_FUNCTIONS = sizeof(functions)/sizeof(functions[0]) };
    int opt;
    int itercount = 2;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'c':
            cflag = 0;
            break;
        case 't':
            tflag = 0;
            break;
        case 'n':
            itercount = atoi(optarg);
            break;
        case 'm':
            maxsize = strtoull(optarg, 0, 0);
            break;
        default:
            fprintf(stderr, "Usage: %s %s\n", argv[0], usestr);
            return(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < itercount; i++)
    {
        for (int j = 0; j < NUM_FUNCTIONS; j++)
            timed_run(&functions[j]);
        if (tflag == 0)
            break;
        cflag = 0;  /* Don't check on subsequent iterations */
    }

    return 0;
}


#include "timer.h"
#include <stdio.h>
#include <string.h>

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

extern void shunt_zeroes(int *list, size_t n);
extern void pushbackzeros(int *list, size_t n);
extern void shufflezeroes(int *list, size_t n);
extern void RemoveDead(int *list, size_t n);

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

typedef void (*Shunter)(int *list, size_t n);

typedef struct FUT      /* FUT = Function Under Test */
{
    Shunter function;
    const char *tag;
} FUT;

static void test_list(int *list, size_t n, Shunter s)
{
    dump_list("Before:", list, n);
    (*s)(list, n);
    dump_list("After:", list, n);
}

static void list_of_tests(Shunter s)
{
    int list1[] = { 1, 0, 2, 0, 3, 0, 4, 0, 5 };
    int list2[] = { 1, 2, 2, 0, 3, 0, 4, 0, 0 };
    int list3[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int list4[] = { 0, 1 };
    int list5[] = { 0, 0 };
    int list6[] = { 0 };

    test_list(list1, DIM(list1), s);
    test_list(list2, DIM(list2), s);
    test_list(list3, DIM(list3), s);
    test_list(list4, DIM(list4), s);
    test_list(list5, DIM(list5), s);
    test_list(list6, DIM(list6), s);
}

static void test_timer(int *list, size_t n, const FUT *f)
{
    Clock t;
    clk_init(&t);
    clk_start(&t);
    f->function(list, n);
    clk_stop(&t);
    char buffer[32];
    printf("%-15s  %7zu  %10s\n", f->tag, n, clk_elapsed_us(&t, buffer, sizeof(buffer)));
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
    for (size_t n = 100; n <= 1000000; n *= 10)
        gen_test(n, f);
}

int main(void)
{
    FUT f1 = { shunt_zeroes,  "shunt_zeroes:"  };
    FUT f2 = { pushbackzeros, "pushbackzeros:" };
    FUT f3 = { shufflezeroes, "shufflezeroes:" };
    FUT f4 = { RemoveDead,    "RemoveDead:"    };

    list_of_tests(shunt_zeroes);
    list_of_tests(pushbackzeros);
    list_of_tests(shufflezeroes);
    list_of_tests(RemoveDead);

    for (int i = 0; i < 2; i++)
    {
        timed_run(&f1);
        timed_run(&f4);
        timed_run(&f2);
        timed_run(&f3);
    }
    return 0;
}


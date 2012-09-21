#include <stdio.h>
#define DIM(x)  (sizeof(x)/sizeof(*(x)))

extern void shunt_zeroes(int *list, size_t n);

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

static void test_list(int *list, size_t n)
{
    dump_list("Before:", list, n);
    shunt_zeroes(list, n);
    dump_list("After:", list, n);
}

int main(void)
{
    int list1[] = { 1, 0, 2, 0, 3, 0, 4, 0, 5 };
    int list2[] = { 1, 2, 2, 0, 3, 0, 4, 0, 0 };
    int list3[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int list4[] = { 0, 1 };
    int list5[] = { 0, 0 };
    int list6[] = { 0 };
    test_list(list1, DIM(list1));
    test_list(list2, DIM(list2));
    test_list(list3, DIM(list3));
    test_list(list4, DIM(list4));
    test_list(list5, DIM(list5));
    test_list(list6, DIM(list6));
}


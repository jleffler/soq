#include <stdio.h>

typedef enum { WHITE, BLACK, RED } color;

static char color_code(color c)
{
    return(c == WHITE ? 'W' : c == RED ? 'R' : 'B');
}

static void dump_colors(char const *tag, color *data, unsigned num)
{
    printf("%s:", tag);
    for (unsigned i = 0; i < num; i++)
        printf(" %c", color_code(data[i]));
    putchar('\n');
}

static
void swap(color *p1, color *p2)
{
    color tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

static
void partition3(color *arr, unsigned n)
{
    if (n <= 1)
        return;

    unsigned w = 0;
    unsigned r = n;

    while (w < r && arr[w] == WHITE)
        w++;
    while (r > w && arr[r-1] == RED)
        r--;
    //printf("w = %d; r = %d\n", w, r);

    for (unsigned i = w; i < r; i++)
    {
        //printf("i = %2u, r = %2u, w = %2u, c = %c", i, r, w, color_code(arr[i]));
        //dump_colors("", arr, n);
        if (arr[i] == RED)
            swap(&arr[i], &arr[--r]);
        if (arr[i] == WHITE)
            swap(&arr[i], &arr[w++]);
    }
}

int main(void)
{
    struct test
    {
        color *data;
        size_t size;
    };
    color array1[] = { WHITE, BLACK, RED };
    color array2[] = { WHITE, WHITE, WHITE };
    color array3[] = { RED, RED, RED };
    color array4[] = { BLACK, BLACK, BLACK };
    color array5[] = { RED, BLACK, WHITE };
    color array6[] = { WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE };
    color array7[] = { BLACK, BLACK, WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE, BLACK, BLACK, };
    color array8[] = { WHITE, BLACK };
    color array9[] = { BLACK, BLACK, RED, RED, WHITE, WHITE, RED };
    color array0[] = { BLACK, BLACK, RED, WHITE, RED };
    struct test tests[] =
    {
        { array1, sizeof(array1)/sizeof(array1[0]) },
        { array2, sizeof(array2)/sizeof(array2[0]) },
        { array3, sizeof(array3)/sizeof(array3[0]) },
        { array4, sizeof(array4)/sizeof(array4[0]) },
        { array5, sizeof(array5)/sizeof(array5[0]) },
        { array6, sizeof(array6)/sizeof(array6[0]) },
        { array7, sizeof(array7)/sizeof(array7[0]) },
        { array8, sizeof(array8)/sizeof(array8[0]) },
        { array9, sizeof(array9)/sizeof(array9[0]) },
        { array0, sizeof(array0)/sizeof(array0[0]) },
    };

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        dump_colors("Before", tests[i].data, tests[i].size);
        partition3(tests[i].data, tests[i].size);
        dump_colors("After ", tests[i].data, tests[i].size);
    }
    return 0;
}

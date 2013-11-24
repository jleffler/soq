#include <stdio.h>

typedef enum { WHITE, BLACK, RED } Colour;

static char colour_code(Colour c)
{
    return(c == WHITE ? 'W' : c == RED ? 'R' : 'B');
}

static void dump_colours(char const *tag, Colour *data, unsigned num)
{
    printf("%s:", tag);
    for (unsigned i = 0; i < num; i++)
        printf(" %c", colour_code(data[i]));
    putchar('\n');
}

static
void swap(Colour *p1, Colour *p2)
{
    Colour tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

static
void partition3(Colour *arr, unsigned n)
{
    if (n <= 1)
        return;

    unsigned w = 0;
    unsigned r = n;

    while (w < r && arr[w] == WHITE)
        w++;
    while (r > w && arr[r-1] == RED)
        r--;
    printf("w = %d; r = %d\n", w, r);

    for (unsigned i = w; i < r; i++)
    {
        putchar('\n');
        printf("-| i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
        dump_colours("", arr, n);
        if (arr[i] == RED)
        {
            swap(&arr[i], &arr[--r]);
            while (r > w && arr[r-1] == RED)
                r--;
            printf("-- i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
            dump_colours("", arr, n);
        }
        if (arr[i] == WHITE)
        {
            swap(&arr[i], &arr[w++]);
            while (r > w && arr[r-1] == RED)
                r--;
            printf("|- i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
            dump_colours("", arr, n);
        }
    }
}

int main(void)
{
    struct test
    {
        Colour *data;
        size_t size;
    };
    //Colour array1[] = { WHITE, BLACK, RED };
    //Colour array2[] = { WHITE, WHITE, WHITE };
    //Colour array3[] = { RED, RED, RED };
    //Colour array4[] = { BLACK, BLACK, BLACK };
    //Colour array5[] = { RED, BLACK, WHITE };
    //Colour array6[] = { WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE };
    //Colour array7[] = { BLACK, BLACK, WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE, BLACK, BLACK, };
    //Colour array8[] = { WHITE, BLACK };
    //Colour array9[] = { BLACK, BLACK, RED, RED, WHITE, WHITE, RED };
    //Colour array0[] = { BLACK, BLACK, RED, WHITE, RED };
    Colour arrayA[] = { RED, BLACK, RED, WHITE, RED, RED, BLACK, WHITE, RED, BLACK, RED, BLACK, BLACK, RED, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, RED, RED, RED, RED, BLACK, WHITE };
    struct test tests[] =
    {
        //{ array1, sizeof(array1)/sizeof(array1[0]) },
        //{ array2, sizeof(array2)/sizeof(array2[0]) },
        //{ array3, sizeof(array3)/sizeof(array3[0]) },
        //{ array4, sizeof(array4)/sizeof(array4[0]) },
        //{ array5, sizeof(array5)/sizeof(array5[0]) },
        //{ array6, sizeof(array6)/sizeof(array6[0]) },
        //{ array7, sizeof(array7)/sizeof(array7[0]) },
        //{ array8, sizeof(array8)/sizeof(array8[0]) },
        //{ array9, sizeof(array9)/sizeof(array9[0]) },
        //{ array0, sizeof(array0)/sizeof(array0[0]) },
        { arrayA, sizeof(arrayA)/sizeof(arrayA[0]) },
    };

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
    {
        dump_colours("Before", tests[i].data, tests[i].size);
        partition3(tests[i].data, tests[i].size);
        dump_colours("After ", tests[i].data, tests[i].size);
    }
    return 0;
}

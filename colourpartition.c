#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { WHITE, BLACK, RED } Colour;

static char colour_code(Colour c)
{
    return(c == WHITE ? 'W' : c == RED ? 'R' : 'B');
}

static void print_colours(FILE *fp, char const *tag, Colour *data, unsigned num)
{
    fprintf(fp, "%s:", tag);
    for (unsigned i = 0; i < num; i++)
        fprintf(fp, " %c", colour_code(data[i]));
    putc('\n', fp);
}

static void dump_colours(char const *tag, Colour *data, unsigned num)
{
    print_colours(stdout, tag, data, num);
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
void partition3(size_t n, Colour *arr)
{
    if (n <= 1)
        return;

    size_t w = 0;
    size_t r = n;

    //putchar('\n');
    //printf("w0 = %d; r0 = %d: ", w, r);
    while (w < r && arr[w] == WHITE)
        w++;
    while (r > w && arr[r-1] == RED)
        r--;
    //printf("w1 = %d; r1 = %d\n", w, r);

    for (size_t i = w; i < r; i++)
    {

        //printf("-| i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
        //dump_colours("", arr, n);
        if (arr[i] == RED)
        {
            swap(&arr[i], &arr[--r]);
            while (r > w && arr[r-1] == RED)
                r--;
            //printf("-- i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
            //dump_colours("", arr, n);
        }
        if (arr[i] == WHITE)
        {
            swap(&arr[i], &arr[w++]);
            while (w < r && arr[w] == WHITE)
                w++;
            //printf("|- i = %2u, r = %2u, w = %2u, c = %c", i, r, w, colour_code(arr[i]));
            //dump_colours("", arr, n);
        }
    }
}

static Colour *dup_sequence(size_t n, Colour const *a)
{
    Colour *d = malloc(n * sizeof(*d));
    if (d == 0)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    for (size_t i = 0; i < n; i++)
        d[i] = a[i];
    return d;
}

static bool is_invalid_sequence(size_t n, Colour *a)
{
    bool rc = false;
    size_t w;
    for (w = 0; w < n; w++)
    {
        if (a[w] != WHITE)
            break;
    }

    size_t b;
    for (b = w; b < n; b++)
    {
        if (a[b] == WHITE)
        {
            fprintf(stderr, "Error: %c out of position (%zu):", colour_code(a[b]), b);
            print_colours(stderr, "", a, n);
            rc = true;
        }
        if (a[b] != BLACK)
            break;
    }

    size_t r;
    for (r = b; r < n; r++)
    {
        if (a[r] != RED)
        {
            fprintf(stderr, "Error: %c out of position (%zu):", colour_code(a[r]), r);
            print_colours(stderr, "", a, n);
            rc = true;
        }
    }

    return rc;
}

typedef struct Test
{
    Colour *data;
    size_t size;
} Test;

static bool test_sequence(Test t)
{
    bool rc = true;
    size_t  n = t.size;
    Colour *a = t.data;
    Colour *d = dup_sequence(n, a);
    dump_colours("Before", a, n);
    partition3(n, d);
    dump_colours("After ", d, n);
    if (is_invalid_sequence(n, d))
        rc = false;
    free(d);
    return rc;
}

int main(void)
{
    size_t fail = 0;
    Colour array1[] = { WHITE, BLACK, RED };
    Colour array2[] = { WHITE, WHITE, WHITE };
    Colour array3[] = { RED, RED, RED };
    Colour array4[] = { BLACK, BLACK, BLACK };
    Colour array5[] = { RED, BLACK, WHITE };
    Colour array6[] = { WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE };
    Colour array7[] = { BLACK, BLACK, WHITE, WHITE, RED, RED, BLACK, BLACK, WHITE, BLACK, BLACK, };
    Colour array8[] = { WHITE, BLACK };
    Colour array9[] = { BLACK, BLACK, RED, RED, WHITE, WHITE, RED };
    Colour array0[] = { BLACK, BLACK, RED, WHITE, RED };
    Colour arrayA[] = { RED, BLACK, RED, WHITE, RED, RED, BLACK, WHITE, RED, BLACK, RED, BLACK, BLACK, RED, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, RED, RED, RED, RED, BLACK, WHITE };
    Test tests[] =
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
        { arrayA, sizeof(arrayA)/sizeof(arrayA[0]) },
    };
    enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };

    for (size_t i = 0; i < NUM_TESTS; i++)
    {
        if (test_sequence(tests[i]) == false)
            fail++;
    }

    unsigned seed = time(0);
    srand(seed);
    printf("Seed: %u\n", seed);

    for (size_t i = 0; i < 1000; i++)
    {
        Test t;
        t.size = rand() % 100;
        t.data = malloc(t.size * sizeof(*t.data));
        if (t.data == 0)
        {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        printf("Test: %zu (%zu)\n", i, t.size);
        for (size_t j = 0; j < t.size; j++)
            t.data[j] = rand() % 3;
        if (test_sequence(t) == false)
        {
            fail++;
            break;
        }
    }

    printf("Failures: %zu\n", fail);

    return 0;
}

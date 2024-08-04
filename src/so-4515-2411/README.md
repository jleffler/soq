### Stack Overflow Question 4515-2411

[SO 4515-2411](https://stackoverflow.com/q/45152411) &mdash;
How to find max element in an unknown type array in c (using pointers to functions)

Generic maximum code.

Note the [answer](https://stackoverflow.com/a/45152784/15168) by
[chqrlie](https://stackoverflow.com/users/4593267/chqrlie); it uses
standard comparators returning <0, 0, >0.


As I noted in a comment and
[chqrlie](https://stackoverflow.com/users/4593267/chqrlie) noted in an
[answer](https://stackoverflow.com/a/45152784/), there are a number of
problems with the original code.  In particular, like the
[`qsort()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/qsort.html)
function, you need to pass the size of each element in the array to the
function — and you should pass an array of values, not of pointers to
values (see comments by [Ilya
Bursov](https://stackoverflow.com/users/2864275/ilya-bursov) and
responses by me amongst others).  Also, GCC notwithstanding, standard C
does not allow you to do pointer arithmetic on `void *` because the size
of the object pointed at is unknown.  You need to convert to a `char *`,
do arithmetic based on index and element size, and then pass that to the
comparison function.

The generic function needed some work to compare the current maximum
with new entries (and mercifully the test data needed to return the last
value from one of the arrays; I had an off-by-one error that the tests
spotted).

The comparators are rather unorthodox — they're not the same as the
ones used by `qsort()` because they only return 0 or 1.  It would be
better to modify them to return a negative value if the first argument
compares smaller than the second, a positive value if the first argument
compares larger than the second, and zero if the arguments compare
equal.  The code in `maxElements()` will work correctly with either type
of comparator, but you'd be able to sort with the same comparators if
they match the 'standard' interface used by `qsort()`.

Making those changes, and some others, leads to code along the lines of:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    static void printStr(char **data, size_t num);
    static void printDbl(double *data, size_t num);
    static void printInt(int *data, size_t num);

    int compareInt(const void *a, const void *b);
    int compareDbl(const void *a, const void *b);
    int compareStr(const void *a, const void *b);
    void *maxElement(void *arr, size_t number, size_t size, int (*comp)(const void *, const void *));

    void *maxElement(void *arr, size_t number, size_t size, int (*comp)(const void *, const void *))
    {
        char *base = arr;
        void *max = base;

        for (size_t i = 1; i < number; i++)
        {
            if (comp(&base[i * size], max) > 0)
                max = &base[i * size];
        }

        return max;
    }

    int compareInt(const void *a, const void *b)
    {
        int i1 = *(int *)a;
        int i2 = *(int *)b;

        return(i1 > i2);
    }

    int compareDbl(const void *a, const void *b)
    {
        double d1 = *(double *)a;
        double d2 = *(double *)b;

        return(d1 > d2);
    }

    int compareStr(const void *a, const void *b)
    {
        char *s1 = *(char **)a;
        char *s2 = *(char **)b;

        int rc = 0;
        if (strcmp(s1, s2) > 0)
            rc = 1;
        return rc;
    }

    int main(void)
    {
        int     i_array[4] = { 11, 3, 7, 0 };
        double  d_array[4] = { 1.23, 6.57, 9.89, 11.56 };
        char   *s_array[5] = { "jess", "ron", "tom", "mia", "alex" };

        printInt(i_array, 4);
        int i_max = *(int *)maxElement(i_array, 4, sizeof(int), &compareInt);
        printDbl(d_array, 4);
        double d_max = *(double *)maxElement(d_array, 4, sizeof(double), &compareDbl);
        printStr(s_array, 5);
        char *s_max = *(char **)maxElement(s_array, 5, sizeof(char *), &compareStr);
        printf("Max integer: %d\n", i_max);
        printf("Max double:  %.2f\n", d_max);
        printf("Max string:  [%s]\n", s_max);
        return 0;
    }

    static void printStr(char **data, size_t num)
    {
        const char *pad = "Strings:";
        for (size_t i = 0; i < num; i++)
        {
            printf("%s %s", pad, data[i]);
            pad = ",";
        }
        putchar('\n');
    }

    static void printDbl(double *data, size_t num)
    {
        const char *pad = "Doubles:";
        for (size_t i = 0; i < num; i++)
        {
            printf("%s %.2f", pad, data[i]);
            pad = ",";
        }
        putchar('\n');
    }

    static void printInt(int *data, size_t num)
    {
        const char *pad = "Integers:";
        for (size_t i = 0; i < num; i++)
        {
            printf("%s %d", pad, data[i]);
            pad = ",";
        }
        putchar('\n');
    }

Note that instead of a 2D array of `char`, I've opted to use a 1D array
of `char *`.  You can write the code to handle the 2D array; it is less
commonly necessary in practice.

Sample output:

    Integers: 11, 3, 7, 0
    Doubles: 1.23, 6.57, 9.89, 11.56
    Strings: jess, ron, tom, mia, alex
    Max integer: 11
    Max double:  11.56
    Max string:  [tom]


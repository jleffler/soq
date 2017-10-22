#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
** Design issue: is the randomizer type appropriate?  Since the array
** sizes are in terms of size_t, and the indexes in the function are
** size_t, it seems sensible to have the randomizer work with size_t
** too.  OTOH, that probably means wrapping a more general purpose
** randomizer.  OTOOH, you probably need to do that anyway.
*/
extern void shuffle(void *array, size_t number, size_t size, size_t (*randomizer)(size_t n));

/*
** rand_int() and shuffle() based on code for integers in
** https://stackoverflow.com/a/3348142 - an answer by Roland Illig
** (https://stackoverflow.com/users/225757/roland-illig).
**
** https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
** To shuffle an array a of n elements (indices 0..n-1):
**     for i from n − 1 downto 1 do
**          j ← random integer such that 0 ≤ j ≤ i
**          exchange a[j] and a[i]
*/

static size_t rand_int(size_t n)
{
    size_t limit = RAND_MAX - RAND_MAX % n;
    size_t rnd;

    while ((rnd = rand()) >= limit)
        ;
    return rnd % n;
}

void shuffle(void *array, size_t number, size_t size, size_t (*randomizer)(size_t n))
{
    char buffer[size];
    char *base = (char *)array;
    for (size_t i = number - 1; i > 0; i--)
    {
        size_t j = (*randomizer)(i + 1);
        memmove(buffer, &base[i * size], size);
        memmove(&base[i * size], &base[j * size], size);
        memmove(&base[j * size], buffer, size);
    }
}

static void dump_matrix(const char *tag, int n, int matrix[n][n])
{
    printf("%s: (%d x %d)\n", tag, n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("  %d", matrix[i][j]);
        putchar('\n');
    }
}

static void dump_data(const char *tag, size_t size, const char *data[size])
{
    printf("%s: (%zu)\n", tag, size);
    for (size_t i = 0; i < size; i++)
        printf("%zu: [%s]\n", i, data[i]);
}

/* Based on example from https://blog.codinghorror.com/the-danger-of-naivete/ */
static void danger_of_naivete(void)
{
    printf("The danger of naivete\n");
    int count[322] = { 0 };
    for (int i = 0; i < 1000000; i++)
    {
        int data[3] = { 1, 2, 3 };
        shuffle(&data[0], 3, sizeof(data[0]), rand_int);
        int n = (data[0] * 10 + data[1]) * 10 + data[2];
        count[n]++;
    }
    for (int i = 0; i < 322; i++)
    {
        if (count[i] != 0)
            printf("%d = %6d\n", i, count[i]);
    }
}

int main(int argc, char **argv)
{
    enum { MATRIX_DIM = 4 };
    enum { MATRIX_SIZE = MATRIX_DIM * MATRIX_DIM };
    int matrix[MATRIX_DIM][MATRIX_DIM];

    if (argc > 1)
    {
        long l = strtol(argv[1], 0, 0);
        unsigned u = (unsigned)l;
        printf("Seed: %u\n", u);
        srand(u);
    }

    int *base = &matrix[0][0];
    for (int i = 0; i < MATRIX_SIZE / 2; i++)
    {
        *base++ = i + 1;
        *base++ = i + 1;
    }

    dump_matrix("Before", MATRIX_DIM, matrix);
    shuffle(&matrix[0][0], MATRIX_SIZE, sizeof(matrix[0][0]), rand_int);
    dump_matrix("After", MATRIX_DIM, matrix);

    const char *data[] =
    {
        "Fiddlesticks",
        "Blathering",
        "Absinthe",
        "Macedonia",
        "Xylophone",
        "Tepid",
        "Arizona"
    };
    enum { DATA_SIZE = sizeof(data) / sizeof(data[0]) };

    dump_data("Before", DATA_SIZE, data);
    shuffle(data, DATA_SIZE, sizeof(data[0]), rand_int);
    dump_data("After", DATA_SIZE, data);

    danger_of_naivete();

    return 0;
}

/* SO 7365814 In-place array reordering */
#include <assert.h>

static void mutate(int *a, int *indices, int n)
{
    for (int i_dst_first = 0; i_dst_first < n; ++i_dst_first)
    {
        /* Check if this element needs to be permuted */
        int i_src = indices[i_dst_first];
        assert(i_src < n);
        if (i_src == i_dst_first)
            /* This element is already in place */
            continue;

        int i_dst = i_dst_first;
        int pending = a[i_dst];

        /* Follow the permutation cycle */
        do
        {
            a[i_dst] = a[i_src];
            indices[i_dst] = i_dst;

            i_dst = i_src;
            i_src = indices[i_src];
            assert(i_src != i_dst);
        } while (i_src != i_dst_first);

        a[i_dst] = pending;
        indices[i_dst] = i_dst;
    }
}

#include <stdio.h>

static void print_vector(const char *tag, int *v, int n)
{
    printf("%s: ", tag);
    const char *pad = "";
    for (int i = 0; i < n; i++)
    {
        printf("%s%d", pad, v[i]);
        pad = ", ";
    }
    putchar('\n');
}

int main(void)
{
    int a[] = { 8, 6, 7, 5, 3, 0, 9 };
    int i[] = { 3, 6, 2, 4, 0, 1, 5 };
    int o[] = { 5, 9, 7, 3, 8, 6, 0 };

    int n = sizeof(a) / sizeof(a[0]);

    print_vector("a", a, n);
    print_vector("i", i, n);
    print_vector("o", o, n);

    mutate(a, i, n);

    print_vector("a", a, n);

    for (int j = 0; j < n; j++)
        assert(a[j] == o[j]);

    puts("OK");
    return 0;
}

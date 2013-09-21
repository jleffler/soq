/* http://stackoverflow.com/q/18928821 Merge sort code debugging */
/* valgrind gives this a clean bill of health */

#include <iostream>
using namespace std;

namespace {

void merge(int *l, int m, int *r, int n, int *result);

void dump_array(const char *tag, int *a, int size)
{
    int i;
    cout << tag << ": (" << size << ") ";
    for (i = 0; i < size; i++)
    {
        cout << ' ' << a[i];
        if (i % 10 == 9)
            cout << '\n';
    }
    if (i % 10 != 0)
        cout << '\n';
}

};

void merge_sort(int *a, int size)
{
    if (size <= 1)
        return;

    dump_array("-->> merge_sort", a, size);
    int middle = size/2;
    int *left = new int[middle];
    int *right = new int[size - middle];

    for (int i = 0; i < middle; i++)
        left[i] = a[i];

    for (int j = 0; j < size - middle; j++)
        right[j] = a[j + middle];

    merge_sort(left, middle);
    merge_sort(right, size - middle);
    merge(left, middle, right, size - middle, a);
    delete [] left;
    delete [] right;
    dump_array("<<-- merge_sort", a, size);
}

namespace {

void merge(int *l, int m, int *r, int n, int *result)
{
    int *l_end = l + m;
    int *r_end = r + n;
    int *out = result;
    cout << "-->> merge: (" << m << "," << n << ")\n";
    dump_array("L", l, m);
    dump_array("R", r, n);

    while (l < l_end && r < r_end)
    {
        if (*l <= *r)
            *out++ = *l++;
        else
            *out++ = *r++;
    }
    while (l < l_end)
        *out++ = *l++;
    while (r < r_end)
        *out++ = *r++;

    dump_array("<<-- merge", result, m+n);
}

};

int main()
{
    for (int i = 1; i <= 10; i++)
    {
        int array1[] = { 9, 3, 5, 7, 1, 8, 0, 6, 2, 4 };
        cout << "\nMerge array of size " << i << "\n\n";
        dump_array("Before", array1, i);
        merge_sort(array1, i);
        dump_array("After", array1, i);
    }
    return 0;
}

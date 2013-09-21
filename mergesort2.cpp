/* http://stackoverflow.com/q/18928821 Merge sort code debugging */
/* valgrind gives this a clean bill of health */

#include <iostream>
using namespace std;

namespace {

template <typename T>
void merge(T *l, int m, T *r, int n, T *result);

template <typename T>
void dump_array(const char *tag, T *a, int size)
{
    int i;
    cout << tag << ": (" << size << ") ";
    for (i = 0; i < size; i++)
    {
        cout << "  " << a[i];
        if (i % 10 == 9)
            cout << '\n';
    }
    if (i % 10 != 0)
        cout << '\n';
}

};

template <typename T>
void merge_sort(T *a, int size)
{
    if (size <= 1)
        return;

    dump_array("-->> merge_sort", a, size);
    int middle = size/2;
    T *left = new T[middle];
    T *right = new T[size - middle];

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

template <typename T>
void merge(T *l, int m, T *r, int n, T *result)
{
    T *l_end = l + m;
    T *r_end = r + n;
    T *out = result;
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

#include <string>

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

    for (int i = 1; i <= 10; i++)
    {
        double array2[] = { 9.9, 3.1, 5.2, 7.3, 1.4, 8.5, 0.6, 6.7, 2.8, 4.9 };
        cout << "\nMerge array of size " << i << "\n\n";
        dump_array("Before", array2, i);
        merge_sort(array2, i);
        dump_array("After", array2, i);
    }

    for (int i = 1; i <= 10; i++)
    {
        std::string array3[] = { "nine", "three", "five", "seven", "one", "eight", "zero", "six", "two", "four" };
        cout << "\nMerge array of size " << i << "\n\n";
        dump_array("Before", array3, i);
        merge_sort(array3, i);
        dump_array("After", array3, i);
    }

    return 0;
}

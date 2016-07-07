/* http://stackoverflow.com/q/18928821 Merge sort code debugging */
/* valgrind gives this a clean bill of health */

#include <iostream>
#include <vector>
using namespace std;

#if !defined(TRACE_ENABLED)
#define TRACE_ENABLED 0
#endif

enum { ENABLE_TRACE = TRACE_ENABLED };

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

template <typename T>
void merge_sort(T *a, int size)
{
    if (size <= 1)
        return;

    if (ENABLE_TRACE)
        dump_array("-->> merge_sort", a, size);
    int middle = size/2;
    vector<T> left(middle);
    vector<T> right(size - middle);

    for (int i = 0; i < middle; i++)
        left[i] = a[i];

    for (int j = 0; j < size - middle; j++)
        right[j] = a[j + middle];

    merge_sort(left.data(), middle);
    merge_sort(right.data(), size - middle);
    merge(left.data(), middle, right.data(), size - middle, a);
    if (ENABLE_TRACE)
        dump_array("<<-- merge_sort", a, size);
}

template <typename T>
void merge(T *l, int m, T *r, int n, T *result)
{
    T *l_end = l + m;
    T *r_end = r + n;
    T *out = result;
    if (ENABLE_TRACE)
    {
        cout << "-->> merge: (" << m << "," << n << ")\n";
        dump_array("L", l, m);
        dump_array("R", r, n);
    }

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

    if (ENABLE_TRACE)
        dump_array("<<-- merge", result, m+n);
}

#include <string>

int main()
{

    for (size_t i = 1; i <= 10; i++)
    {
        int array1[] = { 9, 3, 5, 7, 1, 8, 0, 6, 2, 4 };
        if (i <= sizeof(array1)/sizeof(array1[0]))
        {
            cout << "\nMerge array of type int of size " << i << "\n\n";
            dump_array("Original", array1, i);
            merge_sort(array1, i);
            dump_array("PostSort", array1, i);
        }
    }

    for (size_t i = 1; i <= 10; i++)
    {
        double array2[] = { 9.9, 3.1, 5.2, 7.3, 1.4, 8.5, 0.6, 6.7, 2.8, 4.9 };
        if (i <= sizeof(array2)/sizeof(array2[0]))
        {
            cout << "\nMerge array of type double of size " << i << "\n\n";
            dump_array("Original", array2, i);
            merge_sort(array2, i);
            dump_array("PostSort", array2, i);
        }
    }

    for (size_t i = 1; i <= 10; i++)
    {
        std::string array3[] = { "nine", "three", "five", "seven", "one", "eight", "zero", "six", "two", "four" };
        if (i <= sizeof(array3)/sizeof(array3[0]))
        {
            cout << "\nMerge array type std::string of size " << i << "\n\n";
            dump_array("Original", array3, i);
            merge_sort(array3, i);
            dump_array("PostSort", array3, i);
        }
    }

    for (size_t i = 1; i <= 10; i++)
    {
        char array4[] = "jdfhbiagce";
        if (i <= sizeof(array4)/sizeof(array4[0]))
        {
            cout << "\nMerge array type char of size " << i << "\n\n";
            dump_array("Original", array4, i);
            merge_sort(array4, i);
            dump_array("PostSort", array4, i);
        }
    }

    return 0;
}

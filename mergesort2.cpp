/* http://stackoverflow.com/q/18928821 Merge sort code debugging */

#include <iostream>
using namespace std;

namespace {

int *merge(int *l, int m, int *r, int n);

void dump_array(int *a, int size)
{
    int i;
    cout << size << ": ";
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

int *merge_sort(int *a, int size)
{
    if (size <= 1)
    {
        return a;
    }

    int middle = size/2;
    int *left = new int[middle];
    int *right = new int[size - middle];
    for (int i = 0; i < middle; i++)
    {
        left[i] = a[i];
    }

    for (int j = 0; j < size - middle; j++)
    {
        right[j] = a[j + middle];
    }
    int *nleft = merge_sort(left, middle);
    int *nright = merge_sort(right, size - middle);
    int *result =  merge(nleft, middle, nright, size - middle);
    return result;
}

namespace {

int *merge(int *l, int m, int *r, int n)
{
    int *result = new int[m + n];
    int lsize = m;
    int rsize = n;
    int counter = 0;

    while (lsize > 0 || rsize > 0)
    {
        if (lsize > 0 && rsize > 0)
        {
            if (l[0] <= r[0])
            {
                result[counter] = l[0];
                counter++;
                lsize--;
                l++;
            }
            else
            {
                result[counter] = r[0];
                counter++;
                rsize--;
                r++;
            }
        }
        else if (lsize > 0)
        {
            result[counter] = l[0];
            counter++;
            lsize--;
            l++;
        }
        else if (rsize > 0)
        {
            result[counter] = r[0];
            counter++;
            rsize--;
            r++;
        }
    }
    return result;
}

};

int main()
{
    for (int i = 2; i <= 10; i++)
    {
        int array1[] = { 9, 3, 5, 7, 1, 8, 0, 6, 2, 4 };
        cout << "\nMerge array of size " << i << "\n\n";
        dump_array(array1, i);
        int *result = merge_sort(array1, i);
        dump_array(result, i);
        delete[] result;
    }
    return 0;
}

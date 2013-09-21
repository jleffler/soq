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
    cout << "-->> merge_sort:\n";
    dump_array(a, size);
    if (size <= 1)
    {
        cout << "<<-- merge_sort: early return\n";
        return a;
    }

    int middle = size/2;
    int *left = new int[middle];
    int *right = new int[size - middle];
    cout << middle << ": ";
    for (int i = 0; i < middle; i++)
    {
        left[i] = a[i];
        cout << ' ' << left[i];
    }
    cout << "\n";

    cout << (size - middle) << ": ";
    for (int j = 0; j < size - middle; j++)
    {
        right[j] = a[j + middle];
        cout << ' ' << right[j];
    }
    cout << "\n";
    cout << "MSL:\n";
    int *nleft = merge_sort(left, middle);
    cout << "NL: ";
    dump_array(nleft, middle);
    cout << "OL: ";
    dump_array(left, middle);
    cout << "OR: ";
    dump_array(right, size - middle);
    cout << "MSR:\n";
    int *nright = merge_sort(right, size - middle);
    cout << "NR: ";
    dump_array(nright, size - middle);
    cout << "NL: ";
    dump_array(nleft, middle);
    cout << "OL: ";
    dump_array(left, middle);
    cout << "OR: ";
    dump_array(right, size - middle);
    int *result =  merge(nleft, middle, nright, size - middle);
    cout << "<<-- merge_sort:\n";
    dump_array(result, size);
    return result;
}

namespace {

int *merge(int *l, int m, int *r, int n)
{
    int *result = new int[m + n];
    int lsize = m;
    int rsize = n;
    int counter = 0;
    cout << "-->> merge: (" << m << "," << n << ")\n";
    dump_array(l, m);
    dump_array(r, n);

    while (lsize > 0 || rsize > 0)
    {
        if (lsize > 0 && rsize > 0)
        {
            if (l[0] <= r[0])
            {
                result[counter] = l[0];
                cout << "C: " << counter << "; L = " << l[0] << "; LS = " << lsize << '\n';
                counter++;
                lsize--;
                l++;
            }
            else
            {
                result[counter] = r[0];
                cout << "C: " << counter << "; R = " << r[0] << "; RS = " << rsize << '\n';
                counter++;
                rsize--;
                r++;
            }
        }
        else if (lsize > 0)
        {
            result[counter] = l[0];
            cout << "C: " << counter << "; L = " << l[0] << "; LS = " << lsize << '\n';
            counter++;
            lsize--;
            l++;
        }
        else if (rsize > 0)
        {
            result[counter] = r[0];
            cout << "C: " << counter << "; R = " << r[0] << "; RS = " << rsize << '\n';
            counter++;
            rsize--;
            r++;
        }
    }
    cout << "<<-- merge:\n";
    dump_array(result, m+n);
    return result;
}

};

int main()
{
    for (int i = 2; i <= 10; i++)
    {
        int array1[] = { 9, 3, 5, 7, 1, 8, 0, 6, 2, 4 };
        cout << "\nMerge array of size " << i << "\n\n";
        int *result = merge_sort(array1, i);
        delete[] result;
    }
    return 0;
}

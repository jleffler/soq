#include <algorithm>    // sort
#include <cassert>
#include <cstring>
#include <iomanip>      // setw
#include <iostream>
#include <utility>      // swap

using namespace std;

/* rank is in range 1..N; array indexes are in range 0..N-1 */
template<class T>
static void check_partition(T *a, size_t n, size_t rank)
{
    int ok = 1;
    assert(rank >= 0 && rank <= n);
    for (size_t i = 0; i < rank; i++)
    {
        if (a[i] > a[rank])
        {
            ok = 0;
            cout << "BUG: a[" << i << "] = " << a[i]
                 << " should be no larger than a["
                 << rank << "] = " << a[rank] << "\n";
        }
    }
    for (size_t i = rank + 1; i < n; i++)
    {
        if (a[i] < a[rank])
        {
            ok = 0;
            cout << "BUG: a[" << i << "] = " << a[i]
                 << " should be no smaller than a["
                 << rank << "] = " << a[rank] << "\n";
        }
    }
    if (!ok)
        assert(0);
}

template<class T>
void printArray(char const *tag, T *a, size_t n)
{
    size_t i;
    int const maxw = 15;
    cout << tag << ": (" << n << ")";
    if (n > maxw)
        cout << '\n';
    for (i = 0; i < n; i++)
    {
        cout << ' ' << setw(3) << a[i];
        if (i % maxw == maxw - 1)
            cout << '\n';
    }
    if (i % maxw != 0)
        cout << '\n';
}

template<class T>
size_t partition(T *a, size_t n)
{
    if (n <= 1)
        return 0;
    printArray("-->> partition()", a, n);
    size_t j = n - 1;
    size_t i = 1;
    swap(a[(i + j)/2], a[0]);
    T p = a[0];
    cout << "Pivot: [" << (i + j) / 2 << "] = " << p << endl;

    do
    {
        while (i < n - 1 && a[i] < p)
            i++;
        while (j > 0 && a[j] > p)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    } while (i <= j);
    swap(a[0], a[--i]);
    printArray("<<-- partition()", a, n);
    check_partition(a, n, i);
    cout << "Returning: " << i << endl;
    return i;
}

template<class T>
T quickSelect(T *a, size_t n, size_t k)
{
    while (n > 1)
    {
        assert(k >= 0 && k < n);
        size_t j = partition(a, n);
        assert(j >= 0 && j < n);
        if (k < j)
            n = j;
        else if (k > j)
        {
            a += j;
            n -= j;
            k -= j;
        }
        else
            break;
    }
    return a[k];
}

int main()
{
    int const A[] =
    {
        96, 4, 10, -35, 55,   6, 6, 6, -67,  0,   2,  34,  6, 4,
        56, 2,  7,  -9, 45, -27, 5, 7,   8, 94, -99, -98, 99,
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    for (size_t i = 0; i < A_SIZE; i++)
    {
        int B[A_SIZE];
        int C[A_SIZE];
        memmove(B, A, sizeof(B));
        memmove(C, A, sizeof(B));
        sort(&C[0], &C[A_SIZE]);
        //printArray("Sorted", C, A_SIZE);
        cout << "Rank [" << i << "]" << endl;
        int v = quickSelect(B, A_SIZE, i);
        cout << "Rank [" << i << "] = " << v << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, A_SIZE, i);
        assert(B[i] == C[i]);
        assert(v == C[i]);
        cout << '\n';
    }
    return 0;
}


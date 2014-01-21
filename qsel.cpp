#include <algorithm>    // sort
#include <cassert>
#include <cstring>
#include <iomanip>      // setw
#include <iostream>
#include <utility>      // swap

using namespace std;

/* rank is in range 1..N; array indexes are in range 0..N-1 */
template<class T>
static void check_partition(T *a, long start, long end, long rank)
{
    int ok = 1;
    cout << "s = " << start << "; e = " << end << "; r = " << rank << endl;
    assert(start >= 0 && start < end);
    assert(rank >= start && rank <= end);
    for (long i = 0; i < rank; i++)
    {
        if (a[i] > a[rank])
        {
            ok = 0;
            cout << "BUG: a[" << i << "] = " << a[i]
                 << " should be no larger than a["
                 << rank << "] = " << a[rank] << "\n";
        }
    }
    for (long i = rank + 1; i < end; i++)
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
void printArray(char const *tag, T *A, long N)
{
    long i;
    int const maxw = 15;
    cout << tag << ": (" << N << ")";
    if (N > maxw)
        cout << '\n';
    for (i = 0; i < N; i++)
    {
        cout << ' ' << setw(3) << A[i];
        if (i % maxw == maxw - 1)
            cout << '\n';
    }
    if (i % maxw != 0)
        cout << '\n';
}

template<class T>
long partition(T *a, long N)
{
    printArray("-->> partition()", a, N);
    long j = N - 1;
    long i = 1;
    swap(a[(i + j)/2], a[0]);
    T p = a[0];
    cout << "Pivot: [" << (i + j) / 2 << "] = " << p << endl;

    do
    {
        while (i < N && a[i] < p)
            i++;
        while (j > 0 && a[j] > p)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    } while (i <= j);
    swap(a[0], a[--i]);
    printArray("<<-- partition()", a, N);
    check_partition(a, 0, N, i);
    cout << "Returning: " << i << endl;
    return i;
}

template<class T>
T quickSelect(T *input, long N, long k)
{
    long j = partition(input, N);
    if (2 < N)
    {
        if (j == k - 1)
            return input[k-1];
        else if (k < j + 1)
            return quickSelect(input, j, k);
        else
            return quickSelect(input + j, N - j, k - j);
    }
    else
        return input[k-1];
}

int main()
{
    int const A[] =
    {
        96, 4, 10, -35, 55, 6, 6, 6, -67, 0, 2, 34, 6, 4,
        56, 2,  7, -9, 45, -27, 5, 7, 8, 94, -99, -98, 99
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    for (size_t i = 1; i <= A_SIZE; i++)
    {
        int B[A_SIZE];
        int C[A_SIZE];
        memmove(B, A, sizeof(B));
        memmove(C, A, sizeof(B));
        sort(&C[0], &C[A_SIZE]);
        printArray("Sorted", C, A_SIZE);
        cout << "Rank [" << i << "]" << endl;
        int v = quickSelect(B, A_SIZE, i);
        cout << "Rank [" << i << "] = " << v << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, 0, A_SIZE, i-1);
        assert(B[i-1] == C[i-1]);
        assert(v == C[i-1]);
        cout << '\n';
    }
    return 0;
}


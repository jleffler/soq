#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>  // setw
#include <utility>  // swap

using namespace std;

static const int debug = 0;

template<class T>
static void check_partition(T *a, size_t N, size_t rank)
{
    size_t end = N - 1;
    int ok = 1;
    if (debug) cout << "e = " << end << "; r = " << rank << endl;
    assert(0 < end);
    assert(rank <= end);
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
    for (size_t i = rank + 1; i < end; i++)
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
void printArray(char const *tag, T *A, size_t N)
{
    size_t i;
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
size_t partition(T *a, size_t N)
{
    assert(N > 1);
    size_t u = N - 1;
    assert(u > 0);
    if (debug) printArray("--->> partition()", a, N);
    size_t m = 0;
    swap(a[(u) / 2], a[0]);
    T p = a[0];
    if (debug) cout << "Pivot: [" << (u+1) / 2 << "] = " << p << endl;
    if (debug) printArray("--0-- partition()", a, N);

    for (size_t i = 1; i <= u; i++)
    {
        if (a[i] < p)
        {
            ++m;
            if (debug) cout << "swap (" << i << "," << m << ")<=>(" << a[i] << "," << a[m] << ")\n";
            swap(a[i], a[m]);
            if (debug) printArray("--1-- partition()", a, N);
        }
    }

    if (debug) printArray("--2-- partition()", a, N);
    swap(a[0], a[m]);
    if (debug) printArray("<<--- partition()", a, N);
    check_partition(a, N, m);
    if (debug) cout << "Returning: " << m << endl;
    return m;
}

// u is maximum valid index in a, rather than number of elements in a
template<class T>
void Select(T *a, size_t N, size_t k)
{
    assert(N > 0);
    size_t u = N - 1;
    assert(k <= u);
    while (0 < u)
    {
        assert(k <= u);
        size_t m = partition(a, u+1);
        assert(m <= u);
        if (k <= m)
        {
            if (m <= 1)
                break;
            u = m - 1;
        }
        if (k >= m)
        {
            if (u <= m + 1)
                break;
            a += m + 1;
            u -= m + 1;
            k -= m + 1;
        }
    }
}

int main()
{
    int A[] =
    {
        96, 4, 10, -35, 55,   6, 6, 6, -67,  0,   2,  34,  6, 4,
        56, 2,  7,  -9, 45, -27, 5, 7,   8, 94, -99, -98, 99,
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    printArray("Initial", A, A_SIZE-1);
    for (size_t i = 0; i < A_SIZE; i++)
    {
        int B[A_SIZE];
        memmove(B, A, sizeof(B));
        cout << "Rank [" << i << "]" << endl;
        Select(B, A_SIZE, i);
        cout << "Rank [" << i << "] = " << B[i] << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, A_SIZE, i);
        cout << '\n';
    }
    return 0;
}


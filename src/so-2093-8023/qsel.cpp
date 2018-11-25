/* SO 2093-8023 */
#include <algorithm>    // sort
#include <cassert>
#include <cstring>
#include <iomanip>      // setw
#include <iostream>
#include <utility>      // swap

using namespace std;

static int const debug = 0;

/* rank is in range 1..N; array indexes are in range 0..N-1 */
template<typename T>
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

template<typename T>
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

template<typename T>
size_t partition(T *a, size_t n)
{
    if (n <= 1)
        return 0;
    if (debug) printArray("-->> partition()", a, n);
    size_t j = n - 1;
    size_t i = 1;
    swap(a[n/2], a[0]);
    T p = a[0];
    if (debug) cout << "Pivot: [" << n / 2 << "] = " << p << endl;

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
    if (debug) printArray("<<-- partition()", a, n);
    check_partition(a, n, i);
    if (debug) cout << "Returning: " << i << endl;
    return i;
}

template<typename T>
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
    // Works for signed integer types except signed char.
    // For signed char, the algorithm is fine; the printing thinks the
    // value should be printed as characters instead of integers.  Is
    // there a way around that, other than altering the type (e.g. by
    // adding INTMAX_C(0) or similar) to the values being printed?
    typedef short Data;
    Data const A[] =
    {
        96, 4, 10, -35, 55,   6, 6, 6, -67,  0,   2,  34,  6, 4,
        56, 2,  7,  -9, 45, -27, 5, 7,   8, 94, -99, -98, 99,
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    printArray("Input", A, A_SIZE);

    Data C[A_SIZE];
    memmove(C, A, sizeof(C));
    sort(&C[0], &C[A_SIZE]);
    printArray("Sorted", C, A_SIZE);
    cout << '\n';

    for (size_t i = 0; i < A_SIZE; i++)
    {
        Data B[A_SIZE];
        memmove(B, A, sizeof(B));
        if (debug) cout << "Rank [" << i << "]" << endl;
        Data v = quickSelect(B, A_SIZE, i);
        cout << "Rank [" << i << "] = " << v << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, A_SIZE, i);
        assert(B[i] == C[i]);
        assert(v == C[i]);
        cout << '\n';
    }

    return 0;
}


#include <cassert>
#include <cstdlib>  // rand, srand
#include <cstring>
#include <ctime>    // time
#include <iomanip>  // setw
#include <iostream>
#include <utility>  // swap

using namespace std;

static const int debug = 0;

static size_t RandomInteger(size_t lo, size_t hi)
{
    assert(hi > lo);
    size_t range = hi - lo + 1;
    size_t max_r = RAND_MAX - (RAND_MAX % range);
    size_t r;
    while ((r = rand()) > max_r)
        ;
    r = (r % range + lo);
    assert(lo <= r && r <= hi);
    return r;
}

template<class T>
static void check_partition(T *a, size_t N, size_t rank)
{
    size_t end = N - 1;
    int ok = 1;
    if (debug) cout << "e = " << end << "; r = " << rank << endl;
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
    if (debug) printArray("--->> partition()", a, N);
    size_t m = 0;
    //swap(a[(N-1) / 2], a[0]);
    swap(a[RandomInteger(0, N-1)], a[0]);
    T p = a[0];
    if (debug) cout << "Pivot: [" << (N-1) / 2 << "] = " << p << endl;
    if (debug) printArray("--0-- partition()", a, N);

    for (size_t i = 1; i < N; i++)
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

template<class T>
void Select(T *a, size_t N, size_t k)
{
    assert(N > 0);
    while (1 < N)
    {
        assert(k < N);
        size_t m = partition(a, N);
        assert(m < N);
        if (k <= m)
        {
            if (m <= 1)
                break;
            N = m;
        }
        if (k >= m)
        {
            if (N < m + 3)
                break;
            a += m + 1;
            N -= m + 1;
            k -= m + 1;
        }
    }
}

int main(int argc, char **argv)
{
    long t = time(0);
    if (argc > 1)
        t = atol(argv[1]);
    cout << "Seed: " << t << "\n";
    srand(t);

    int A[] =
    {
        96, 4, 10, -35, 55,   6, 6, 6, -67,  0,   2,  34,  6, 4,
        56, 2,  7,  -9, 45, -27, 5, 7,   8, 94, -99, -98, 99,
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    for (size_t m = 1; m <= A_SIZE; m++)
    {
        printArray("Initial", A, m);
        for (size_t r = 0; r < m; r++)
        {
            int B[A_SIZE];
            memmove(B, A, sizeof(B));
            if (debug) cout << "Rank [" << r << "]" << endl;
            Select(B, m, r);
            cout << "Rank [" << r << "] = " << B[r] << endl;
            printArray("Finish", B, m);
            check_partition(B, m, r);
            cout << '\n';
        }
    }
    return 0;
}


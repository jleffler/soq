#include <algorithm>    // sort
#include <cassert>
#include <cstdlib>      // rand, srand
#include <cstring>
#include <ctime>        // time
#include <iomanip>      // setw
#include <iostream>
#include <utility>      // swap

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
static void check_partition(T *a, size_t n, size_t rank)
{
    size_t end = n - 1;
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
    assert(n > 1);
    if (debug) printArray("--->> partition()", a, n);
    size_t m = 0;
    swap(a[RandomInteger(0, n-1)], a[0]);
    T p = a[0];
    if (debug) cout << "Pivot: [" << (n-1) / 2 << "] = " << p << endl;
    if (debug) printArray("--0-- partition()", a, n);

    for (size_t i = 1; i < n; i++)
    {
        if (a[i] < p)
        {
            ++m;
            if (debug) cout << "swap (" << i << "," << m << ")<=>(" << a[i] << "," << a[m] << ")\n";
            swap(a[i], a[m]);
            if (debug) printArray("--1-- partition()", a, n);
        }
    }

    if (debug) printArray("--2-- partition()", a, n);
    swap(a[0], a[m]);
    if (debug) printArray("<<--- partition()", a, n);
    check_partition(a, n, m);
    if (debug) cout << "Returning: " << m << endl;
    return m;
}

template<class T>
void quickSelect(T *a, size_t n, size_t k)
{
    assert(n > 0);
    while (n > 1)
    {
        assert(k < n);
        size_t m = partition(a, n);
        assert(m < n);
        if (k <= m)
        {
            if (m <= 1)
                break;
            n = m;
        }
        if (k >= m)
        {
            if (n < m + 3)
                break;
            a += m + 1;
            n -= m + 1;
            k -= m + 1;
        }
    }
}

template<class T>
static void test_select(T *a, size_t n)
{
    for (size_t m = 1; m <= n; m++)
    {
        printArray("Initial", a, m);
        for (size_t r = 0; r < m; r++)
        {
            T *b = new int[n];
            T *c = new int[n];
            memmove(b, a, n * sizeof(*a)); // C-think
            memmove(c, a, n * sizeof(*a)); // C-think
            sort(&c[0], &c[m]);
            //printArray("Sorted", c, m);
            if (debug) cout << "Rank [" << r << "]" << endl;
            quickSelect(b, m, r);
            cout << "Rank [" << r << "/" << m << "] = " << b[r] << endl;
            printArray("Finish", b, m);
            check_partition(b, m, r);
            assert(c[r] == b[r]);
            cout << '\n';
            delete[] b;
            delete[] c;
        }
    }
}

template<class T>
static void shuffle(T *a, size_t n)
{
    /*
    ** Floyd's F2 algorithm from More Programming Pearls Chapter 13
    **
    ** Shuffle array X[1..M]:
    **     for I := M downto 2 do
    **         J := RandInt(1, I)
    **         Swap(X[J], X[I])
    */
    for (size_t i = n-1; i > 1; i--)
        swap(a[RandomInteger(0, i)], a[i]);
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

    test_select(A, A_SIZE);
    shuffle(A, A_SIZE);
    test_select(A, A_SIZE);

    return 0;
}


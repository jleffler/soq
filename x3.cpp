#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>  // setw
#include <utility>  // swap

using namespace std;

/* rank is in range 1..N; array indexes are in range 0..N-1 */
template<class T>
static void check_partition(T *a, size_t start, size_t end, size_t rank)
{
    int ok = 1;
    cout << "s = " << start << "; e = " << end << "; r = " << rank << endl;
    assert(start >= 0 && start < end);
    assert(rank >= start && rank <= end);
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
    printArray("--->> partition()", a, N);
    size_t j = N - 1;
    size_t i = 1;
    swap(a[(i + j)/2], a[0]);
    T p = a[0];
    cout << "Pivot: [" << (i + j) / 2 << "] = " << p << endl;
    printArray("--0-- partition()", a, N);

    do
    {
        while (i < N && a[i] < p)
            i++;
        while (j > 0 && a[j] > p)
            j--;
        if (i <= j)
        {
            cout << "swap (" << i << "," << j << ")<=>(" << a[i] << "," << a[j] << ")\n";
            swap(a[i++], a[j--]);
            printArray("--1-- partition()", a, N);
        }
    } while (i <= j);

    printArray("--2-- partition()", a, N);
    swap(a[0], a[--i]);

    printArray("--3-- partition()", a, N);
    cout << "<<--- partition(): " << i << endl;
    return i;
}

template<class T>
T quickSelect(T *input, size_t N, size_t k)
{
    size_t j = partition(input, N);
    size_t pivot = j + 1;
    if (2 < N)
    {
        if (j == k - 1)
        {
            cout << "<<-- quickSelect() - 1: " << input[j] << endl;
            return input[j];
        }
        else if (k < pivot)
        {
            T value = quickSelect(input, j, k);
            cout << "<<-- quickSelect() - 2: " << value << endl;
            return value;
        }
        else
        {
            T value = quickSelect(input + j, N - j, k - j);
            cout << "<<-- quickSelect() - 3: " << value << endl;
            return value;
        }
    }
    else
    {
        cout << "<<-- quickSelect() - 5: " << input[k-1] << endl;
        return input[k-1];
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
    for (size_t i = 1; i <= A_SIZE; i++)
    {
        int B[A_SIZE];
        memmove(B, A, sizeof(B));
        cout << "Rank [" << i << "]" << endl;
        cout << "Rank [" << i << "] = " << quickSelect(B, A_SIZE, i) << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, 0, A_SIZE, i-1);
        cout << '\n';
    }
    return 0;
}


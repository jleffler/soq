#include <cassert>
#include <cstring>
#include <iostream>
#include <utility>  // swap

using namespace std;

template<class T>
static void check_partition(T *a, long start, long end, long rank)
{
    int ok = 1;
    assert(start >= 0 && start < end);
    assert(rank >= start && rank < end);
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
    cout << tag << ": (" << N << ")";
    for (long i = 0; i < N; i++)
        cout << ' ' << A[i];
    cout << '\n';
}

template<class T>
long partition(T *a, long N)
{
    long j = N - 1;
    long i = 1;

    printArray("-->> partition()", a, N);
    swap(a[(i + j)/2], a[0]);
    T p = a[0];
    cout << "Pivot: [" << (i + j) / 2 << "] = " << p << endl;

    do
    {
        while (a[i] < p)
            i++;
        while (a[j] > p)
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
    long pivot = j + 1;
    if (2 < N)
    {
        if (j == k - 1)
        {
            return input[j];
        }
        else if (k < pivot)
        {
            return quickSelect(input, j, k);
        }
        else
        {
            return quickSelect(input + j, N - j, k - j);
        }
    }
    else
    {
        if (j == k - 1)
        {
            return input[j];
        }
        else
        {
            return input[0];
        }
    }
}

int main()
{
    int A[] =
    {
        100, 4, 10, -35, 55, 6, 6, 6, -67, 0, 2, 34, 6, 4,
        56, 2, 7, -9, 45, -27, 5, 7, 8, 94, -478, -98, 13456
    };
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    for (long i = 2; i < 20; i += 3)
    {
        int B[A_SIZE];
        memmove(B, A, sizeof(B));
        cout << "Rank [" << i << "]" << endl;
        cout << "Rank [" << i << "] = " << quickSelect(B, A_SIZE, i) << endl;
        printArray("Finish", B, A_SIZE);
        check_partition(B, 0, A_SIZE, i-1);
    }
    return 0;
}


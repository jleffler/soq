#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

template<class T>
void printArray(char const *tag, T *A, long N)
{
    cout << tag << ": (" << N << ")";
    for (long i = 0; i < N; i++)
        cout << ' ' << A[i];
    cout << '\n';
}

template<class T>
long partition(T *a, T &p, long N)
{
    long i = 0, j = N - 1;
    T temp;

    printArray("-->>partition", a, N);
    p = a[(i + j) / 2];
    cout << p << endl;

    do {
        while (a[i] < p) { i++; }
        while (a[j] > p) { j--; }
        if (i <= j) {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++; j--;
        }
    } while (i <= j);
    printArray("<<--partition", a, N);
    return ++j;
}


template<class T>
T quickSelect(T *input, T &p, long N, long k)
{
    long j = partition(input, p, N);
    long pivot = j + 1;
    if (2 < N) {
        if (j == k - 1) {
            return p;
        } else if (k < pivot) {
            return quickSelect(input, p, j, k);
        } else {
            return quickSelect(input + j, p, N - j, k - j);
        }
    } else {
        if (j == k - 1) {
            return p;
        } else {
            return input[1];
        }
    }
}

int main()
{
    int A[] = {100, 4, 10, -35, 55, 6, 6, 6, -67, 0, 2, 34, 6, 4, 56, 2, 7, -9, 45, -27, 5, 7, 8, 94, -478, -98, 13456};
    const size_t A_SIZE = sizeof(A) / sizeof(A[0]);
    for (long i = 2; i < 20; i += 3)
    {
        int B[A_SIZE];
        memmove(B, A, sizeof(B));
        cout << "Rank [" << i << "]" << endl;
        int pivot = A[0];
        cout << "Rank [" << i << "] = " << quickSelect(A, pivot, A_SIZE, 2) << endl;
        printArray("Finish", B, A_SIZE);
    }
    return 0;
}

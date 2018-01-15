/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Modified Binary Search - for ranges with same value
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

/* SO 3514-7784 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Pair
{
    int lo;
    int hi;
} Pair;

extern Pair BinSearch_D(int N, const int X[N], int T);
extern int BinSearch_A(int N, const int X[N], int T);
extern int BinSearch_B(int N, const int X[N], int T);
extern int BinSearch_C(int N, const int X[N], int T);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_modbinsearch_c[];
const char jlss_id_modbinsearch_c[] = "@(#)$Id$";
#endif /* lint */

/*
** Programming Pearls, 1st Edn, 8.3 Major Surgery - Binary Search
**
** In each fragment, P contains the result (0 indicates 'not found').
**
** Search for T in X[1..N] - BinSearch-A
**
**      L := 1; U := N
**      loop
**          # Invariant: if T is in X, it is in X[L..U]
**          if L > U then
**              P := 0; break;
**          M := (L+U) div 2
**          case
**              X[M] < T:  L := M+1
**              X[M] = T:  P := M; break
**              X[M] > T:  U := M-1
**
** Search for first occurrence of T in X[1..N] - BinSearch-B
**
**      L := 0; U := N+1
**      while L+1 != U do
**          # Invariant: X[L] < T and X[U] >= T and L < U
**          M := (L+U) div 2
**          if X[M] < T then
**              L := M
**          else
**              U := M
**      # Assert: L+1 = U and X[L] < T and X[U] >= T
**      P := U
**      if P > N or X[P] != T then P := 0
**
** Search for last occurrence of T in X[1..N] - BinSearch-C
** Adapted from BinSearch-B (not in Programming Pearls)
**
**      L := 0; U := N+1
**      while L+1 != U do
**          # Invariant: X[L] <= T and X[U] > T and L < U
**          M := (L+U) div 2
**          if X[M] <= T then
**              L := M
**          else
**              U := M
**      # Assert: L+1 = U and X[L] < T and X[U] >= T
**      P := L
**      if P = 0 or X[P] != T then P := 0
**
** C implementations of these deal with X[0..N-1] instead of X[1..N],
** and return -1 when the value is not found.
*/

int BinSearch_A(int N, const int X[N], int T)
{
    int L = 0;
    int U = N-1;
    while (1)
    {
        /* Invariant: if T is in X, it is in X[L..U] */
        if (L > U)
            return -1;
        int M = (L + U) / 2;
        if (X[M] < T)
            L = M + 1;
        else if (X[M] > T)
            U = M - 1;
        else
            return M;
    }
    assert(0);
}

int BinSearch_B(int N, const int X[N], int T)
{
    int L = -1;
    int U = N;
    while (L + 1 != U)
    {
        /* Invariant: X[L] < T and X[U] >= T and L < U */
        int M = (L + U) / 2;
        if (X[M] < T)
            L = M;
        else
            U = M;
    }
    assert(L+1 == U && (L == -1 || X[L] < T) && (U >= N || X[U] >= T));
    int P = U;
    if (P >= N || X[P] != T)
        P = -1;
    return P;
}

int BinSearch_C(int N, const int X[N], int T)
{
    int L = -1;
    int U = N;
    while (L + 1 != U)
    {
        /* Invariant: X[L] <= T and X[U] > T and L < U */
        int M = (L + U) / 2;
        if (X[M] <= T)
            L = M;
        else
            U = M;
    }
    assert(L+1 == U && (L == -1 || X[L] <= T) && (U >= N || X[U] > T));
    int P = L;
    if (P < 0 || X[P] != T)
        P = -1;
    return P;
}

/*
** If value is found in the array (elements array[0]..array[a_size-1]),
** then the returned Pair identifies the lowest index at which value is
** found (in lo) and the highest value (in hi).  The lo and hi values
** will be the same if there's only one entry that matches.
**
** If the value is not found in the array, the pair (-1, -1) is returned.
**
** -- If the values in the array are unique, then this is not the binary
**    search to use.
** -- If it doesn't matter which one of multiple identical keys are
**    returned, this is not the binary search to use.
**
** ------------------------------------------------------------------------
**
** Another way to look at this is:
** -- Lower bound is largest  index lo such that a[lo] < value and a[lo+1] >= value
** -- Upper bound is smallest index hi such that a[hi] > value and a[hi-1] <= value
** -- Range is then lo+1..hi-1.
** -- If the values is not found, the value (-1, -1) is returned.
**
** Let's review:
** == Data: 2, 3, 3, 3, 5, 5, 6, 8 (N = 8)
** Searches and results:
** == 1 .. lo = -1, hi = -1  R = (-1, -1) not found
** == 2 .. lo = -1, hi =  1  R = ( 0,  0) found
** == 3 .. lo =  0, hi =  4  R = ( 1,  3) found
** == 4 .. lo = -1, hi = -1  R = (-1, -1) not found
** == 5 .. lo =  3, hi =  6  R = ( 4,  5) found
** == 6 .. lo =  5, hi =  7  R = ( 6,  6) found
** == 7 .. lo = -1, hi = -1  R = (-1, -1) not found
** == 8 .. lo =  6, hi =  8  R = ( 7,  7) found
** == 9 .. lo = -1, hi = -1  R = (-1, -1) not found
**
** Code created by combining BinSearch_B() and BinSearch_C() into a
** single function.  The two separate ranges of values to be searched
** (L_lo:L_hi vs U_lo:U_hi) are almost unavoidable as if there are
** repeats in the data, the values diverge.
*/

Pair BinSearch_D(int N, const int X[N], int T)
{
    int L_lo = -1;
    int L_hi = N;
    int U_lo = -1;
    int U_hi = N;

    while (L_lo + 1 != L_hi || U_lo + 1 != U_hi)
    {
        if (L_lo + 1 != L_hi)
        {
            /* Invariant: X[L_lo] < T and X[L_hi] >= T and L_lo < L_hi */
            int L_md = (L_lo + L_hi) / 2;
            if (X[L_md] < T)
                L_lo = L_md;
            else
                L_hi = L_md;
        }
        if (U_lo + 1 != U_hi)
        {
            /* Invariant: X[U_lo] <= T and X[U_hi] > T and U_lo < U_hi */
            int U_md = (U_lo + U_hi) / 2;
            if (X[U_md] <= T)
                U_lo = U_md;
            else
                U_hi = U_md;
        }
    }

    assert(L_lo+1 == L_hi && (L_lo == -1 || X[L_lo] < T) && (L_hi >= N || X[L_hi] >= T));
    int L = L_hi;
    if (L >= N || X[L] != T)
        L = -1;
    assert(U_lo+1 == U_hi && (U_lo == -1 || X[U_lo] <= T) && (U_hi >= N || X[U_hi] > T));
    int U = U_lo;
    if (U < 0 || X[U] != T)
        U = -1;

    return (Pair) { .lo = L, .hi = U };
}

/* Test support code */

static void check_sorted(const char *a_name, int size, const int array[size])
{
    int ok = 1;
    for (int i = 1; i < size; i++)
    {
        if (array[i-1] > array[i])
        {
            fprintf(stderr, "Out of order: %s[%d] = %d, %s[%d] = %d\n",
                    a_name, i-1, array[i-1], a_name, i, array[i]);
            ok = 0;
        }
    }
    if (!ok)
        exit(1);
}

static void dump_array(const char *a_name, int size, const int array[size])
{
    printf("%s Data: ", a_name);
    for (int i = 0; i < size; i++)
        printf(" %2d", array[i]);
    putchar('\n');
}

/* This interface could be used instead of the Pair returned by BinSearch_D() */
static void linear_search(int size, const int array[size], int value, int *lo, int *hi)
{
    *lo = *hi = -1;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            if (*lo == -1)
                *lo = i;
            *hi = i;
        }
        else if (array[i] > value)
            break;
    }
}

static void test_abc_search(const char *a_name, int size, const int array[size])
{
    dump_array(a_name, size, array);
    check_sorted(a_name, size, array);

    for (int i = array[0] - 1; i < array[size - 1] + 2; i++)
    {
        int a_idx = BinSearch_A(size, array, i);
        int b_idx = BinSearch_B(size, array, i);
        int c_idx = BinSearch_C(size, array, i);
        printf("T %2d:  A %2d,  B %2d,  C %2d\n", i, a_idx, b_idx, c_idx);
        assert(a_idx != -1 || (b_idx == -1 && c_idx == -1));
        assert(b_idx != -1 || (c_idx == -1 && a_idx == -1));
        assert(c_idx != -1 || (a_idx == -1 && b_idx == -1));
        assert(a_idx == -1 || (array[a_idx] == i && array[b_idx] == i && array[c_idx] == i));
        assert(a_idx == -1 || (a_idx >= b_idx && a_idx <= c_idx));
        int lo;
        int hi;
        linear_search(size, array, i, &lo, &hi);
        assert(lo == b_idx && hi == c_idx);
    }
}

static void test_d_search(const char *a_name, int size, const int array[size], const Pair results[])
{
    dump_array(a_name, size, array);
    check_sorted(a_name, size, array);

    for (int i = array[0] - 1, j = 0; i < array[size - 1] + 2; i++, j++)
    {
        Pair result = BinSearch_D(size, array, i);
        printf("%2d: (%d, %d) vs (%d, %d)\n", i, result.lo, result.hi, results[j].lo, results[j].hi);
        int lo;
        int hi;
        linear_search(size, array, i, &lo, &hi);
        assert(lo == result.lo && hi == result.hi);
    }
}

int main(void)
{
    int A[] = { 1, 2, 2, 4, 5, 5, 5, 5, 5, 6, 8, 8, 9, 10 };
    enum { A_SIZE = sizeof(A) / sizeof(A[0]) };

    test_abc_search("A", A_SIZE, A);

    int B[] = { 10, 12, 12, 12, 14, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 18, 18, 18, 19, 19, 19, 19, };
    enum { B_SIZE = sizeof(B) / sizeof(B[0]) };

    test_abc_search("B", B_SIZE, B);

    int C[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, };
    enum { C_SIZE = sizeof(C) / sizeof(C[0]) };

    test_abc_search("C", C_SIZE, C);

    /* Results for BinSearch_D() on array A */
    static const Pair results_A[] =
    {
        { -1, -1 }, {  0,  0 }, {  1,  2 },
        { -1, -1 }, {  3,  3 }, {  4,  8 },
        {  9,  9 }, { -1, -1 }, { 10, 11 },
        { 12, 12 }, { 13, 13 }, { -1, -1 },
    };

    test_d_search("A", A_SIZE, A, results_A);

    int D[] = { 2, 3, 3, 3, 5, 5, 6, 8 };
    enum { D_SIZE = sizeof(D) / sizeof(D[0]) };
    static const Pair results_D[] =
    {
        { -1, -1 }, {  0,  0 }, {  1,  3 },
        { -1, -1 }, {  4,  5 }, {  6,  6 },
        { -1, -1 }, {  7,  7 }, { -1, -1 },
    };

    test_d_search("D", D_SIZE, D, results_D);

    return 0;
}

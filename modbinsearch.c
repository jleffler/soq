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

/* SO 35147784 */

#include "posixver.h"
#include "stderr.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char optstr[] = "hV";
static const char usestr[] = "[-hV]";
static const char hlpstr[] = 
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

typedef struct Pair
{
    size_t lo;
    size_t hi;
} Pair;

extern Pair modbinsearch(const int *array, size_t a_size, int value);
extern int BinSearch_A(int N, int X[N], int T);
extern int BinSearch_B(int N, int X[N], int T);
extern int BinSearch_C(int N, int X[N], int T);

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_modbinsearch_c[];
const char jlss_id_modbinsearch_c[] = "@(#)$Id$";
#endif /* lint */

/*
** If value is found in the array (elements array[0]..array[a_size-1]),
** then the returned Pair identifies the lowest index at which value is
** found (in lo) and the highest value (in hi).  The values will be the
** same if there's only one entry that matches.
**
** If value is not found in the array, then the index before (at) which
** value should be inserted is returned in hi, and lo is set to hi+1.
**
** -- If the values in the array are unique, then this is not the binary
**    search to use.
** -- If it doesn't matter which one of multiple identical keys are
**    returned, this is not the binary search to use.
*/

/*
** The following description requires a different interpretation of the
** rules - it is not compatible with the previous definition.
**
** Another way to look at this is:
** -- Lower bound is largest  index lo such that a[lo] < value and a[lo+1] >= value
** -- Upper bound is smallest index hi such that a[hi] > value and a[hi-1] <= value
** -- Range is then lo+1..hi-1.
*/

/*
** Programming Pearls, 1st Edn, 8.3 Major Surgery - Binary Search
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
** C implementations of these deal with X[0..N-1] instead of X[1..N]
*/

int BinSearch_A(int N, int X[N], int T)
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

int BinSearch_B(int N, int X[N], int T)
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

int BinSearch_C(int N, int X[N], int T)
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

Pair modbinsearch(const int *array, size_t a_size, int value)
{
    assert(a_size < SIZE_MAX);
    Pair result = { 1, 0 };
    /* Deal with edge cases */
    if (a_size == 0)
        return result;
    else if (value < array[0])
        return result;
    else if (value > array[a_size  - 1])
        return (Pair) { .lo = a_size + 1, .hi = a_size };

    size_t lo = 0;
    size_t hi = a_size - 1;

    assert(array[lo] <= value && array[hi] >= value);
    /*
    ** Conceptually, array[-1] < value and array[a_size] > value
    ** The out of bounds elements will never be accessed
    **
    ** Pre-condition: foreach (i in 0..a_size-2) assert(array[i] <= array[i+1])
    ** aka - the data in array is sorted.
    **
    ** Loop invariant (inadequate):
    ** If value is in array, it is in array[lo]..array[hi].
    ** Objective:
    **  If found -
    **      array[lo]   == value && array[hi]   == value &&
    **      array[lo-1] <  value && array[hi+1] >  value &&
    **      lo <= hi
    **  If not found -
    **      array[hi] > value && array[hi-1] < value
    **      and lo = hi + 1
    */
    while (lo < hi)
    {
        size_t md = (hi - lo) / 2 + lo;
        //if (lo == 0 || array[lo] > value)
        //{
        //}
        if (array[md] > value)
        {
            /* High point is before md */
            hi = md - 1;
        }
        else if (array[md] < value)
        {
            /* Low point is after md */
            lo = md + 1;
        }
        else
        {
            /* Low point is at or before lo */
            /* High point is at or after hi */
        }
    }

    return result;
}

static void check_sorted(int size, int array[size])
{
    bool ok = true;
    for (int i = 1; i < size; i++)
    {
        if (array[i-1] > array[i])
        {
            fprintf(stderr, "Out of order: A[%d] = %d, A[%d] = %d\n", i-1, array[i-1], i, array[i]);
            ok = false;
        }
    }
    if (!ok)
        exit(1);
}

static void test_array(int size, int array[size])
{
    printf("Data: ");
    for (int i = 0; i < size; i++)
        printf(" %2d", array[i]);
    putchar('\n');
    check_sorted(size, array);

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
    }
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    int a[] = { 1, 2, 2, 4, 5, 5, 5, 5, 5, 6, 8, 8, 9, 10 };
    enum { A_SIZE = sizeof(a) / sizeof(a[0]) };

    test_array(A_SIZE, a);

    int b[] = { 10, 12, 12, 12, 14, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 18, 18, 18, 19, 19, 19, 19, };
    enum { B_SIZE = sizeof(b) / sizeof(b[0]) };

    test_array(B_SIZE, b);

    int c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, };
    enum { C_SIZE = sizeof(c) / sizeof(c[0]) };

    test_array(C_SIZE, c);

#if 0
    static const struct Results
    {
        size_t lo;
        size_t hi;
    } results[] =
    {
        {  1,  0 },
        {  0,  0 },
        {  1,  2 },
        {  4,  3 },
        {  3,  3 },
        {  4,  8 },
        {  9,  9 },
        { 11, 10 },
        { 10, 11 },
        { 12, 12 },
        { 13, 13 },
        { 14, 13 },
    };
#endif

#if 0
    for (int i = a[0] - 1; i < a[A_SIZE - 1] + 2; i++)
    {
        Pair result = modbinsearch(a, A_SIZE, i);
        printf("%2d: (%zu, %zu) vs (%zu, %zu)\n", i, result.lo, result.hi, results[i].lo, results[i].hi);
    }
#endif

    return 0;
}

/* SO 4178-6918 Quick Sort Again */
/* Common monitoring code */

#ifndef QS_MON_H_INCLUDED
#define QS_MON_H_INCLUDED

extern void quicksort(int *data, int start, int end);
extern void dump_data(const char *tag, int *data, int start, int end);
extern void check_sorted(int *data, int lo, int hi);

static inline void swap_ints(int *A, int i, int j)
{
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

#endif /* QS_MON_H_INCLUDED */

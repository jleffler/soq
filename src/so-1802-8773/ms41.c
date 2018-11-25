/* SO 1802-8773: Merge Sort */
/* Genericized Merge Sort */

//#include "mergesort.h"
#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <stddef.h>

typedef int (*Comparator)(const void *vp1, const void *vp2);
extern void merge_sort(void *array, size_t size, size_t arrlen, Comparator cmp);

#endif /* MERGESORT_H_INCLUDED */

#include <string.h>

#undef DEBUG

/* Debug */
#ifdef DEBUG
static void enter_func(const char *func);
static void exit_func(const char *func);
#else
#define enter_func(f)       ((void)0)
#define exit_func(f)        ((void)0)
#endif

/*
function merge(left, right)
   var list result
    while length(left) > 0 and length(right) > 0
        if first(left) ≤ first(right)
            append first(left) to result
            left = rest(left)
        else
            append first(right) to result
            right = rest(right)
    end while

    # You know that one of left and right is empty
    # Copy the rest of the data from the other
    while length(left) > 0
        append first(left) to result
        left = rest(left)
    end while
    while length(right) > 0
        append first(right) to result
        right = rest(right)
    end while
    return result
end function
*/

static void merge(void *left, size_t size, size_t l_len, void *right,
                  size_t r_len, void *output, Comparator cmp)
{
    size_t r_pos = 0;
    size_t l_pos = 0;
    char  *l_base = left;
    char  *r_base = right;
    char  *o_base = output;
    enter_func(__func__);
    while (r_pos < r_len && l_pos < l_len)
    {
        if ((*cmp)(r_base, l_base) < 0)
        {
            memmove(o_base, r_base, size);
            o_base += size;
            r_base += size;
            r_pos++;
        }
        else
        {
            memmove(o_base, l_base, size);
            o_base += size;
            l_base += size;
            l_pos++;
        }
    }
    /* Only one of these conditions is active */
    if (r_pos < r_len)
        memmove(o_base, r_base, (r_len - r_pos) * size);
    if (l_pos < l_len)
        memmove(o_base, l_base, (l_len - l_pos) * size);
    exit_func(__func__);
}

/*
function merge_sort(m)
    if length(m) ≤ 1
        return m
    var list left, right, result

    var integer middle = length(m) / 2
    for each x in m up to middle
        add x to left
    for each x in m after middle
        add x to right
    left = merge_sort(left)
    right = merge_sort(right)
    result = merge(left, right)
    return result
*/

void merge_sort(void *array, size_t size, size_t arrlen, Comparator cmp)
{
    if (arrlen <= 1)
        return;

    char *base = array;
    size_t mid = arrlen / 2;
    size_t l_len = mid;
    size_t r_len = arrlen - mid;
    char l_data[l_len * size];
    char r_data[r_len * size];

    enter_func(__func__);
    memmove(l_data, base, l_len * size);
    memmove(r_data, base + l_len * size, r_len * size);
    merge_sort(l_data, size, l_len, cmp);
    merge_sort(r_data, size, r_len, cmp);
    merge(l_data, size, l_len, r_data, r_len, array, cmp);
    exit_func(__func__);
}

/* Test code */
#include <stdio.h>

#ifdef DEBUG
static void enter_func(const char *func)
{
    printf("-->> %s\n", func);
}

static void exit_func(const char *func)
{
    printf("<<-- %s\n", func);
}
#endif

struct stability
{
    int  key;
    int  index;
};

static void dump_int_array(const char *tag, int *array, size_t len)
{
    printf("%-8s", tag);
    for (size_t i = 0; i < len; i++)
        printf(" %2d", array[i]);
    putchar('\n');
}

static void dump_dbl_array(const char *tag, double *array, size_t len)
{
    int pad = printf("%-8s (%zu): ", tag, len);
    for (size_t i = 0; i < len; i++)
    {
        if (i > 0 && i % 7 == 0)
            printf("%*s", pad, "");
        printf(" %7.2f", array[i]);
        if (i % 7 == (7 - 1))
            putchar('\n');
    }
    if (len % 7 != 0)
        putchar('\n');
}

static void dump_stability_array(const char *tag, const struct stability *array, size_t len)
{
    size_t columns = 6;
    int pad = printf("%-8s (%zu): ", tag, len);
    for (size_t i = 0; i < len; i++)
    {
        if (i > 0 && i % columns == 0)
            printf("%*s", pad, "");
        printf(" %3d (%3d)", array[i].key, array[i].index);
        if (i % columns == (columns - 1))
            putchar('\n');
    }
    if (len % columns != 0)
        putchar('\n');
}

static int cmp_int(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return +1;
    else
        return 0;
}

static int cmp_dbl(const void *vp1, const void *vp2)
{
    double v1 = *(double *)vp1;
    double v2 = *(double *)vp2;
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return +1;
    else
        return 0;
}

static int cmp_stability(const void *vp1, const void *vp2)
{
    const struct stability *v1 = vp1;       /* C not C++ */
    const struct stability *v2 = vp2;       /* C not C++ */
    if (v1->key < v2->key)
        return -1;
    else if (v1->key > v2->key)
        return +1;
    else
        return 0;
}

int main(void)
{
    int array[] = { 38, 27, 43, 3, 9, 82, 10 };
    size_t arrlen = sizeof(array) / sizeof(array[0]);

    dump_int_array("Before:", array, arrlen);
    merge_sort(array, sizeof(array[0]), arrlen, cmp_int);
    dump_int_array("After:", array, arrlen);

    double d_array[] =
    {
        /* random -n 35 -F '%6.2f' -f 100 999 | commalist -B 8 -n 7 */
        /* Repeat middle row deliberately */
        860.35, 138.65, 167.09, 861.15, 100.22, 635.50, 197.92,
        479.18, 685.14, 713.16, 530.49, 606.27, 367.75, 162.94,
        647.05, 279.78, 936.03, 758.85, 171.60, 780.44, 280.32,
        647.05, 279.78, 936.03, 758.85, 171.60, 780.44, 280.32,
        690.25, 881.14, 569.99, 893.91, 627.07, 312.78, 191.45,
        767.00, 607.65, 903.29, 501.17, 178.12, 921.82, 619.55,
    };
    size_t d_arrlen = sizeof(d_array) / sizeof(d_array[0]);

    dump_dbl_array("Before", d_array, d_arrlen);
    merge_sort(d_array, sizeof(d_array[0]), d_arrlen, cmp_dbl);
    dump_dbl_array("After", d_array, d_arrlen);

    struct stability s_array[] =
    {
        /* Lots of repeats in the keys */
        /*
        paste -d ',' <(random -n 97 100 120) <(range 100 196) |
        sed 's%.*%{ & }%;s%,%, %' |
        commalist -B 8 -n 4
        */
        { 104, 100 }, { 106, 101 }, { 102, 102 }, { 102, 103 },
        { 112, 104 }, { 105, 105 }, { 107, 106 }, { 101, 107 },
        { 112, 108 }, { 101, 109 }, { 101, 110 }, { 116, 111 },
        { 105, 112 }, { 116, 113 }, { 111, 114 }, { 110, 115 },
        { 110, 116 }, { 118, 117 }, { 115, 118 }, { 120, 119 },
        { 113, 120 }, { 119, 121 }, { 113, 122 }, { 112, 123 },
        { 118, 124 }, { 106, 125 }, { 117, 126 }, { 108, 127 },
        { 110, 128 }, { 120, 129 }, { 109, 130 }, { 117, 131 },
        { 102, 132 }, { 120, 133 }, { 120, 134 }, { 109, 135 },
        { 113, 136 }, { 104, 137 }, { 114, 138 }, { 100, 139 },
        { 118, 140 }, { 111, 141 }, { 104, 142 }, { 114, 143 },
        { 109, 144 }, { 104, 145 }, { 102, 146 }, { 108, 147 },
        { 113, 148 }, { 120, 149 }, { 119, 150 }, { 104, 151 },
        { 100, 152 }, { 116, 153 }, { 118, 154 }, { 101, 155 },
        { 113, 156 }, { 113, 157 }, { 111, 158 }, { 113, 159 },
        { 103, 160 }, { 115, 161 }, { 107, 162 }, { 110, 163 },
        { 102, 164 }, { 110, 165 }, { 119, 166 }, { 104, 167 },
        { 100, 168 }, { 118, 169 }, { 101, 170 }, { 109, 171 },
        { 102, 172 }, { 111, 173 }, { 113, 174 }, { 106, 175 },
        { 113, 176 }, { 114, 177 }, { 115, 178 }, { 109, 179 },
        { 120, 180 }, { 116, 181 }, { 107, 182 }, { 108, 183 },
        { 118, 184 }, { 108, 185 }, { 118, 186 }, { 115, 187 },
        { 102, 188 }, { 106, 189 }, { 106, 190 }, { 108, 191 },
        { 116, 192 }, { 113, 193 }, { 101, 194 }, { 107, 195 },
        { 101, 196 },
    };
    size_t s_arrlen = sizeof(s_array) / sizeof(s_array[0]);

    dump_stability_array("Before", s_array, s_arrlen);
    merge_sort(s_array, sizeof(s_array[0]), s_arrlen, cmp_stability);
    dump_stability_array("After", s_array, s_arrlen);

    return 0;
}

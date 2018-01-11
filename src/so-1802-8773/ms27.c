/* SO 1802-8773: Merge Sort */
#include <stddef.h>

extern void merge_sort(int *array, size_t arrlen);

/* Debug */
#ifdef DEBUG
static void dump_array(const char *tag, int *array, size_t len);
static void enter_func(const char *func);
static void exit_func(const char *func);
#else
#define dump_array(t, a, l) ((void)0)
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

static void merge(int *left, size_t l_len, int *right, size_t r_len, int *output)
{
    size_t r_pos = 0;
    size_t l_pos = 0;
    size_t o_pos = 0;
    enter_func(__func__);
    dump_array("Left:", left, l_len);
    dump_array("Right:", right, r_len);
    while (r_pos < r_len && l_pos < l_len)
    {
        if (right[r_pos] < left[l_pos])
            output[o_pos++] = right[r_pos++];
        else
            output[o_pos++] = left[l_pos++];
    }
    while (r_pos < r_len)
        output[o_pos++] = right[r_pos++];
    while (l_pos < l_len)
        output[o_pos++] = left[l_pos++];
    dump_array("Output:", output, r_len + l_len);
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

void merge_sort(int *array, size_t len)
{
    if (len <= 1)
        return;
    int left[(len+1)/2];
    int l_pos = 0;
    int right[(len+1)/2];
    int r_pos = 0;
    size_t mid = len / 2;

    enter_func(__func__);
    dump_array("Input:", array, len);
    for (size_t i = 0; i < mid; i++)
        left[l_pos++] = array[i];
    for (size_t i = mid; i < len; i++)
        right[r_pos++] = array[i];
    dump_array("Left:", left, l_pos);
    dump_array("Right:", right, r_pos);
    merge_sort(left, l_pos);
    merge_sort(right, r_pos);
    merge(left, l_pos, right, r_pos, array);
    dump_array("Result:", array, len);
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

/* dump_array is always used */
#undef dump_array

static void dump_array(const char *tag, int *array, size_t len)
{
    printf("%-8s", tag);
    for (size_t i = 0; i < len; i++)
        printf(" %2d", array[i]);
    putchar('\n');
}

int main(void)
{
    int array[] = { 38, 27, 43, 3, 9, 82, 10 };
    size_t arrlen = sizeof(array) / sizeof(array[0]);

    dump_array("Before:", array, arrlen);
    merge_sort(array, arrlen);
    dump_array("After:", array, arrlen);
    return 0;
}

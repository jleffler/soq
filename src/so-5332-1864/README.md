### Stack Overflow Question 5332-1864 — Deleted

[SO 5332-1864](https://stackoverflow.com/q/53321864) &mdash;
Sort array so that the numbers with the same digits are in front of
those that don't have the same digits.

The additional requirement is that the data is sorted stably; within the
list of 'all digits the same', the order is the same as in the input
array, and within the 'some different digits' list, the order is the
same as in the input array.

This is a form of stable partitioning.  However, despite some
superficially useful references from a Google search, there aren't many
references which don't simply cite the C++ `stable_partition()`
algorithm.  There must be some literature on how to do it, but I've not
found anything definitive.

* `ads13.c`

  Fixing the bugs in ads47.c.  Also trying to characterize the sort, which
  is related to bubble sort and selection sort, but not the same as either.
  This code could use the `genswap.c`/`genswap.h` code recently added to my
  private `lib/JL`.

  * [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
  * [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort)
  * [Selection sort](https://en.wikipedia.org/wiki/Selection_sort)

* `ads29.c`

  A working solution, using the generic merge sort code from [SO
  1802-8773: Merge Sort](https://github.com/jleffler/soq/tree/master/src/so-1882-8773)
  and the file `ms41.c` in particular.  That code could perhaps be
  extracted into standalone source files — a header and source file.
  NB: On macOS (BSD), the system `<stdlib.h>` declares `mergesort()`
  with the same signature.

* `ads41.c`

  A working solution, using a generic insertion sort function based on
  code from Bentley "Programming Pearls, 2nd Edn".

* `ads47.c`
  First pass, but eventually I noticed this isn't actually a stable
  sort.  The trouble is that it doesn't always compare adjacent keys.
  There are some uglinesses in the code too.

* `ads71.c`

  This is an adaptation of `ads13.c` sorting a structure which allows
  the code to demonstrate that it is a stable sort (and the `qsort()` is
  not necessarily or usually stable.  It uses the `struct Sortable`
  outlined below in the section on 'How do you demonstrate stability of
  sort?'.  I've not deduced a better way to handle it yet.

* `ads83.c`

  This code contains 3 variants of `selection_sort()`.  Since selection
  sort isn't a stable sort, this isn't a suitable choice for solving
  this problem, but I wanted the selection sort code lurking around.

### How do you demonstrate stability of sort?

First, the sorted data must be in the correct order.
This means that for every pair of entries A[N] and A[N+1], the
comparison function must report negative or zero result, never a
positive one.

Next, there are a conservation properties that are required of a sort.
For example, the same elements must be present in the sorted and
unsorted sets of data; no spurious duplicates, no accidental omissions.

In this case, there's the additional requirement that the sort is
stable.
What does that mean in detail, in this case where there is a binary
partition in progress and in the more general case of an array (probably
of a structure type, if only so that it is easier to record original
positions in the array).

A sort is stable if (and only if):

* For each pair of elements A[N] and A[N+1] where the comparison
  function reports equality, the original index of entry A[N] in
  the unsorted data must be before the original index of A[N+1].

In the presence of repeated keys (w.r.t the comparison function),
you need to determine where the values were originally.
This may not always be unambiguous with simple values such as an
array of integers.

For example, given the comparison condition for this question,
consider the array of data:

    { 12, 33, 1, 12, 19, 44, 11, 12, 76, 27, 12, 13, }

The correctly sorted data looks like:

    { 33, 1, 44, 11, 12, 12, 19, 12, 76, 27, 12, 13, }

It is easy enough in this example to establish that 33, 1, 44, and 11
have been sorted stably.
It is less clear cut that the adjacent occurrences of 12 have been
sorted stably, or that the subsequent occurrences of 12 are in the
correct relative position.
Does the stability checker have to mark values as 'used' in some way?
Clearly, if you compare 12 and 19, there are occurrences of 12 before
19, and other occurrences of 12 after 19.
If there were 3 occurrences of 12 before 19 in the sorted data, then the
sort is not stable; likewise if there was but 1 occurrence of 12 before
the 19.
Note that the sort comparator in this example is no help in judging the
similarity here; it will treat 12 and 19 as identical.

That means that we need an alternative comparator for determining
positions, at least under some conditions.
The question is — what conditions?
If dealing with a simple 'ascending order' comparator, then there's
no particular problem for an array of integers.

However, if dealing with an array of structures, then there might be
a way to spot the original unsorted order within the sorted order.

    struct Sortable
    {
        SortedData  data;
        int         posn;
    };

    /* Data from sample above, with posn indexed from 10 */
    struct Sortable array[] =
    {
        { 12, 10 }, { 33, 11 }, {  1, 12 }, { 12, 13 },
        { 19, 14 }, { 44, 15 }, { 11, 16 }, { 12, 17 },
        { 76, 18 }, { 27, 19 }, { 12, 20 }, { 13, 21 },
    };

The correct stable sorted order is:

        { 33, 11 }, {  1, 12 }, { 44, 15 }, { 11, 16 },
        { 12, 10 }, { 12, 13 }, { 19, 14 }, { 12, 17 },
        { 76, 18 }, { 27, 19 }, { 12, 20 }, { 13, 21 },

With the posn element, it is feasible to ensure that the sort is
stable — where the main sort comparator indicates equality, the
posn values must be such that A[N].posn < A[N+1].posn.  (There are
no duplicates allowed in the unsorted posn values, and they must
be in monotonically increasing order in the unsorted data.)

Can stability be shown by demonstrating that there are the same
number of equal items before and after the one being inspected?

* How do you distinguish the one being inspected?
* No; that's probably a blind alley.

Can you automate the wrapping of the data in a 'struct Sortable'?
Probably not — alignment is a problem.

With a generic sort, you might be able to get close, though.

    int cmp_sorted(const void *v1, const void *v2);
    int cmp_stable(const void *v1, const void *v2);

    int cmp_stable(const void *v1, const void *v2)
    {
        const struct Sortable *p1 = v1;
        const struct Sortable *p2 = v2;

        int rc = cmp_sorted(&p1->data, &p2->data);
        if (rc == 0)
        {
            if (p1->posn < p2->posn)
                rc = -1;
            else if (p1->posn > p2->posn)
                rc = +1;
        }
        return rc;
    }

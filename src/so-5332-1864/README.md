### Stack Overflow Question 5332-1864

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

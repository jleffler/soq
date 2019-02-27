### Stack Overflow Question 1802-8773

[SO 1802-8773](https://stackoverflow.com/q/18028773) &mdash;
Merging in merge sort algorithm

* `ms27.c`

  Debuggable merge sort for an array of integers.

  This was provided as the answer to the original question, though it is
  not entirely clear what was being asked, The link in the question is
  actually a copy of the material on merge sort from Wikipedia.

* `ms41.c`

  Generic merge sort analogous to standard C `qsort()`.

  This code is simpler, in many ways, than the specific sort.  It
  exploits `memmove()` to do array copying, instead of explicit loops.

  There are three tests, for a small array of integers (the same array
  as in `ms27.c`), then a bigger array of doubles, and finally a
  slightly bigger array of a structure type that is used to demonstrate
  that the sort is stable.

  Each entry in the stability structure has a random key between 100 and
  120, plus a sequential index number in the range 100..196 (there are
  97 elements in the array).  The keys have many repeats, but the output
  shows that the indexes are in ascending order within a key.  I suppose
  this isn't 100% convincing, come to think of it; this is what you'd
  get if the data was sorted by key and then index.  Oh well, you have
  to examine the code to see that isn't what's happening.  Fixing it so
  the demonstration is 'foolproof' is harder.  Maybe a triple with key,
  value and index where the value is also a random integer, but the
  indexes are still sequential; that makes for easier validation, but is
  still not completely convincing.  Otherwise, make the index a random
  number, and then the validation becomes non-trivial.  It suffices as
  it is!

  The code generation for the array of doubles and array of structures
  is a satisfying demonstration of the general utility of the random and
  commalist programs, and the power of paste, process substitution and
  sed.

  Note: because this algorithm uses arrays on the stack (VLAs), it is
  only suitable for smallish arrays — it requires approximately the
  same space as in the main array for the sub-arrays.

  It would not be hard to devise a version that allocates each of the
  sub-arrays with `malloc()` et al.  Maybe this variant should be called
  `merge_sort_vla()` and the alternative should be `merge_sort_mem()`.
  Maybe a cover function `merge_sort()` should choose between the
  `merge_sort_vla()` and `merge_sort_mem()` variants based on the value
  of `size * number`; if it is 1 MiB or less, use the VLA variant;
  otherwise use the allocating variant.  The threshold could be
  adjustable — and smaller when used on Windows (128 KiB?).

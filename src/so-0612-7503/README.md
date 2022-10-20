### Stack Overflow Question 0612-7503

[SO 0612-7503](https://stackoverflow.com/q/06127503) &mdash;
Shuffle array in C

Note the discussions at:

* [Fisher-Yates Shuffle](http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
  on Wikipedia.
* [Ben Pfaff's implementation](http://benpfaff.org/writings/clc/shuffle.html)
  on his web site.
* [The Danger of Naivete](http://www.codinghorror.com/blog/2007/12/the-danger-of-naivete.html)
  on the Coding Horror blog site.
* [Why does this simple shuffle algorithm produce biassed results?](https://stackoverflow.com/questions/859253)
  on SO.
* [Is this C implementation of Fisher-Yates shuffle correct?](https://stackoverflow.com/questions/3343797/)
  on SO, especially the answer by Roland Ilig.

No doubt there are many other relevant sources.
For general purpose code, you probably need to use a custom random
number generator rather than co-opting the sequence from `rand()`.
For example, `nrand48()` allows each user (e.g. the shuffle code) to
have an independent sequence of random numbers without interference by
or to other code using random number generation.
This is critical for high quality library functions.
The choice of which such random number generator is up to the user.
Consider the merits of `/dev/urandom` too — remembering that
repeatability is not one of the merits.
And on BSD-derived systems, `arc4random()` may be a good choice.

### Bar Gelfer algorithm

One new [answer](https://stackoverflow.com/a/74122335/15168) by
[Bar Gelfer](https://stackoverflow.com/users/20280604/bar-gelfer)
postulates a shuffle that is encapsulated in the code:

* `check-conservation.c`
* `check-conservation.h`

These are prototypes for what will probably end up in my private library,
and maybe in `libsoq` too.

There are multiple potentially useful functions in here.  Note that they are
fairly expensive, using an O(N^2) algorithm and O(N) storage.

* `check_conservation()`

  Compare two arrays for equivalence.  It spots whether there are differences
  between the data.

* `print_sorted_copy_of_array()`

  Generate a copy of an array, and print both the original and the sorted copy.
  The copy is stored in space provided by the calling code.

* `print_array_differences()`

  Print the differences between two versions of an array.  The code sorts the
  arrays (`print_sorted_copy_of_array()`) and then steps through the arrays
  identifying where the entries differ.  It it believed to work sanely for any
  two arrays, but it [pii

The code should be genericized, but the biggest problem is genericizing the
printing.  That'll probably need to be done by a function pointer passed to
the code.  And it's likely that the code should format into a string.  The
memory management for that remains to be decided - but POSIX `getline()` might
be an exemplar.

The test code shows that the Bar Gelfer algorithm does not conserve the input
data.  Consequently, it is not an acceptable shuffle algorithm.  It also uses
the Fisher-Yates code (`fyshuffle.c`, `fyshuffle.h` - not yet available in
`libsoq`) along with random seeding code (`randseed.c`, `randseed.h` - also not
yet available in `libsoq`) to show that that shuffle does conserve the data.


### Stack Overflow Question 4351-0251

[SO 4351-0251](http://stackoverflow.com/q/43510251) &mdash;
Pivot set in quicksort

> Why doesn't a different pivot, besides high, work for this code?
Is there a code for quicksort that can handle high/low/random pivots or
does it have to be a separate algorithm ?
I think that this is using [Lomuto's partitioning
scheme](https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme).

Some code added:

* `qs83.c`: code related to SO 4405-8637 [Inconsistent output of quick
   sort](https://stackoverflow.com/questions/44058637/inconsistent-output-of-quick-sort)

* `iq89.c`: modified version of the code in the question.  Some is
   standard cleanup (static functions, etc); some is extending the test
   process.


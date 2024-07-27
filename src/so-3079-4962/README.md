### Stack Overflow Question 3079-4962

[SO 3079-4962](https://stackoverflow.com/q/30794962) &mdash;
How to return positive occurrence

Also code related to:
* [SO 3514-7784](https://stackoverflow.com/q/35147784) &mdash; first and last occurrence for binary search.
* [SO 3707-5084](https://stackoverflow.com/q/37075084) &mdash; fuzzy matching on strings (deleted).
* [SO 4088-0230](https://stackoverflow.com/q/40880230) &mdash; Lookup Table in C with Ranges
* [SO 4477-2009](https://stackoverflow.com/q/44772009) &mdash; CS50: PSET 3: Binary Search inconsistent success with test data
* [SO 4584-8084](https://stackoverflow.com/q/45848084) &mdash; Determine if a range is contained within a set of ranges
* [SO 5305-8133](https://stackoverflow.com/q/53058133) &mdash; A query regarding the algorithm of binary search using C
* [SO 5313-7765](https://stackoverflow.com/q/53137765) &mdash; Binary Search is giving me a segfault
* [SO 7880-0047](https://stackoverflow.com/q/78800047) &mdash; Weird timings when measuring the perfomance of binary search

Programs:

* `binsearch-speed`
  Compare different binary search algorithms for speed.
* `bs-files`
  SO 3707-5084: 
* `bscheck`
  Check basic binary search algorithm for accuracy.
  Includes bsearch.c, which is nominally a symlink link to `bsearch-4477-2009.c`
* `bsmax`
  Find highest index for value in the array if there are duplicates.
* `bsmin`
  Finds lowest index for value in the array if there are duplicates.
* `bsprobes`
  SO 7880-0047: Counts the probes required to produce a result.
  The question finds 'best', 'worst' and 'average' case search times,
  but the question has a very naive interpretation of what is best,
  worst, and average.  The question was justifiably closed as missing
  information; requiring access to a GitHub repo to see what the OP is
  really doing.
* `bsrange-chux-00`
  SO 4584-8084: an answer by [chux](https://stackoverflow.com/users/2410359/chux)
* `bsrange-chux-01`
  JLSS adaptation of `bsrange-chux-00.c` with more thorough testing.
* `bsrange`
  SO 4584-8084: determine whether a given range is covered by the ranges in the data array.
* `modbinsearch`
  SO 3514-7784: if there are repeats of the value to found in the array, report first and last indexes
* `rangebinsearch`
  SO 4088-0230: more variant search algorithms, most of which are found in other code here too.
* `shiftbinsearch`
  Binary search using 'shifts' to find range where answer lies (or doesn't lie).


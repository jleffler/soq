### Stack Overflow Question 4568-6957

[SO 4568-6957](https://stackoverflow.com/q/45686957) &mdash;
What is logic to construct a binary tree?

Three C++ programs that do the job, more or less.

The programs can all be run using:

    range 1 $n | btNN

(or use `seq` in place of `range`).

* `bt67` - first pass, vector of nodes
* `bt89` - second pass, vector of node pointers
* `bt83` - third pass, vector of nodes, better presentation of results

The accepted answer code is `bt83.cpp`.

### Stack Overflow Question 5059-5146

[SO 5059-5146](https://stackoverflow.com/q/50595146) &mdash;
Delete element from a dynamic array C

The objective is to end up with an array of just the unique values.

There are multiple ways to do this.
The simplest, and the one implemented so far, is when there's no
ownership issues with the data in the array.
Values that are not needed can be ignored.

Things get more complicated with, for example, an array of strings.
Then you need to ensure that the unwanted elements are not lost, so that
they can be freed somehow.

There's outline code for doing that in uniq31.c, but it is far from
complete (it is pseudo-code in a comment) or guaranteed to be correct.
Nevertheless, the idea that an array which may hold duplicates is a
sequence of units, each of which contains an optional subsequence of at
least 2 identical values, followed by a subsequence of 0 or more
distinct values (distinct from the identical values, and distinct from
each other, and the last element is not duplicated in the following
subsequence).

For example:

* 10 10 10 11 12 13 14 14 14 15 15 15 16 16 16 17 18 19

consists of 4 units in sequence (where each subsequence happens to
contain 3 items, but need not):

* { {10 10 10} {11 12 13} }
* { {14 14 14} }
* { {15 15 15} }
* { {16 16 16} {17 18 19} }

Obviously, an example like this is perfectly permissible too:

* 10 10 11 12 12 13 14 15 16 17

yields:

* { {10 10} {11} }
* { {12 12} {13 14 15 16 17} }

and:

* 10 11 12 12 13 14 15 16 17

yields:

* { {} {10 11} }
* { {12 12} {13 14 15 16 17} }

There is never a reason to have an empty repeat sequence except for the
very first unit in the data.
There can be a reason to have an empty distinct sequence at any point in
the data.
Empty sets and singleton sets are unexciting.

Is it better to consider the data as coming in interleaved sequences of
either 2 or repeated values or sequences of 0 or more distinct values?

### `chk.uniq31`

Runs a sequence of tests of `uniq31`.
These include fixed sequences of 0 to 3 values in all legitimate
combinations of distinct or same values.

It also uses `random` to generate sequences of random numbers and
includes code to ensure the correctness of the unique-ness coding.


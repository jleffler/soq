### Stack Overflow Question 5201-4002

[SO 5201-4002](https://stackoverflow.com/q/52014002) &mdash;
C - Reading limited length words in unlimited length lines

As explained in the answer, this answers a slightly different problem
from the question, mainly because it doesn't trust the input.

A previous version of `scan59.c` mostly worked on trustworthy data,
except that it didn't handle a word split across fragment boundaries
correctly.

The tests, especially `test-data.3`, are fairly stringent.

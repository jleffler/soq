### SO 7365814 - Permuting elements of an array

Python code provided by QWERTY (http://stackoverflow.com/users/937390/qwerty).

C code provided by AnT (http://stackoverflow.com/users/187690/ant), but
tarted up into a test case.

### Question

Let's say I have an array `a` of length `n` and a second array
`indices`, also of length `n`. `indices` contains some arbitrary
permutation of the sequence `[0, n)`.  I want to to rearrange `a` such
that it's in the order specified by `indices`.  For example, using D
syntax:

    auto a = [8, 6, 7, 5, 3, 0, 9];
    auto indices = [3, 6, 2, 4, 0, 1, 5];
    reindexInPlace(a, indices);
    assert(a == [5, 9, 7, 3, 8, 6, 0]);

Can this be done in both O(1) space and O(n) time, preferably without
mutating `indices`?

### Stack Overflow Question 4489-4213

[SO 4489-4213](https://stackoverflow.com/q/44894213) &mdash;
What is Best way for Replace with More Performance Using C?

The test program in the question has 8 'replace' algorithms in a random
order, and some barely minimal test code.
Two of the functions (`replace4()` and `replace6()`) originally returned
a pointer to static data; they were upgraded to allocate the same amount
of space.
At least one of the functions does not always return a pointer to newly
allocated space; it sometimes returns the original string.
That is a nightmare — do you, or do you not, free what it returns.

The `replace3()` code doesn't seem to work, even with some minor tweaks.
It also frees the original string without justification.
It is commented out and probably not worth preserving.

I did some benchmarking.
The benchmarking needs improvement.
Using random numbers is good.
Not doing exactly the same test with each algorithm is sub-optimal,
though the differences don't really affect the performance.

One of the two 'originally static' algorithms is much faster than the
others.
However, IIRC, it doesn't heed buffer overflows at all.

Sample output (time in seconds, of course):

    replace1       0.501161
    replace2       0.506037
    replace4       0.302938
    replace5       0.483471
    replace6       0.044771
    replace7       0.488791
    replace8       0.886122

Note that `replace6()` is by far the fastest.

The sources of the algorithms are not properly identified or attributed.
See also SO 0440-8170 for more information (in the SOQ repo, and on SO
itself).

There is barely any change in the code provided, apart from 'not using
static variables'.


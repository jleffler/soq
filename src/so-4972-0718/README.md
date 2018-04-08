### Stack Overflow Question 4972-0718

[SO 4972-0718](https://stackoverflow.com/q/49720718) &mdash;
How to control mutex lock and unlock?

Various solutions were mooted and more or less acceptable solutions were
proposed.
ONe solution I proposed in comments turned out to have a typo in it (two
`pthread_mutex_lock()` calls on the same mutex, rather than one
`pthread_mutex_lock()` and one `pthread_mutex_unlock()`.
This code was assembled to create an answer covering and demonstrating
the various points.

The shell script is trivial — it simply runs the program `pth71` with
the argument `-0` five times, then with `-1`, ..., `-4`, to test each
algorithm five times.

The results recorded in my answer are quite interesting:

    Variant 0: time : 0.006511s  result : 1003   [ 251, 251, 251, 250 ]
    Variant 0: time : 0.007028s  result : 1003   [ 251, 251, 251, 250 ]
    Variant 0: time : 0.006156s  result : 1003   [ 333, 224, 223, 223 ]
    Variant 0: time : 0.006656s  result : 1003   [ 251, 251, 250, 251 ]
    Variant 0: time : 0.006931s  result : 1003   [ 252, 250, 250, 251 ]
    Variant 1: time : 0.000462s  result : 1000   [ 0, 0, 1000, 0 ]
    Variant 1: time : 0.000345s  result : 1000   [ 1000, 0, 0, 0 ]
    Variant 1: time : 0.000345s  result : 1000   [ 1000, 0, 0, 0 ]
    Variant 1: time : 0.000388s  result : 1000   [ 1000, 0, 0, 0 ]
    Variant 1: time : 0.000340s  result : 1000   [ 1000, 0, 0, 0 ]
    Variant 2: time : 0.006203s  result : 1000   [ 251, 250, 249, 250 ]
    Variant 2: time : 0.006779s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 2: time : 0.006841s  result : 1000   [ 251, 250, 250, 249 ]
    Variant 2: time : 0.005960s  result : 1000   [ 251, 250, 250, 249 ]
    Variant 2: time : 0.006416s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 3: time : 0.012238s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 3: time : 0.012763s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 3: time : 0.013417s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 3: time : 0.012676s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 3: time : 0.012899s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 4: time : 0.005999s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 4: time : 0.006461s  result : 1000   [ 251, 250, 250, 249 ]
    Variant 4: time : 0.006112s  result : 1000   [ 250, 250, 250, 250 ]
    Variant 4: time : 0.005910s  result : 1000   [ 251, 249, 250, 250 ]
    Variant 4: time : 0.006832s  result : 1000   [ 250, 250, 250, 250 ]

It was gratifying to see the first variant 1 result.
The variant 0 ones are intriguing, especially the third result.


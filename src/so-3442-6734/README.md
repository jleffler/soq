### Stack Overflow Question 3442-6734

[SO 3442-6734](https://stackoverflow.com/q/34426734) &mdash; (deleted)
Given array A consisting of N integers, return the size of the largest set S[K] for the array

This question was deleted a long time ago.

The question was:

> A zero indexed array A consisting of N different integers is given.  The
> array contains all integers in the range [0.. N-1].
> Sets S[K] for 0 <= K < N are defined as follows:
> 
> S[K] = {A[k], A[A[k]], A[A[A[k]]], …}
> 
> The sets S[K] are finite for each k.
> 
> The task is to write a function that, when given an array A consisting
> of N integers, returns the size of the largest set S[K] for this array.
> The function should return 0 if input is empty;
> 
>     A[0] = 5
>     A[1] = 4
>     A[2] = 0
>     A[3] = 3
>     A[4] = 1
>     A[5] = 6
>     A[6] = 2
> 
> For this data, the function should return 4 because set S[2] equals
> {0,5,6,2} and has four elements.  No other set S[K] has more than four
> elements.  Assume elements in A are all distinct.  Each element of array
> A is an integer with in the range [0.. N-1].
> 
> Can anyone help me with how to start with this problem?

Given that the OP didn't try any code, my response was not a coded solution:

> What may be throwing you off is how to identify the elements of S[K].
>
> The key point is that the set { A[K], A[A[K]], A[A[A[K]]], … } can
> be created iteratively, starting at any index K (so you'll end up with
> a loop index K running over the range 0..N-1).  Another way of writing
> the set might be:
>
>     S[K] = { S0 = A[K], S1 = A[S0], S2 = A[S1], … }
>
> and the set is complete when A[Smax] = K.  You might also observe that
> when the cycle is of length L such that 2L >= N, there won't be a
> longer cycle, which can terminate the loop early.  You can count the
> members added to the set as they're added, and keep a record of the
> longest set as you go.
>
> This is at least a very straight-forward algorithm with complexity
> O(N2) — it uses N iterations of the set, and each iteration scans up
> to N elements from the set.

The code in `set-sk.c` features command-line argument processing and
random shuffling of arrays to generate examples, and so on.

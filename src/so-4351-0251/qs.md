As far as I can tell, the code in the question is a working quicksort
algorithm.
It uses the highest element in a range as the pivot for that range.

To the extent that there are questions, they are:

* What has to change if I want to pivot around the lowest element in the range?
* What has to change if I want to pivot around a random element in the range?

I previously
[commented](https://stackoverflow.com/questions/43510251/pivot-set-in-quicksort?noredirect=1#comment74074879_43510251):

> From what I've seen, you can write a quick sort that uses either the
> first or the last index as the pivot.
> To get a random pivot, the code usually seems to choose an entry at
> random and swap it with either the first or last index, and that
> becomes the pivot.
> You might look at [Quicksort: Choosing the
> pivot](http://stackoverflow.com/questions/164163/quicksort-choosing-the-pivot)
> for more information on pivot selection algorithms.

The standard version of Lomuto's partitioning algorithm chooses the last
element in the range as the pivot, as in the code in the question.

The standard version of Hoare's partitioning algorithm chooses the first
element in the range as the pivot.

It is perfectly feasible, though not 100% straight-forward, to produce a
variant of Lomuto's algorithm that works with the first element in the
range as the pivot, and also to produce a variant of Hoare's algorithm
that works with the last element in the range as the pivot.

Then, for a random pivot point, you simply choose an element in the
range at random and swap it with the chosen pivot location (low or
high).


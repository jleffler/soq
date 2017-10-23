### Stack Overflow Question 4673-6148

[SO 4673-6148](https://stackoverflow.com/q/46736148) &mdash;
Computing a sequence?

### Question

I have got a sequence in which first four numbers are given
(specifically they are 1, 9, 8, 9 and the fifth one is solved as `a5 =
(a1 + a2 + a3 + a4) % 10`.
Then the numbers move to the right and process of solving fifth number
is the same (meaning they are 9, 8, 9, 7 now).
The task is to find out whether there will be a sequence of 1, 9, 8, 9
again and if so, after how many iterations.

### `so-4673-6148A.c`

This code provides a direct answer to the question, listing the steps.
It takes 1560 steps to complete the cycle starting from 1989.

### `so-4673-6148B.c`

This code produces the answer of how many steps are in the cycles from
each 4-digit starting number, including leading zeroes.

The output has to be analyzed.  For example:

	$ so-4673-6148B | sed 's/.* \([0-9]\{1,4\}\))$/\1/' | sort | uniq -c  | sort  -n 
	   1 1
	  15 5
	 624 312
	9360 1560
	$

This tells us that there is one cycle with one element, 3 cycles with 5
elements in each, 2 cycles with 312 elements in each, an 6 cycles with
1560 elements in each.

### `so-4673-6148C.c`

This code determines the lowest number in each sequence for each of the
numbers 0..9999.
This allows us to find ohe element in each sequence, from which a simple
adaptation of the first program would allow us to print the
corresponding sequence.


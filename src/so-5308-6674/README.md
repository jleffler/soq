### Stack Overflow Question 5308-6674 (deleted)

[SO 5308-6674](https://stackoverflow.com/q/53086674) &mdash;
A rhombus filled with prime numbers

This question was deleted by the OP so it isn't necessarily visible.

See also:

* [SO 5333-9734](https://stackoverflow.com/q/53339734) "Finding the
   first prime number after the entered number"
* [SO 5332-0995](https://stackoverflow.com/q/53320995) "Finding closest
   prime number".

There are a couple of parts to the rhombus problem.

1. Establish a list of prime numbers, or a way to get the next prime number.
2. Print a rhombus.
3. Combine the two.

### `npa67.c`

This program contains a function to establish the 'next prime after' a
given value.
It uses the 6N±1 technique to look for prime numbers, bootstrapping off
a list of prime numbers up to 1013 to speed up many prime number
determinations.

### `npt23.c`

This program contains a function to find the nearest prime number before
or after the given value.

### `rhom59.c`

This code prints a rhombus with entries marked by three asterisks.
It takes command line arguments, and prints values (copious debug
information).

### `prim29.c`

This code combines `npa67.c` and `rhom59.c` to produce an unsubmitted
answer to the code problem.
It adapts the number of digits printed to the size of rhombus, but the
size boundaries are established empirically rather than calculated.

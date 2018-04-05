### Stack Overflow Question 4929-0953

[SO 4929-0953](https://stackoverflow.com/q/49290953) &mdash;
How do I make conditions in printf statements?

Asked by [Katie.P](https://stackoverflow.com/users/9494911/katie-p).

This is a weird question with an equally weird answer.
The conditions claimed by the OP are ridiculous.
The inflexibility of the OP lead to somewhat curt responses from me;
they don't seem to be able to extract code from a function for use in a
single-function `main()` program.
However, the question requirements are nuisancy enough that it becomes
almost interesting.

# Question

I have homework where I have to create a C program which sorts 5 numbers
from smallest to largest.
I know how to easily program this using functions and `if` statements
(using `>=` and `<=`).

However, the catch is I am only allowed to use `printf` and `scanf`, so
I have to calculate all the `>=` and `<=` inside the `printf`.
And I'm not allowed to use the ternary operator.

I've been trying to a long time.
So I tried to sort just 3 numbers, I still can't even get past sorting
the smallest number.
It just keeps printing `1`.

    // This printf is just trying to figure out the smallest number from
    // 3 numbers provided but it keeps printing 1.
    printf("The ascending order of the numbers are: %d ",
        (
         (num1 <= num2 && num1 <= num3) || // Checking if num1 is the smallest
         (num2 <= num1 && num2 <= num3) || // Checking if num2 is the smallest
         (num3 <= num2 && num3 <= num1)    // Checking if num3 is the smallest
        ));

One possible solution I have come up with is adding the `((num1 + num2 +
num3) -1)` because if one of the statements is true (for example if
`num2` is the smallest, it would print `1` because `1` means true).
If it is false it prints `0`.
So I could technically add the statement which is true then `-1`.
So if `num2`'s statement is true, I could do `+ num2 - 1`.

# Answer

### Pass 1: Minimum of three distinct values

Note that if a condition evaluates to false, the result is `0`; if true,
`1`.
So you can use a trick (as long as multiplication and addition aren't
verboten too) — for three distinct values as shown in the question:

    printf("The smallest number is: %d ",
           (num1 * (num1 <= num2 && num1 <= num3) +
            num2 * (num2 <= num1 && num2 <= num3) +
            num3 * (num3 <= num1 && num3 <= num2)));

There will be trouble if two values are the same and are also the smaller value.

* Code from `sort3-17.c` is applicable but not present in the answer.

### Pass 2: Minimum of five distinct values

If you need to process 5 values, it is (as noted in a comment) more tedious than difficult.

    printf("The smallest number is: %d ",
           (num1 * (num1 <= num2 && num1 <= num3 && num1 <= num4 && num1 <= num5) +
            num2 * (num2 <= num1 && num2 <= num3 && num2 <= num4 && num2 <= num5) +
            num3 * (num3 <= num1 && num3 <= num2 && num3 <= num4 && num3 <= num5) +
            num4 * (num4 <= num1 && num4 <= num2 && num4 <= num3 && num4 <= num5) +
            num5 * (num5 <= num1 && num5 <= num2 && num5 <= num3 && num5 <= num4)));

This is just for finding the minimum; working it for each of the other
cases quickly becomes preposterous.
Indeed, the whole exercise is fairly silly, but it is also fairly
typical of some courses.

### Pass 3: Minimum of three values not necessarily distinct

After a bit of cogitation, I think you can deal with 2 or 3 numbers the
same with this (which is basically what
[user3386109](https://stackoverflow.com/users/3386109/user3386109) said
in a
[comment](https://stackoverflow.com/questions/49290953/how-do-i-make-conditions-in-printf-statements/49291191#comment85585542_49290953)).

* Code from `sort3-29.c`

Output:

    The smallest number of (1, 1, 1) is 1
    The smallest number of (1, 1, 2) is 1
    The smallest number of (1, 1, 3) is 1
    The smallest number of (1, 2, 1) is 1
    The smallest number of (1, 2, 2) is 1
    The smallest number of (1, 2, 3) is 1
    The smallest number of (1, 3, 1) is 1
    The smallest number of (1, 3, 2) is 1
    The smallest number of (1, 3, 3) is 1
    The smallest number of (2, 1, 1) is 1
    The smallest number of (2, 1, 2) is 1
    The smallest number of (2, 1, 3) is 1
    The smallest number of (2, 2, 1) is 1
    The smallest number of (2, 2, 2) is 2
    The smallest number of (2, 2, 3) is 2
    The smallest number of (2, 3, 1) is 1
    The smallest number of (2, 3, 2) is 2
    The smallest number of (2, 3, 3) is 2
    The smallest number of (3, 1, 1) is 1
    The smallest number of (3, 1, 2) is 1
    The smallest number of (3, 1, 3) is 1
    The smallest number of (3, 2, 1) is 1
    The smallest number of (3, 2, 2) is 2
    The smallest number of (3, 2, 3) is 2
    The smallest number of (3, 3, 1) is 1
    The smallest number of (3, 3, 2) is 2
    The smallest number of (3, 3, 3) is 3

### Pass 4: Sorted order for three values not necessarily distinct

Calculating the maximum instead of the minimum is trivial; simply use
`>` in place of `<` throughout.
Calculating the median turns out to be harder.
I suspect there is a better way of doing it than this, but at least this
works.
Note the subtracted term — omit that, and the median value is doubled
when the three values are the same.

* Code from `sort3-79.c`

Output:

    The sorted order of (-7, -7, -7) is (-7, -7, -7)
    The sorted order of (-7, -7, -1) is (-7, -7, -1)
    The sorted order of (-7, -7,  5) is (-7, -7,  5)
    The sorted order of (-7, -1, -7) is (-7, -7, -1)
    The sorted order of (-7, -1, -1) is (-7, -1, -1)
    The sorted order of (-7, -1,  5) is (-7, -1,  5)
    The sorted order of (-7,  5, -7) is (-7, -7,  5)
    The sorted order of (-7,  5, -1) is (-7, -1,  5)
    The sorted order of (-7,  5,  5) is (-7,  5,  5)
    The sorted order of (-1, -7, -7) is (-7, -7, -1)
    The sorted order of (-1, -7, -1) is (-7, -1, -1)
    The sorted order of (-1, -7,  5) is (-7, -1,  5)
    The sorted order of (-1, -1, -7) is (-7, -1, -1)
    The sorted order of (-1, -1, -1) is (-1, -1, -1)
    The sorted order of (-1, -1,  5) is (-1, -1,  5)
    The sorted order of (-1,  5, -7) is (-7, -1,  5)
    The sorted order of (-1,  5, -1) is (-1, -1,  5)
    The sorted order of (-1,  5,  5) is (-1,  5,  5)
    The sorted order of ( 5, -7, -7) is (-7, -7,  5)
    The sorted order of ( 5, -7, -1) is (-7, -1,  5)
    The sorted order of ( 5, -7,  5) is (-7,  5,  5)
    The sorted order of ( 5, -1, -7) is (-7, -1,  5)
    The sorted order of ( 5, -1, -1) is (-1, -1,  5)
    The sorted order of ( 5, -1,  5) is (-1,  5,  5)
    The sorted order of ( 5,  5, -7) is (-7,  5,  5)
    The sorted order of ( 5,  5, -1) is (-1,  5,  5)
    The sorted order of ( 5,  5,  5) is ( 5,  5,  5)

### Pass 5: Sorted order for three values, no loops or function

As before, the code in Pass 4 does a thorough test of all combinations
of three numbers in their relative positions.
If you're required to read three numbers and then sort them (and you're
not allowed to use loops or functions other than `main()`, `scanf()`,
`printf()`, so be it — you can transplant the `printf()` statement
into your `main()` immediately after you've read three values:

* Code from `sort3-53.c`

Testing with a random number generator (program name `sort3-53`) yields:

    $ for i in $(range 0 9); do random -n 3 10 99 | sort3-53; done
    The sorted order of (66, 62, 70) is (62, 66, 70)
    The sorted order of (43, 99, 23) is (23, 43, 99)
    The sorted order of (20, 46, 66) is (20, 46, 66)
    The sorted order of (87, 82, 19) is (19, 82, 87)
    The sorted order of (63, 29, 62) is (29, 62, 63)
    The sorted order of (40, 66, 15) is (15, 40, 66)
    The sorted order of (17, 13, 58) is (13, 17, 58)
    The sorted order of (84, 50, 11) is (11, 50, 84)
    The sorted order of (60, 86, 54) is (54, 60, 86)
    The sorted order of (37, 33, 96) is (33, 37, 96)
    $

You can probably use `seq` where I use `range`.
I'm not sure there's a standard PRNG program analogous to the `random` I
use (and wrote).
The invocation shown generates 3 random numbers between 10 and 99
inclusive.

### How it should be done?

The whole process here is preposterous — but that's because of the
conditions placed on the techniques that can be used.
If you need to sort three or more numbers, put them in an array, sort
the array, and print the array.
Failing that, you should swap the values to find the sorted order; it
would dramatically reduce the number of comparisons needed, and there'd
be no multiplications.

* Code from `sortnet3-89.c` is applicable but not shown in the answer.
  It shows 6 different ways of sorting 3 values with 3 comparisons and
  up to 3 swaps.

### Apposite comments

I agree with the sentiments of both these comments.
The exercise as described in the question (and comments) is preposterous.

By [yano](https://stackoverflow.com/users/3476780/yano) in a
[pair](https://stackoverflow.com/questions/49290953/how-do-i-make-conditions-in-printf-statements#comment85586861_49290953)
of
[comments](https://stackoverflow.com/questions/49290953/how-do-i-make-conditions-in-printf-statements#comment85586961_49290953):

* _The value in this assignment is academic only, I suppose, by making
  you "think outside the box" (I wouldn't come up with a solution to
  this in any reasonable amount of time).
  Practically, this is a dumb, stupid, useless assignment at best, and
  possibly detrimental.
  Presumably this is CompSci 101 or something equivalent; how many
  students interested in coding is a task like this going to scare off?
  Are the students left going to think it's normal to do this much work
  in `printf`?
  After this assignment, never write code like this again.
  These asinine requirements (not allowed to use this,_
* _this, or this), are only useful IMO when you're implementing your own
  version of a function call to see how it works.
  Writing your own `strcat` or `pow` functions, for instance, have value.
  Writing a bubble sort function has value.
  Even if you figure out a sorting algorithm that has merit, stuffing it
  all into a printf as some kind of extended expression is confusing,
  hard to read, and hard for others after you to maintain.
  You should mention this on the class eval.
  /rant_

By [Steve Summit](https://stackoverflow.com/users/3923896/steve-summit)
in a
[comment](https://stackoverflow.com/questions/49290953/how-do-i-make-conditions-in-printf-statements#comment85686623_49291191):

* What I'm still puzzling over is: _What in the world was the expected
  answer??_ Jonathan Leffler is one of the most experienced C
  programmers on SO, and he could only barely begin to solve this
  problem.
  There's no way a student in an ordinary C programming class could
  have.
  So either something got lost in translation, or the instructor who set
  this assignment is a truly malicious sadist.


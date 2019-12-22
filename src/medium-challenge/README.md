From Medium - Better Programming

[Do you know how to solve these programming problems?](https://medium.com/better-programming/do-you-know-how-to-solve-these-programming-problems-18d04defc05e)

### Challenge 1: Plus Minus (from [HackerRank](https://www.hackerrank.com/))

> Given an array of integers, calculate the fractions of its elements
> that are positive, negative and are zeros.  Print the decimal value of
> each fraction on a new line.

> Note: This challenge introduces precision problems.  The test cases
> are scaled to six decimal places, though answers with aboslute error
> of up to 1E-4 are acceptable.

> For example, given the array arr = [1, 1, 0, -1, -1] there are 5
> elements, two positive, two negative and one zero.  Ther ratios would
> be 2/5 = 0.500000, 2/5 = 0.400000, and 1/5 = 0.200000.  It should be
> printed as:

>     0.400000
>     0.400000
>     0.200000

I observe that the provided PHP solution doesn't produce 6 fractional digits - it might not pass muster.

Solution 1: `pmf23.c`

There isn't much to say about it.  In C, the required code is basically trivial.

### Challenge 2: Two sum (from [LeetCode](https://leetcode.com/problems/two-sum/))

> Given an array of integers, return **indices** of the two numbers such
> that they add up to a specific target.

> You may assume that each input would have **exactly** one solution,
> and you may not use the same element twice.

> Example: Given nums = [2, 7, 11, 15], target = 9

> Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].

Solution 2: not attempted - insufficient interest in a brute force solution.

### Challenge 3: Largest palindrome product (from [Project Euler](https://projecteuler.net/problem=4)

> A palindromic number reads the same both ways.  The largest palindrome
> made from the product of two 2-digit numbers is 9009 = 911 * 99.

> Find the largest palindrom made from the product or two 3-digit numbers.

Solution 3: `lpp13.c`

The tricky bit is working out how to avoid doing 900 x 900 = 810,000
tests.

The code counts down from 999 for each of the two factors.

I opted for a heuristic - I guessed that the biggest palindromic number
would be 500 x 500 = 250,000 or bigger.  The solution on the site has a
better heuristic; if the product of the two numbers is smaller than the
biggest palindrome so far, stop processing.

### Challenge 4: Distinct powers (from [Project Euler](https://projecteuler.net/problem=29))

> Consider all the integer combinations of a<sup>b</sup> for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

> * 2<sup>2</sup> = 4, 2<sup>3</sup> = 8, 2<sup>4</sup> = 16, 2<sup>5</sup> = 32.
> * 3<sup>2</sup> = 9, 3<sup>3</sup> = 27, 3<sup>4</sup> = 81, 3<sup>5</sup> = 243.
> * 4<sup>2</sup> = 16, 4<sup>3</sup> = 64, 4<sup>4</sup> = 256, 4<sup>5</sup> = 1024.
> * 5<sup>2</sup> = 25, 5<sup>3</sup> = 125, 5<sup>4</sup> = 625, 5<sup>5</sup> = 3125.

> If they are then placed in numerical order, with any repeats removed,
> we get the following sequence of 15 distinct terms:

>     4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 11024, 3125

> How many distinct terms are in the seuqence generqated by a<sup>b</sup> for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?

Solution 4: `dp97.c`

The PHP solution simply calculates the 99 x 99 = 9801 numbers in an
array, and the eliminates duplicates and counts what's left.

Coding like that in C directly isn't a sensible option; it requires some
sort of multi-precision arithmetic package.  The chosen solution is to
represent each number in terms of its prime factorization.  This makes
it easy to represent large numbers.  There are probably more compact wys
to do the job than by using an array of size 25 (for the 25 prime
numbers between 2 and 100), but it is simple and sufficiently effective.

The data is kept in the order it is determined; a linear search is used
to find a match.  There isn't a trivial way to determine whether (7^2)
is greater or smaller than (2)(5^2) (using `^` to denote exponentiation,
of course).

I regard this as the hardest of the six challenges, at least when coding
in C.

Having studied the output from the PHP solution, I believe it works with
`double` rather than exact integer arithmetic.  That may be sufficient,
as the numbers are unlikely to be all that similar.  Working with prime
factorizations is still neat.  It would be possible to calculate (a
sufficiently good approximateion to) the actual numbers using `double`
in C, of course.

Only 9801 - 9183 = 618 duplicated entries occur.

### Challenge 5: Kaprekars Constant (from [CoderByte](https://www.coderbyte.com/editor/Kaprekars%20Constant:JavaScript))

> Have the function `KaprekarsConstant(num)` take the `num` parameter
> being passed which will be a 4-digit number with at least two distinct
> digits.  Your program should perform the following routine on the
> number: Arrange the digits in descending order and in ascending order
> (adding zeroes to fit it to a 4-digit number), and subtract the
> smaller number from the bigger number.  Then repeat the previous step.
> Performing this routine will always cause you to reach a f3ixed
> number: 6174.  Then performing the routine on 6174 will always give
> you 6174 (7641 - 1467 = 6174).  Your program should return the number
> of times this routine must be performed until 6174 is reached.  For
> example, if `num` is 3524, your program should return 3 because of the
> following steps: (1) 5432 - 2345 = 3087, (2) 8730 - 0378 = 8352, (3)
> 8532 - 2358 = 6174.

> Hard challenges are worth 15 points and you are not timed for them.

> Examples:

>     Input: 2111
>     Output: 5

>     Input: 9831
>     Output: 7

Solution 5: `kaprekars-constant-17.c`

The algorithm is straight-forward.  It uses `qsort()` to sort the
digits, which is almost overkill.  The program processes all the numbers
from 0000..9999 except those with 4 identical digits (which generates
zero for the difference which never progresses to Kaprekar's Constant).
The unacceptable numbers are those with no remainder when divided by
1111.

The code is straight-forward too.  GCC witters unreasonably if you limit
thesize of buffers to 5 (which is sufficient for 4-digit numbers, but
GCC has problems with it, and the wasted space using 12 instead of 5 a
few times (emphasis on few) isn't worth the hassle.

The maximum number of steps required to converge to Kaprekar's Constant
(6174) is 7.  The minimum is 0 (when the input is 6174).

### Challenge 6: Swap Nodes in Pairs (from [LeetCode](https://leetcode.com/problems/swap-nodes-in-pairs))

> Given a linked list, swap every two adjacent nodes and return its head.

> You may not modify the values in the list's node, only nodes itself
> may be changed.

> Example:

>     Given 1->2->3->4, you should return the list 2->1->4->3.

Solution 6: `revpairs71.c`

Clearly, arrays make this trivial, but they aren't relevant.  Drawing a
diagram helps enormously.  I ended up using a diagram like this:

    Before:

      prev            curr            next            yonder
    +--------+      +--------+      +--------+      +--------+
    | X      |----->| 1      |----->| 2      |----->| Y      |
    +--------+      +--------+      +--------+      +--------+

    After:

      prev            curr            next            yonder
    +--------+      +--------+      +--------+      +--------+
    | X      |-+ +->| 1      |-+ +->| 2      |-+ +->| Y      |
    +--------+ | |  +--------+ | |  +--------+ | |  +--------+
               | |             | |             | |
               +-|-------------|-+             | |
                 +-------------|---------------+ |
                               +-----------------+

At the start of the next cycle, the Y node becomes the new current node,
the 1 node becomes the new previous node, and the node after the Y node
becomes the new next node.

With a little care, the pointer processing is fairly straight-forward.
Using a dummy head node as the initial previous node eliminates the
special case for the first cycle, which is very beneficial.

### Summary

When coding in C, the hardest problem to resolve is number 4, the
distinct powers problem.  With a good insight, it is soluble without
formally calculating the value of 100^100.

Problems 5 & 6 are supposed to be the hardest, but with C, number 6 is
not quite elementary, but certainly not hard.  And number 5 is not very
hard either.  It is interesting how different languages and different
sets of built-in library functions colour perceptions of difficulty.


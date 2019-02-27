## Stack Overflow Question 4418-8297

[SO 4418-8297](https://stackoverflow.com/q/44188297) &mdash;
How to allocate triangular array using a single malloc in C?

### Question

> I am trying to allocate triangular array using single malloc but I
> could'nt find any solution for this.  My structure is something like
> this:

>     a  -  -  -  - 
>     b  c  -  -  -  
>     d  e  f  -  -  
>     g  h  i  j  -
>     k  l  m  n  o

> I've made it using two malloc.

### Answer

How are you planning to use the structure — what code would you write
to access an array element?
Also, what size of array are you dealing with?

If the array is small enough (say less than 100x100, but the boundary
value is negotiable) then it makes sense to use a regular rectangular
array and access that as usual, accepting that some of the allocated
space is unused.
If the array will be large enough that the unused space will be
problematic, then you have to work harder.

Do you plan to use lt_matrix[r][c] notation, or could you use a 1D array
lt_matrix[x] where x is calculated from r and c?
If you can use the 1D notation, then you can use a single allocation —
as shown in Technique 1 in the code below.
If you use the double-subscript notation, you should probably do two
memory allocations — as shown in Technique 2 in the code below.
If you don't mind living dangerously, you can mix things up with
Technique 3, but it isn't recommended that you use it unless you can
determine what the limitations and issues are and assess for yourself
whether it is safe enough for you to use.
(If you ask me, the answer's "No; don't use it", but that could be
regarded as being over-abundantly cautious.)

> code from `lt67.c`

The output from the program is:

    a  -  -  -  -  
    b  c  -  -  -  
    d  e  f  -  -  
    g  h  i  j  -  
    k  l  m  n  o  
    A  -  -  -  -  
    B  C  -  -  -  
    D  E  F  -  -  
    G  H  I  J  -  
    K  L  M  N  O  
    1  -  -  -  -  
    2  3  -  -  -  
    4  5  6  -  -  
    7  8  9  10 -  
    11 12 13 14 15 

Valgrind version 3.13.0.SVN (revision 16398) gives this a clean bill of
health on macOS Sierra 10.12.5 using GCC 7.1.0.

<hr>

The code here is essentially what was posted on SO.
The 'Technique 3' code isn't as dangerous as the comments in the answer
make out.
On many machines, for many data types, it will be fine.
The issues come if you're working on a machine with 32-bit pointers and
a data type like `double` that needs 8-byte alignment but there is an
odd number of rows in the matrix so that the size of the array of
pointers isn't as well aligned as you need.
There are ways around that, of course, and they're not particularly
hard, even; but you need to be aware of what you're up to.


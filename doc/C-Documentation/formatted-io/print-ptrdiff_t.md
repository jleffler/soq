# Printing the difference between two pointers to the same object

[Subtracting the values of two pointers][1] to an object results in a signed integer <sup>*1</sup>. So it would be printed using *at least* the `d` conversion specifier.

To make sure there is a type being wide enough to hold such a "pointer-difference", since C99 `<stddef.h>` defines the type `ptrdiff_t`. To print a `ptrdiff_t` use the `t` length modifier.

<!-- if version [gte C99] -->

    #include <stdlib.h> /* for EXIT_SUCCESS */
    #include <stdio.h> /* for printf() */
    #include <stddef.h> /* for ptrdiff_t */


    int main(void)
    {
      int a[2];
      int * p1 = &a[0], * p2 = &a[1];
      ptrdiff_t pd = p2 - p1;

      printf("p1 = %p\n", (void*) p1);
      printf("p2 = %p\n", (void*) p2);
      printf("p2 - p1 = %td\n", pd);

      return EXIT_SUCCESS;
    }

The result might look like this:

    p1 = 0x7fff6679f430
    p2 = 0x7fff6679f434
    p2 - p1 = 1

Please note that the resulting value of the difference is scaled by the size of the type the pointers subtracted point to, an `int` here. The size of an `int` for this example is 4.

---------------------

<sup>*1</sup>If the two pointers to be subtracted do not point to the same object the behaviour is undefined.
<!-- end version if -->


  [1]: http://stackoverflow.com/documentation/c/256/operators/2205/pointer-arithmetic#t=201607261026480437786

# Printing the Difference of the Values of two Pointers to an Object

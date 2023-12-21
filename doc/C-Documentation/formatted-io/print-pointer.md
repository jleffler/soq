# Printing the Value of a Pointer to an Object

To print the value of a pointer to an object (as opposed to a function pointer) use the `p` conversion specifier. It is defined to print `void`-pointers only, so to print out the value of a non `void`-pointer it needs to be explicitly converted ("casted*") to `void*`.

    #include <stdlib.h> /* for EXIT_SUCCESS */
    #include <stdio.h>  /* for printf() */

    int main(void)
    {
      int i;
      int * p = &i;

      printf("The address of i is %p.\n", (void*) p);

      return EXIT_SUCCESS;
    }


<!-- if version [gte c99] -->

### Using `<inttypes.h>` and `uintptr_t`

Another way to print pointers in C99 or later uses the `uintptr_t` type and the macros from `<inttypes.h>`:

    #include <inttypes.h> /* for uintptr_t and PRIXPTR */
    #include <stdio.h>    /* for printf() */

    int main(void)
    {
      int  i;
      int *p = &i;

      printf("The address of i is 0x%" PRIXPTR ".\n", (uintptr_t)p);

      return 0;
    }

In theory, there might not be an integer type that can hold any pointer converted to an integer (so the type `uintptr_t` might not exist).  In practice, it does exist.  Pointers to functions need not be convertible to the `uintptr_t` type — though again they most often are convertible.

If the `uintptr_t` type exists, so does the `intptr_t` type.  It is not clear why you'd ever want to treat addresses as signed integers, though.

<!-- end version if -->


<!-- if version [eq K&R] [lt c89] -->

Pre-Standard History:
---------------------

Prior to C89 during K&R-C times there was no type `void*` (nor header `<stdlib.h>`, nor prototypes, and hence no `int main(void)` notation), so the pointer was cast to `long unsigned int` and printed using the `lx` length modifier/conversion specifier.

**The example below is just for informational purpose. Nowadays this is invalid code, which very well might provoke the infamous [Undefined Behaviour][1].**

    #include <stdio.h> /* optional in pre-standard C - for printf() */

    int main()
    {
      int  i;
      int *p = &i;

      printf("The address of i is 0x%lx.\n", (long unsigned) p);

      return 0;
    }

<!-- end version if -->


  [1]: http://stackoverflow.com/documentation/c/364/undefined-behavior


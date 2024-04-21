### Stack Overflow Question 7776-8267

[SO 7776-8267](https://stackoverflow.com/q/77768267) &mdash;
Palindrome String

### Jonathan's answer:

Although it's possible to map the input to 'all letters' and then do the
palindromic comparison, it is not necessary to do so.  It is crucial to
use the character classification facilities from `<ctype.h>`.  This code
won't work on Unicode (UTF-8) data outside the ASCII range, though —
it must be a single-byte code set that is used.

This code works on non-degenerate cases:

```
#include <ctype.h>
#include <stdbool.h>    /* Won't be need in C23 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char string[100];
    while (scanf(" %99[^\n]", string) == 1)
    {
        size_t j = strlen(string) - 1;
        size_t i = 0;

        bool is_palindrome = true;
        while (i < j)
        {
            while (!isalpha((unsigned char)string[i]) && i < j)
                i++;
            while (!isalpha((unsigned char)string[j]) && i < j)
                j--;
            if (tolower((unsigned char)string[i]) != tolower((unsigned char)string[j]))
            {
                is_palindrome = false;
                break;
            }
            i++;
            j--;
        }

        printf("The string [%s] %s a palindrome\n", string,
                (is_palindrome ? "is" : "is not"));
    }
    return 0;
}
```

For example, given the data file:

```none
 madam
 racecar
 radar
 a man a plan a canal panama
 a man a pla n a cana L Panama
 Cigar? Toss it in a can, It is sotragic
 ambivalent
 (    Not=a=palin=drome   )
 (    A=man=a=PlaN=A=Canal===Panama!!!   )
     LeadingBlanksknalbgnidael          
```

Where there are trailing blanks on the last line, the program above gives the output:

```none
The string [madam] is a palindrome
The string [racecar] is a palindrome
The string [radar] is a palindrome
The string [a man a plan a canal panama] is a palindrome
The string [a man a pla n a cana L Panama] is a palindrome
The string [Cigar? Toss it in a can, It is sotragic] is a palindrome
The string [ambivalent] is not a palindrome
The string [(    Not=a=palin=drome   )] is not a palindrome
The string [(    A=man=a=PlaN=A=Canal===Panama!!!   )] is a palindrome
The string [LeadingBlanksknalbgnidael          ] is a palindrome
```

I didn't notice until I pasted it that there was at least one leading
blank on each line.  The `%[…]` (scan set) conversion specifier —
like the `%c` and `%n` conversion specifiers, but unlike all other
conversion specifiers — does not skip white space.  However, on the
subsequent lines, I want the code to skip over the newline left behind
by the previous input, hence the leading space in the `" %99[^\n"`
format string.

The casts to `(unsigned char)` are noisy but necessary.  The functions
declared in `<ctype.h>` don't work reliably with negative values if the
type of plain `char` is signed (which it is on most machines these
days).

C11 [§7.4 Character handling `<ctype.h>` ¶1](https://port70.net/~nsz/c/c11/n1570.html#7.4p1):

> In all cases the argument is an `int`, the value of which shall be
> representable as an `unsigned char` or shall equal the value of the
> macro `EOF`.  If the argument has any other value, the behavior is
> undefined.

Another way to deal with this would be to treat the `string` array as
`unsigned char` by defining `unsigned char *str = (unsigned char
*)string;` and then using `str[i]` or `str[j]` where the code currently
uses `string[i]` or `string[j]`, and then the noisy casts in the calls
to `isalpha()` etc would not be necessary any more.

<hr>

As [chqrlie](https://stackoverflow.com/users/4593267/chqrlie) rightly
pointed out in a
[comment](https://stackoverflow.com/questions/77768267/palindrome-string#comment137104920_77768436),
the code above does not work correctly when the input is a single letter
and any non-zero number of trailing blanks (e.g. [`a `]).

The trouble is that the code unconditionally decrements `j` when `j` is
zero after testing that `string[i]` equals `string[j]`.  I think the
simplest and cleanest fix is to break the loop if `i == j` before
comparing the letters.

This code also creates `unsigned char *text = (unsigned char *)string;`
and then indexes into `text` to avoid the repeated casts in the calls to
`isalpha()` and `tolower()`.

There is also a mildly interesting question: is a string that contains
no letters a palindrome?  It hinges on the definition of a palindrome.
If it is a sequence of one or more "words" (where a word consists of one
or more letters) that reads the same backwards as it does forwards
(ignoring the case of the letters and word breaks), then a string that
contains no letters is not a palindrome.  If you define a palindrome as
a sequence of characters where the sequence of letters (ignoring
non-letters and the case of the letters) is the same backwards as it is
forwards, then a string with no letters is a palindrome.  The question
doesn't stipulate the required result for a zero-letter string —
either result is legitimate.  The code assumes that a string devoid of
letters is a palindrome.

```
/* SO 7776-8267 */
#include <assert.h>
#include <ctype.h>
#include <stdbool.h> /* Won't be needed in C23 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char string[100];
    while (scanf(" %99[^\n]", string) == 1)
    {
        assert(strlen(string) != 0);
        size_t j = strlen(string) - 1;
        size_t i = 0;
        unsigned char *text = (unsigned char *)string;

        bool is_palindrome = true;
        while (i < j)
        {
            while (i < j && !isalpha(text[i]))
                i++;
            while (i < j && !isalpha(text[j]))
                j--;
            if (i == j)
                break;
            if (tolower(text[i]) != tolower(text[j]))
            {
                is_palindrome = false;
                break;
            }
            i++;
            j--;
        }

        printf("The string [%s] %s a palindrome\n", string,
                (is_palindrome ? "is" : "is not"));
    }
    return 0;
}
```

It produces the same output on the original test data.  It also
correctly claims that all but one of these strings are palindromes:

```none
The string [a] is a palindrome
The string [a ] is a palindrome
The string [a  ] is a palindrome
The string [aa] is a palindrome
The string [ab] is not a palindrome
The string [aba] is a palindrome
The string [abXba] is a palindrome
The string [ab=ba] is a palindrome
The string [= ] is a palindrome
The string [=] is a palindrome
The string [@@] is a palindrome
The string [@@@] is a palindrome
```

---

### Comments

@chqrlie — I agree that the original code misbehaved, but I'm not sure
it is the skipping logic that is imperfect.  The trouble is that
decrementing `j` when it is zero leads to UB when it is used to index
into the string.  I've included modified code and extra testing.  The
code stops looping on EOF or on an all-blank or empty line.  The code
could be improved by having `main()` read the string and then call a
function to determine whether the string is palindromic.

– Jonathan @Leffler Jan 8 2024 at 0:26

The problem for `"a "` was the test for trailing spaces left both `i`
and `j` equal to 0 and the test `tolower(text[i]) != tolower(text[j])`
of course failed so `i` gets incremented to `1` and `j` decremented to
`SIZE_MAX`, thus the `while` loop keeps going and the next access to
`text[j]` has undefined behavior.  Your amended code fixes this problem.

– chqrlie Jan 8 2024 at 20:35 

---

### Observations

The code would be better with a function to evaluate whether a string is
a palindrome rather than mixing up the I/O code with the analysis code.
All else apart, it would use `return` instead of `break`, which
simplifies the code.  This is alluded to in my comment.

The code won't work on UTF-8 because the character classification
functions in `<ctype.h>` won't report accurately on whether bytes
outside the ASCII range (U+0000..U+007F) are letters or not.

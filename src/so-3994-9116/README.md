### Stack Overflow Question 3994-9116

[SO 3994-9116](https://stackoverflow.com/q/39949116) &mdash;
Why is my trie leaking data?

[SO 4997-3644](https://stackoverflow.com/q/49973644) &mdash;
Changing a string without delimiters into corresponding numbers.

> For example I have "onethousandtwohundredandtwentysix" as input and
> the corresponding output should be 1226 (in digits) in C++.
> Can someone help me by showing how to parse the string when delimiters
> for eg "blank spaces" are not present in a string in C++.

The second question was deleted (too broad, abandoned).

It is nevertheless an interesting question.
It requires a trie-based search algorithm — most of the other trie
questions stop at building the trie rather than really using it.

For the example in the question "onethousandtwohundredandtwentysix",
there is interesting analysis required.

There was a possible duplicate identified:

* [SO 0007-0161](https://stackoverflow.com/q/70161) &mdash;
How to read values from numbers written as words?

That is an interesting question too; it has some interesting answers.

### `trie89.c`

Basic code to create a trie and print it and free it, demonstrating that
it can be done.
This is typically sufficient help for those stuck with the problem in
the CS50 course.

### `trie-search13.c`

Basic code to scan a long string looking for consecutive known words in
continuous string of (lower-case) letters.
It stops when it encounters an unknown word.
If the word list it is given is `words.numeric`, then it will look for
consecutive number-related words, stopping when a word is unrecognized.
It uses a semi-coherent command-line argument passing (and parsing)
convention.

### `trie-split59.c`

This extends `trie-search13.c` to identify both known words and unknown
character sequences.
Again, if given a numeric word list, it will identify the known numeric
words and the unknown non-numeric words.
It uses `aoscopy.[ch]` to handle the word lists, which slightly reduces
the length of the code in this source file.

### `trie-split67.c`

This extends `trie-search59.c` using `aommngd.[ch]` to allow strings to
be tagged with what type of character sequence is contained.
It can identify both known words and unknown character sequences.
Again, if given a numeric word list, it will identify the known numeric
words and the unknown non-numeric words.

Maybe it should be enhanced to recognize 'digit sequences' too, as a
separate class from other 'non-alpha'?

The code does not yet drive JLSS `wordnum.c` or `numword.c` (though it
does scan the output from the `numword` program that tests `numword.c`
correctly).
The functions in those files need review and probably generalization.
Perhaps the trickiest part is deciding on the error detection and
reporting in word-to-number processing.
Should the words 'a' and 'an' be allowed as pseudo-numeric words?
What about dozen, or score, or gross?
What about the Indian system of units (crore, lakh, etc)?

### English is a peculiar language

Silly question time:

* one half, three halves, two thirds, three quarters, four fifths, one
  sixth, one seventh, one eighth, two ninths, three tenths, four
  elevenths, five twelfths, six thirteenths, five fourteenths, seven
  fifteenths, one sixteenth, two seventeenths, five eighteenths, four
  nineteenths, three twentieths, ...

  What comes next?
  Four twenty-firsts?
  (That sounds a bit weird, but is there any alternative that isn't
  worse?
  Someone else didn't see anything odd about it, so I'm probably just
  over-thinking.)

  Three twenty-seconds doesn't sound wrong; neither does five
  twenty-thirds or seven twenty-fourths?

Here be rabbit holes!

Twenty seconds has a different meaning from one twenty-second, which
isn't very clear.

* Time flies like an arrow.
* Fruit flies like a banana.

Also, should plural words like 'hundreds' and 'thousands' be included in
the list of numeric words?
Formally, you don't often say 'three hundreds' rather than 'three
hundred', at least not without a change of meaning.

What about 'a' and 'an'? And 'nine and nineteen one hundredths'?

Can Roman numbers be extracted reliably?
Can you distinguish between the first person singular pronoun (I) and
Roman one (i or I)?
(In general, no you can't extract Roman numbers reliably, but it is
easier to extract mcmlcvii than just i).

### Stack Overflow Question 7400-1677

[SO 7400-1677](https://stackoverflow.com/q/74001677) &mdash;
How to differentiate between 1 space and 3 spaces

---

I'm trying to write a C program for a Morse code decoder.  The format of
this code is written in a way so that letters are separated by 1 space
and words are separated by 3 spaces ie.

    -(1 space).- = EA
    -(3 spaces).- = E A

    - .-   = EA
    -   .- = E A

I'm currently using fscanf to read each set of letters but it is
removing all the spaces.  I found that I could use fgets then strtok to
separate the letters themselves however strtok will not differentiate
between 1 space and 3.  I guess my questions are: is there a function
that can differentiate between 1 and 3 spaces, or is there just an
overall better way of thinking about this.

---

The code in `morse17.c` is what was posted as an answer to the question.

The code in `morse19.c` is a mostly functional Morse code encoder and decoder.
At the moment, words can be broken across lines in the Morse code output.
That's sub-optimal, I think.
The output from the decoder (Morse to ASCII) is not good.


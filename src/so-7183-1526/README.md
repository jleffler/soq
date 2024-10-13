### Stack Overflow Question 7183-1526

[SO 7183-1526](https://stackoverflow.com/q/71831526) &mdash;
How can I rotate to left/right all the bits in a byte array by some amount

### Question

I can rotate a word to left or right by a certain amount like this:

    #define ROR(x, r) ((x >> r) | (x << (64 - r)))
    #define ROL(x, r) ((x << r) | (x >> (64 - r)))

    [...]

    ROR(var1, 11);
    ROL(var1, 11);

How can I do the same but with an entire array of bytes (I mean: all the
bits in array sequence)?  An array like this:
```
uint32_t somearray[12] = {
    0xd1310ba6, 0x98dfb5ac, 0x2ffd72db, 0xd01adfb7, 0xb8e1afed, 0x6a267e96,
    0xba7c9045, 0xf12c7f99, 0x24a19947, 0xb3916cf7, 0x0801f2e2, 0x858efc16,
};
```
PS: There is a [similar question here][1], but I need to know how to do it with some amount.

  [1]: https://stackoverflow.com/questions/48346876/transform-rotate-bits-in-byte-array

### Answer

I didn't formally provide an answer to this question.  I found find some issues in one of
the answer, which were subsequently resolved.


### Stack Overflow Question 5468-0129

[SO 5468-0129](https://stackoverflow.com/q/54680129) &mdash;
Clean way to add elements to fixed length array and removing the first element?

Neither a ring buffer solution nor a 'shuffle buffer' solution is
particularly complex.
Here's one of each.
Note that the ring buffer solution stores 15 values in an array of 16;
the shuffle buffer solution use an array of size 15.
The solutions give the same sequence of outputs if you map the entries
such as `( 1: 30)` to `(99: 30)` to allow for the differences in the way
that the data is stored.

Both solutions assume you understand structures (and pointers to
structures too).

### Shuffle Buffer

This corresponds most closely to the code in the question.

* `shuffler11.c`


### Ring Buffer

* `ringbuff29.c`

If your compiler is so antiquated that it doesn't recognize `inline` as
a keyword, simply add `#define inline /* C99 not available */` near the
top of the file (or, better, get a compiler that does recognize the
almost 20-year old standard).

### Sample output from Ring Buffer

    Post insert: (head = 1, tail = 0)
    ( 0:  23)
    Post insert: (head = 2, tail = 0)
    ( 0:  23) ( 1:  30)
    Value 23 removed
    Post remove: (head = 2, tail = 1)
    ( 1:  30)
    Post insert: (head = 3, tail = 1)
    ( 1:  30) ( 2:  37)
    Post insert: (head = 4, tail = 1)
    ( 1:  30) ( 2:  37) ( 3:  44)
    Value 30 removed
    Post remove: (head = 4, tail = 2)
    ( 2:  37) ( 3:  44)
    Post insert: (head = 5, tail = 2)
    ( 2:  37) ( 3:  44) ( 4:  51)
    Post insert: (head = 6, tail = 2)
    ( 2:  37) ( 3:  44) ( 4:  51) ( 5:  58)
    Value 37 removed
    Post remove: (head = 6, tail = 3)
    ( 3:  44) ( 4:  51) ( 5:  58)
    Post insert: (head = 7, tail = 3)
    ( 3:  44) ( 4:  51) ( 5:  58) ( 6:  65)
    Post insert: (head = 8, tail = 3)
    ( 3:  44) ( 4:  51) ( 5:  58) ( 6:  65) ( 7:  72)
    Value 44 removed
    Post remove: (head = 8, tail = 4)
    ( 4:  51) ( 5:  58) ( 6:  65) ( 7:  72)
    Post insert: (head = 9, tail = 4)
    ( 4:  51) ( 5:  58) ( 6:  65) ( 7:  72) ( 8:  79)
    Post insert: (head = 10, tail = 4)
    ( 4:  51) ( 5:  58) ( 6:  65) ( 7:  72) ( 8:  79)
    ( 9:  86)
    Value 51 removed
    Post remove: (head = 10, tail = 5)
    ( 5:  58) ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86)
    Post insert: (head = 11, tail = 5)
    ( 5:  58) ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86)
    (10:  93)
    Post insert: (head = 12, tail = 5)
    ( 5:  58) ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86)
    (10:  93) (11: 100)
    Value 58 removed
    Post remove: (head = 12, tail = 6)
    ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86) (10:  93)
    (11: 100)
    Post insert: (head = 13, tail = 6)
    ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86) (10:  93)
    (11: 100) (12: 107)
    Post insert: (head = 14, tail = 6)
    ( 6:  65) ( 7:  72) ( 8:  79) ( 9:  86) (10:  93)
    (11: 100) (12: 107) (13: 114)
    Value 65 removed
    Post remove: (head = 14, tail = 7)
    ( 7:  72) ( 8:  79) ( 9:  86) (10:  93) (11: 100)
    (12: 107) (13: 114)
    Post insert: (head = 15, tail = 7)
    ( 7:  72) ( 8:  79) ( 9:  86) (10:  93) (11: 100)
    (12: 107) (13: 114) (14: 121)
    Post insert: (head = 0, tail = 7)
    ( 7:  72) ( 8:  79) ( 9:  86) (10:  93) (11: 100)
    (12: 107) (13: 114) (14: 121) (15: 128)
    Value 72 removed
    Post remove: (head = 0, tail = 8)
    ( 8:  79) ( 9:  86) (10:  93) (11: 100) (12: 107)
    (13: 114) (14: 121) (15: 128)
    Post insert: (head = 1, tail = 8)
    ( 8:  79) ( 9:  86) (10:  93) (11: 100) (12: 107)
    (13: 114) (14: 121) (15: 128) ( 0: 135)
    Post insert: (head = 2, tail = 8)
    ( 8:  79) ( 9:  86) (10:  93) (11: 100) (12: 107)
    (13: 114) (14: 121) (15: 128) ( 0: 135) ( 1: 142)
    Value 79 removed
    Post remove: (head = 2, tail = 9)
    ( 9:  86) (10:  93) (11: 100) (12: 107) (13: 114)
    (14: 121) (15: 128) ( 0: 135) ( 1: 142)
    Post insert: (head = 3, tail = 9)
    ( 9:  86) (10:  93) (11: 100) (12: 107) (13: 114)
    (14: 121) (15: 128) ( 0: 135) ( 1: 142) ( 2: 149)
    Post insert: (head = 4, tail = 9)
    ( 9:  86) (10:  93) (11: 100) (12: 107) (13: 114)
    (14: 121) (15: 128) ( 0: 135) ( 1: 142) ( 2: 149)
    ( 3: 156)
    Value 86 removed
    Post remove: (head = 4, tail = 10)
    (10:  93) (11: 100) (12: 107) (13: 114) (14: 121)
    (15: 128) ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156)
    Post insert: (head = 5, tail = 10)
    (10:  93) (11: 100) (12: 107) (13: 114) (14: 121)
    (15: 128) ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156)
    ( 4: 163)
    Post insert: (head = 6, tail = 10)
    (10:  93) (11: 100) (12: 107) (13: 114) (14: 121)
    (15: 128) ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156)
    ( 4: 163) ( 5: 170)
    Value 93 removed
    Post remove: (head = 6, tail = 11)
    (11: 100) (12: 107) (13: 114) (14: 121) (15: 128)
    ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163)
    ( 5: 170)
    Post insert: (head = 7, tail = 11)
    (11: 100) (12: 107) (13: 114) (14: 121) (15: 128)
    ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163)
    ( 5: 170) ( 6: 177)
    Post insert: (head = 8, tail = 11)
    (11: 100) (12: 107) (13: 114) (14: 121) (15: 128)
    ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163)
    ( 5: 170) ( 6: 177) ( 7: 184)
    Value 100 removed
    Post remove: (head = 8, tail = 12)
    (12: 107) (13: 114) (14: 121) (15: 128) ( 0: 135)
    ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170)
    ( 6: 177) ( 7: 184)
    Post insert: (head = 9, tail = 12)
    (12: 107) (13: 114) (14: 121) (15: 128) ( 0: 135)
    ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170)
    ( 6: 177) ( 7: 184) ( 8: 191)
    Post insert: (head = 10, tail = 12)
    (12: 107) (13: 114) (14: 121) (15: 128) ( 0: 135)
    ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170)
    ( 6: 177) ( 7: 184) ( 8: 191) ( 9: 198)
    Value 107 removed
    Post remove: (head = 10, tail = 13)
    (13: 114) (14: 121) (15: 128) ( 0: 135) ( 1: 142)
    ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177)
    ( 7: 184) ( 8: 191) ( 9: 198)
    Post insert: (head = 11, tail = 13)
    (13: 114) (14: 121) (15: 128) ( 0: 135) ( 1: 142)
    ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177)
    ( 7: 184) ( 8: 191) ( 9: 198) (10: 205)
    Post insert: (head = 12, tail = 13)
    (13: 114) (14: 121) (15: 128) ( 0: 135) ( 1: 142)
    ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177)
    ( 7: 184) ( 8: 191) ( 9: 198) (10: 205) (11: 212)
    Value 114 removed
    Post remove: (head = 12, tail = 14)
    (14: 121) (15: 128) ( 0: 135) ( 1: 142) ( 2: 149)
    ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177) ( 7: 184)
    ( 8: 191) ( 9: 198) (10: 205) (11: 212)
    Post insert: (head = 13, tail = 14)
    (14: 121) (15: 128) ( 0: 135) ( 1: 142) ( 2: 149)
    ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177) ( 7: 184)
    ( 8: 191) ( 9: 198) (10: 205) (11: 212) (12: 219)
    Post insert: (head = 14, tail = 15)
    (15: 128) ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156)
    ( 4: 163) ( 5: 170) ( 6: 177) ( 7: 184) ( 8: 191)
    ( 9: 198) (10: 205) (11: 212) (12: 219) (13: 226)
    Value 128 removed
    Post remove: (head = 14, tail = 0)
    ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163)
    ( 5: 170) ( 6: 177) ( 7: 184) ( 8: 191) ( 9: 198)
    (10: 205) (11: 212) (12: 219) (13: 226)
    Post insert: (head = 15, tail = 0)
    ( 0: 135) ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163)
    ( 5: 170) ( 6: 177) ( 7: 184) ( 8: 191) ( 9: 198)
    (10: 205) (11: 212) (12: 219) (13: 226) (14: 233)
    Post insert: (head = 0, tail = 1)
    ( 1: 142) ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170)
    ( 6: 177) ( 7: 184) ( 8: 191) ( 9: 198) (10: 205)
    (11: 212) (12: 219) (13: 226) (14: 233) (15: 240)
    Value 142 removed
    Post remove: (head = 0, tail = 2)
    ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177)
    ( 7: 184) ( 8: 191) ( 9: 198) (10: 205) (11: 212)
    (12: 219) (13: 226) (14: 233) (15: 240)
    Post insert: (head = 1, tail = 2)
    ( 2: 149) ( 3: 156) ( 4: 163) ( 5: 170) ( 6: 177)
    ( 7: 184) ( 8: 191) ( 9: 198) (10: 205) (11: 212)
    (12: 219) (13: 226) (14: 233) (15: 240) ( 0: 247)
    …
    Post insert: (head = 3, tail = 4)
    ( 4: 611) ( 5: 618) ( 6: 625) ( 7: 632) ( 8: 639)
    ( 9: 646) (10: 653) (11: 660) (12: 667) (13: 674)
    (14: 681) (15: 688) ( 0: 695) ( 1: 702) ( 2: 709)
    Post insert: (head = 4, tail = 5)
    ( 5: 618) ( 6: 625) ( 7: 632) ( 8: 639) ( 9: 646)
    (10: 653) (11: 660) (12: 667) (13: 674) (14: 681)
    (15: 688) ( 0: 695) ( 1: 702) ( 2: 709) ( 3: 716)
    Value 618 removed
    Post remove: (head = 4, tail = 6)
    ( 6: 625) ( 7: 632) ( 8: 639) ( 9: 646) (10: 653)
    (11: 660) (12: 667) (13: 674) (14: 681) (15: 688)
    ( 0: 695) ( 1: 702) ( 2: 709) ( 3: 716)
    Insert/remove loop over
    Value 625 removed
    Value 632 removed
    Value 639 removed
    Value 646 removed
    Value 653 removed
    Value 660 removed
    Value 667 removed
    Value 674 removed
    Value 681 removed
    Value 688 removed
    Value 695 removed
    Value 702 removed
    Value 709 removed
    Value 716 removed

### Timing

With the main loop repeating 100 times, there's not really a measurable
difference between the two programs if you disable the printing, and its
only barely measurable and not entirely reliable if you enable the
printing.

With printing disabled and the buffer size of 15 or 16, looping one
million times in the main program took 4.5 ms for ring buffer vs 9.0 ms
for shuffle buffer.
Change the buffer size to 2047 or 2048, and the times were 3.7 ms for
ring buffer vs 87.3 ms for shuffle buffer.
With the printing enabled, the slight extra work done by ring buffer in
the printing swamped the performance gain from not shuffling; the two
programs were running in essentially the same time: 4,546.5 ms vs
4,477.2 ms (so shuffle buffer was slightly faster with the printing
enabled — in large part because it produced only 353 MiB of data
compared with 368 MiB of data from the ring buffer — with the data
being written to `/dev/null` with the timing runs).

The measured times were elapsed run time for the executable — not CPU
time per se.
The testing was done an a 15" MacBook Pro (2017) with 2.9 GHz Intel Core
i7 with 16 GiB of 2133 MHz [LPDDR3](https://en.wikipedia.org/wiki/LPDDR)
RAM, running macOS 10.14.3 Mojave and using a home-built GCC 8.2.0.
Speed testing is difficult — I think the results without printing are
meaningful, but [YMMV](https://www.acronymfinder.com/YMMV.html).
If you ever needed a demonstration that 'printing is slow', this is
quite possibly a good one.


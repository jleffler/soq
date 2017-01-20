### Stack Overflow Question 0612-7503

[SO 0612-7503](http://stackoverflow.com/q/06127503) &mdash;
Shuffle array in C

Note the discussions at:

* [Fisher-Yates Shuffle](http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
  on Wikipedia.
* [Ben Pfaff's implementation](http://benpfaff.org/writings/clc/shuffle.html)
  on his web site.
* [The Danger of Naivete](http://www.codinghorror.com/blog/2007/12/the-danger-of-naivete.html)
  on the Coding Horror blog site.
* [Why does this simple shuffle algorithm produce biassed results?](http://stackoverflow.com/questions/859253)
  on SO.
* [Is this C implementation of Fisher-Yates shuffle correct?](https://stackoverflow.com/questions/3343797/)
  on SO, especially the answer by Roland Ilig.

No doubt there are many other relevant sources.
For general purpose code, you probably need to use a custom random
number generator rather than co-opting the sequence from `rand()`.
For example, `nrand48()` allows each user (e.g. the shuffle code) to
have an independent sequence of random numbers without interference by
or to other code using random number generation.
This is critical for high quality library functions.
The choice of which such random number generator is up to the user.
Consider the merits of `/dev/urandom` too — remembering that
repeatability is not one of the merits.
And on BSD-derived systems, `arc4random()` may be a good choice.


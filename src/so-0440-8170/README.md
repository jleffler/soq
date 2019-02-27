# String Replacement Algorithm

I'm not convinced this is great code, but it works for the simple cases
tested (and one not-so-simple test case).  One problem is the interface,
overwriting the original string.

The over-writing bug (and fix) was reported in comments on the SO
4401870 web page 2016-07-03.

The original code was written by
[Brandin](https://stackoverflow.com/users/1691280/brandin).

Related questions on SO include (far from a definitive list):

* [Looking for PHP-like str_replace() for C/C++ but WITHOUT malloc()/realloc(), using the original buffer](https://stackoverflow.com/questions/14653564)
* [For string, find and replace](https://stackoverflow.com/questions/4408170/)
* [What is the function to replace string in C?](https://stackoverflow.com/questions/779875)
* [What is the best way for replace with more performance using C?](https://stackoverflow.com/questions/44894213)

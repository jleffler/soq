### Stack Overflow Question 4685-9611

[SO 4685-9611](https://stackoverflow.com/q/46859611) &mdash;
How to filter fqdn of x.y.c.d where x.y is random, but c.d is fixed?

Not a very well written question, but the gist is that given a bunch of
FQDNs, the code should print the 2-part domain name of those domains
with 4 or more parts, where there are 4 or more entries with the same
3-part domain.

Given:

    p66-contacts.fe.apple-dns.net
    p39-contacts.fe.apple-dns.net
    p11-content.fe.apple-dns.net
    p54-content.fe.apple-dns.net

The output should be `apple-dns.net` because there are 4 entries with
`fe.apple-dns.net` as the 3-part domain names.

There are multiple solutions proffered by 3 people.
The OP has not yet selected an answer, or otherwise been forthcoming.

The Perl solutions are mine.
The 'random double-digit prime numbers' happened to be genereated in
reverse order, so 97 ws the first solution, 83 was more compact, and 73
is the most compact.
I'm not sure how maintainable 73 is - it needs more explanation.

The `awk`-based solutions from
[ctac](https://stackoverflow.com/users/8592975/ctac) (whose name
formally ends with an underscore, but that wreaks havoc on Markdown
formatting, at least in Vim) are in the files prefixed `ctac`.
The `awk` code can be upgraded so it will work, using appropriate
associative arrays, very much along the lines of my Perl solution.

The all shell solutions from [David C
Rankin](https://stackoverflow.com/users/3422102/david-c-rankin) are in
the files prefixed `rankin`.
This solution only works if the data is in a file whereas my solutions
and Awk solutions scan the data just once.
Consequently, if the file is big enough, these will be measurably slower
than the alternatives.


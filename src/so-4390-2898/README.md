# What does (?^:…) mean in a Perl qr// Regex?

Text of question [SO 4390-2898](https://stackoverflow.com/q/43902898).

<hr>

Consider this script, which is based on an answer to
[SO 267399](https://stackoverflow.com/q/267399) about parsing Roman
number, though the parsing of Roman numbers is incidental to this
question.

    #!/usr/bin/env perl
    #
    # Based on answer to SO 0026-7399

    use warnings;
    use strict;

    my $qr1 = qr/(?i:M{1,3})/;
    my $qr2 = qr/(?i:C[MD]|D?C{1,3})/;
    my $qr3 = qr/(?i:X[CL]|L?X{1,3})/;
    my $qr4 = qr/(?i:I[XV]|V?I{1,3})/;

    print "1000s: $qr1\n";
    print " 100s: $qr2\n";
    print "  10s: $qr3\n";
    print "   1s: $qr4\n";

    # This $qr is too simple — it matches the empty string
    #my $qr = qr/($qr1?$qr2?$qr3?$qr4?)/;

    my $qr = qr/\b((?:$qr1$qr2?$qr3?$qr4?)|(?:$qr2$qr3?$qr4?)|(?:$qr3$qr4?)|(?:$qr4))\b/;

    print " Full: $qr\n";

    while (<>)
    {
        chomp;
        print " Line: [$_]\n";
        while ($_ =~ m/$qr/g)
        {
            print "Match: [$1] found in [$_] using qr//\n";
        }
    }

Given the data file below, the first three lines each contain a Roman number.

    mix in here
    no mix in here
    mmmcmlxxxix
    minimum

When run with (home-built) Perl 5.22.0 on a Mac now running macOS Sierra
10.12.4, I get output like this (but the version of Perl is not
critical):

    1000s: (?^:(?i:M{1,3}))
     100s: (?^:(?i:C[MD]|D?C{1,3}))
      10s: (?^:(?i:X[CL]|L?X{1,3}))
       1s: (?^:(?i:I[XV]|V?I{1,3}))
     Full: (?^:\b((?:(?^:(?i:M{1,3}))(?^:(?i:C[MD]|D?C{1,3}))?(?^:(?i:X[CL]|L?X{1,3}))?(?^:(?i:I[XV]|V?I{1,3}))?)|(?:(?^:(?i:C[MD]|D?C{1,3}))(?^:(?i:X[CL]|L?X{1,3}))?(?^:(?i:I[XV]|V?I{1,3}))?)|(?:(?^:(?i:X[CL]|L?X{1,3}))(?^:(?i:I[XV]|V?I{1,3}))?)|(?:(?^:(?i:I[XV]|V?I{1,3}))))\b)
     Line: [mix in here]
    Match: [mix] found in [mix in here] using qr//
     Line: [no mix in here]
    Match: [mix] found in [no mix in here] using qr//
     Line: [mmmcmlxxxix]
    Match: [mmmcmlxxxix] found in [mmmcmlxxxix] using qr//
     Line: [minimum]

The only part of the output that I don't understand is the caret `^` in the
`(?^:…)` notation.

I've looked at Perl documentation for
[`perlre`](http://perldoc.perl.org/perlre.html) and
[`perlref`](http://perldoc.perl.org/perlreref.html) and even the section of
[`perlop`](http://perldoc.perl.org/perlop.html#Regexp-Quote-Like-Operators)
on 'Regex quote-like operators' without seeing this exemplified or
explained.

There are two parts to my question:

1. What is the significance of the caret in `(?^:…)` and what caused
   it to be added to the `qr//` regexes?
2. If it matters, how do you stop it from being added to the `qr//` regexes?

<hr>

The short [answer](https://stackoverflow.com/a/43902948/) is that I
missed it in the documentation:

> Basically it means the default flags apply (even if it gets
> interpolated into a regex that specifies differently).
> Before it was introduced, qr would produce something like (?-ismx: and
> a new flag being added to Perl would make that change, which m ade
> keeping tests up to date a pain.

> * http://perldoc.perl.org/perlre.html#Extended-Patterns:

> Starting in Perl 5.14, a "^" (caret or circumflex accent) immediately
> after the "?" is a shorthand equivalent to d-imnsx .
> Flags (except "d" ) may follow the caret to override it.
> But a minus sign is not legal with it.


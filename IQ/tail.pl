#!/usr/bin/env perl
use strict;
use warnings;

my $nlines = 10;
my @lines;
while (<>)
{
    push @lines, $_;
    shift @lines if scalar @lines > $nlines;
}

print foreach (@lines);

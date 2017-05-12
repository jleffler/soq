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

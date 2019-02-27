#!/usr/bin/env perl
#
# Based on answer to SO 0026-7399

use warnings;
use strict;
#use re 'strict';   # Reports itself as experimental with 5.22.0 and makes no difference

# Working, but more stringent than intended
my $qr1 = qr/(?i:M{0,3})/;
my $qr2 = qr/(?i:C[MD]|D?C{0,3})?/;
my $qr3 = qr/(?i:X[CL]|L?X{0,3})?/;
my $qr4 = qr/(?i:I[XV]|V?I{0,3})?/;

print "1000s: $qr1\n";
print " 100s: $qr2\n";
print "  10s: $qr3\n";
print "   1s: $qr4\n";

my $qr = qr/($qr1$qr2$qr3$qr4)/;

print " Full: $qr\n";

while (<>)
{
    chomp;
    print " Line: [$_]\n";
    while ($_ =~ m/$qr/g)
    {
    print "Match: [$1] found in [$_] using qr//\n" ;#if ($_ =~ $qr); # && length($1) > 0);
    }
    #print "Match: [$1] found in [$_] using qr//\n" if ($_ =~ $qr); # && length($1) > 0);
    print "Match: [$1] found in [$_] using m//\n"
        if m/( (?i:M{0,3}) (?i:C[MD]|D?C{0,3})? (?i:X[CL]|L?X{0,3})? (?i:I[XV]|V?I{0,3})? )/x;
}

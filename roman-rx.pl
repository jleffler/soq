#!/usr/bin/env perl
#
# JL answer to SO 0026-7399

use warnings;
use strict;

# Not working yet
#my $qr1 = qr/(?i:M{0,3})/;
#my $qr2 = qr/(?i:C[MD]|D?C{0,3})?/;
#my $qr3 = qr/(?i:X[CL]|L?X{0,3})?/;
#my $qr4 = qr/(?i:I[XV]|V?I{0,3})?/;

# Working, but more stringent than intended
my $qr1 = qr/(?i:M{0,3})/;
my $qr2 = qr/(?i:C[MD]|D?C{0,3})?/;
my $qr3 = qr/(?i:X[CL]|L?X{0,3})?/;
my $qr4 = qr/(?i:I[XV]|V?I{0,3})?/;

my $qr = qr/^($qr1$qr2$qr3$qr4)$/;

while (<>)
{
    chomp;
    print "[$1] found in [$_]\n" if ($_ =~ $qr && length($1) > 0);
}

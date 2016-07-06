#!/usr/bin/env perl
#
# Produce a list of numbers squishing consecutive numbers into lo-hi ranges.
# Separate numbers and ranges with spaces.
# Assume incoming data is in sorted order (not necessarily unique).

use warnings;
use strict;

my $pad = " ";
my $out = "";
my $hi  = <> + 0;   # Read the first number
my $lo  = $hi;

while (<>)
{
    chomp;
    my $new = $_ + 0;
    next if $new == $hi;    # Ignore repeats
    die "Out of order (old $hi; new $new - $_)" if $new < $hi;
    if ($new != $hi+1)
    {
        $out .= "$pad$lo"     if ($lo == $hi);
        $out .= "$pad$lo-$hi" if ($lo != $hi);
        $lo = undef;
    }
    $hi = $new;
    $lo //= $new;
}

$out .= "$pad$lo"     if ($lo == $hi);
$out .= "$pad$lo-$hi" if ($lo != $hi);

print "$out\n";

#!/usr/bin/env perl
#
# Produce a list of numbers squishing consecutive numbers into lo-hi ranges
# Separate plain numbers with spaces
# Assume incoming data is in sorted order

use warnings;
use strict;

my $pad = " ";
my ($list) = "";

my $old = <> + 0;
my $lo = $old;
my $hi = $old;

while (<>)
{
    chomp;
    my $number = $_ + 0;
    next if $number == $old;    # Ignore repeats
    die "Out of order (old $old; new $number)" if $number < $old;
    if ($number != $old+1)
    {
        $list .= "$pad$lo"     if ($lo == $hi);
        $list .= "$pad$lo-$hi" if ($lo != $hi);
        $lo = undef;
    }
    $old = $number;
    $lo //= $old;
    $hi = $number;
}

if (defined $lo)
{
    $list .= "$pad$lo"     if ($lo == $hi);
    $list .= "$pad$lo-$hi" if ($lo != $hi);
}
else
{
    $list .= "$pad$old";
}

print "$list\n";

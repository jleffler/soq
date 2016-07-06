#!/usr/bin/env perl
#
# Produce a list of numbers squishing consecutive numbers into lo-hi ranges
# Separate plain numbers with spaces

use warnings;
use strict;

my %numbers;
my $min;
while (<>)
{
    chomp;
    $numbers{$_}++;
    $min //= $_;
    $min = $_ if ($_ < $min);
}

my $pad = " ";
my ($list, $old) = ("", $min-2);
my $lo;
my $hi;

foreach my $number (sort { $a <=> $b } keys %numbers)
{
    if ($number == $old+1)
    {
        $lo //= $old;
        $hi = $number;
    }
    elsif (defined $lo)
    {
        $list .= "$pad$lo-$hi";
        $lo = undef;
    }
    $old = $number;
}

if (defined $lo)
{
    $list .= "$pad$lo-$hi" if (defined $lo);
}
else
{
    $list .= "$pad $old";
}

print "$list\n";

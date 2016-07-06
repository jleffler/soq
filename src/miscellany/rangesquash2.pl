#!/usr/bin/env perl
#
# Produce a list of numbers squishing consecutive numbers into lo-hi ranges
# Separate plain numbers with spaces

use warnings;
use strict;

my %numbers;
while (<>)
{
    chomp;
    $numbers{$_}++;
}

my ($list, $old) = ("", 0);
foreach my $number (sort { $a <=> $b } keys %numbers)
{
    my $pad = ($number == $old+1) ? "-" : " ";
    $list =~ s/-$old$// if ($number == $old+1);
    $list .= "$pad$number";
    $old = $number;
}
print "$list\n";

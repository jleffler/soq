#!/usr/bin/env perl
use strict;
use warnings;

my $size = 9;
my @board;
my $nlines = 0;
while (my $line = <>)
{
    chomp $line;
    die "Incorrect board size" unless length($line) == 9;
    die "Invalid data in board" unless $line =~ /^[.XO]+$/;
    my @row;
    my $i = 0;
    foreach (split / */, $line)
    {
        $row[$i++] = $_;
    }
    $board[$nlines++] = \@row;
}

for (my $i = 0; $i < $size; $i++)
{
    for (my $j = 0; $j < $size; $j++)
    {
        print $board[$i][$j];
    }
    print "\n";
}

#!/usr/bin/env perl
use strict;
use warnings;

use constant debug => 0;

my $empty = '.';
my $size = 0;
my @board;

my $nlines = 0;
while (my $line = <>)
{
    chomp $line;
    if ($size == 0)
    {
        $size = length($line);
        die "Invalid board size ($size)"
            unless $size % 2 == 1 && $size >= 9 && $size <= 19;
    }
    die "Incorrect board size" unless length($line) == $size;
    die "Invalid data in board" unless $line =~ /^[.XO]+$/;
    my @row;
    my $i = 0;
    foreach (split / */, $line)
    {
        $row[$i++] = $_;
    }
    $board[$nlines++] = \@row;
}
die "Incorrect board size ($nlines instead of $size lines)"
    if $nlines != $size;

# Dump board
for (my $i = 0; $i < $size; $i++)
{
    for (my $j = 0; $j < $size; $j++)
    {
        print $board[$i][$j];
    }
    print "\n";
}

sub already_checked
{
    my($r, $c, @checked) = @_;
    foreach my $v (@checked)
    {
        return 1 if $v->[0] == $r && $v->[1] == $c;
    }
    return 0;
}

sub onboard
{
    my($r, $c) = @_;
    return 0 if $r < 0 || $r >= $size || $c < 0 || $c >= $size;
    return 1;
}

sub print_group
{
    my @checked = @_;
    my $pad = "      ";
    return if (scalar @checked <= 1);
    foreach my $v (@checked)
    {
        my($r, $c) = ($v->[0], $v->[1]);
        print "$pad($r,$c) = $board[$r][$c]";
        $pad = " --> "
    }
    print "\n";
}

my @posn = ( [ +1, 0 ], [ -1, 0 ], [ 0, +1 ], [ 0, -1 ] );

sub check_capture
{
    my($r0, $c0) = @_;
    my $captured = 1;
    my @checked;
    my @tocheck = ( [ $r0, $c0 ] );
    my $piece = $board[$r0][$c0];

    while (scalar @tocheck)
    {
        my $v = shift @tocheck;
        my $r = $v->[0];
        my $c = $v->[1];
        die "Incorrect piece ($board[$r][$c] instead of $piece)" if $board[$r][$c] ne $piece;
        foreach my $p (@posn)
        {
            my($r1, $c1) = ($p->[0], $p->[1]);
            $r1 += $r;
            $c1 += $c;
            next if !onboard($r1, $c1);
            print "Test($r1,$c1) = $board[$r1][$c1]\n" if debug;
            next if already_checked($r1, $c1, @checked);

            if ($board[$r1][$c1] eq $empty)
            {
                push @tocheck, [ $r1, $c1 ];
                print "Piece ($r0,$c0) = $piece is not captured (position ($r1,$c1) is empty)\n";
                print_group(@checked);
                return 0;
            }
            elsif ($board[$r1][$c1] eq $piece)
            {
                push @tocheck, [ $r1, $c1 ];
            }
        }
        push @checked, $v;
    }

    print "Piece ($r0,$c0) = $piece is captured\n";
    print_group(@checked);

    return 1;
}

for my $r (0..$size-1)
{
    print "\n";
    for my $c (0..$size-1)
    {
        if ($board[$r][$c] eq '.')
        {
            print "Empty position ($r, $c)\n";
        }
        else
        {
            check_capture($r, $c);
        }
    }
}


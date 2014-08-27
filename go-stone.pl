#!/usr/bin/env perl
use strict;
use warnings;

my $empty = '.';
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

my($r0, $c0) = (3, 3);
die "Empty positions are not dead" if $board[$r0][$c0] eq '.';

my @checked;
my @tocheck = ( [ $r0, $c0 ] );

my $piece = $board[$r0][$c0];

sub already_checked
{
    my($r, $c) = @_;
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
    my $pad = "    ";
    foreach my $v (@checked)
    {
        my($r, $c) = ($v->[0], $v->[1]);
        print "$pad($r,$c) = $board[$r][$c]\n";
        $pad = "--> "
    }
}

my @posn = ( [ +1, 0 ], [ -1, 0 ], [ 0, +1 ], [ 0, -1 ] );
my $captured = 1;

MAIN_LOOP:
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
        print "Test($r1,$c1) = $board[$r1][$c1]\n";
        next if !onboard($r1, $c1);
        next if already_checked($r1, $c1);

        if ($board[$r1][$c1] eq $empty)
        {
            print "Piece ($r0,$c0) = $piece is not captured\n";
            print_group(@checked);
            print "--> ($r1,$c1) = $board[$r1][$c1]\n";
            $captured = 0;
            last MAIN_LOOP;
        }
        elsif ($board[$r1][$c1] eq $piece)
        {
            push @tocheck, [ $r1, $c1 ];
        }
    }
    push @checked, $v;
}

if ($captured)
{
    print "Piece ($r0,$c0) = $piece is captured\n";
    print_group(@checked);
}

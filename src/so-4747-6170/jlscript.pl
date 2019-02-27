#!/usr/bin/env perl
use strict;
use warnings;

my %fh;

while (<>)
{
    my @fields = split;
    my $pfx = substr($fields[1], 0, 3);
    open $fh{$pfx}, '>>', "split_DB/${pfx}.part" or die
        unless defined $fh{$pfx};
    my $fh = $fh{$pfx};
    print $fh $_;
}

foreach my $h (keys %fh)
{
    close $fh{$h};
}

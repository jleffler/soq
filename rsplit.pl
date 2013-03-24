#!/usr/bin/env perl
use strict;
use warnings;

# Configuration items - could be set by argument handling
my $prefix = "rs.";
my $number = 1;
my $width  = 4;
my $rx = qr/^\+$/;
my $limit = 3;      # 50,000 in real case

sub next_file
{
    my $name = sprintf("%s%.*d", $prefix, $width, $number++);
    open my $fh, '>', $name or die "Failed to open $name for writing";
    print "$name\n";
    return $fh;
}

my $fh = next_file;
my $counter = 0;

while (<>)
{
    print $fh $_;
    $counter++ if (m/$rx/);
    if ($counter >= $limit)
    {
        close $fh;
        $fh = next_file;
        $counter = 0;
    }
}

close $fh;

#!/usr/bin/env perl
# http://stackoverflow.com/q/18812266 Merging multiple sorted files
use strict;
use warnings;

# Generate sorted, merge-worthy data

die "Usage: num-files lines-per-file [basename]" unless scalar(@ARGV) == 2 || scalar(@ARGV) == 3;
my $num_files = $ARGV[0];
my $num_lines = $ARGV[1];
die "Enter a number of files between 2 and 999" unless $num_files >= 2 && $num_files <= 999;
die "Enter a number of lines between 2 and 9,999,999" unless $num_files >= 2 && $num_files <= 9_999_999;

my $base = $ARGV[2] // "datafile";
my $digits = length($num_files . '');
my $format = "$base.%.${digits}d";

my $offset = 10 * $num_files;
   $offset = $num_lines / $num_files + 1 if ($offset >= $num_lines);

print "$offset\n";

foreach my $i (1..$num_files)
{
    my $file = sprintf $format, $i;
    print "$file\n";
    open my $fh, '>', $file or die "Failed to create $file";
    foreach my $n (1..$num_lines)
    {
        printf $fh "%.7d-%.3d\n", $n + $offset * $i, $i;
    }
    close $fh;
}

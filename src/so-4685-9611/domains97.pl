#!/usr/bin/env perl
#
# SO 4685-9611 (https://stackoverflow.com/q/46859611)

use strict;
use warnings;
use constant debug => 0;

my %domains2;       # 2-part domains keyed by 3-part domains
my %domains3;       # Count of occurrences of 3-part domains
my $min_count = 4;  # Minimum number of occurrences required

while (<>)
{
    chomp;
    next unless m/(\.[-\w]+\.([-\w]+\.[-\w]+))$/;
    print "OK: $_\n" if debug;
    $domains2{$1} = $2;
    $domains3{$1}++;
}

my %results;
foreach my $dom3 (keys %domains3)
{
    $results{$domains2{$dom3}}++ if $domains3{$dom3} > $min_count;
}

print join "\n", sort keys %results;


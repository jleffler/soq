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

print join "\n", sort keys
                 map  { $domains2{$_} => 1 }
                 grep { $domains3{$_} >= $min_count }
                 keys %domains3; 


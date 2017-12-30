#!/usr/bin/env perl
#
# SO 4685-9611 (https://stackoverflow.com/q/46859611)

use strict;
use warnings;

my %domains3;       # Count of occurrences of 3-part domains
my $min_count = 4;  # Minimum number of occurrences required

while (<>)
{
    chomp;
    $domains3{$1}++ if m/(\.[-\w]+\.[-\w]+\.[-\w]+)$/;
}

my %results = map  { ($_ =~ s/^\.[^.]+\.//r) => 1 }
              grep { $domains3{$_} >= $min_count }
              keys %domains3; 

print join("\n", sort keys %results), "\n";

#!/usr/bin/env perl
#
# SO 38427289
# More Perlish way to sort string with leading floating point number?

use strict;
use warnings;

my @unsorted = ( "8.02|a|b|c", "47.6|d|e|f", "108.1|g|h|i", "411.5|j|k|l", "8.1|m|n|o" );

# Original:
#sub by_firstField {
#sub compare {
#    my @tmpA = split ( /\|/, $a ) ;
#    my @tmpB = split ( /\|/, $b ) ;
#    if ($tmpA[0]> $tmpB[0]) { -1 } elsif ($tmpA[0] < $tmpB[0]) { 1 } else { 0 }
#}
#my @sorted   = sort compare @unsorted;

#sub compare
#{
#    my ($a0) = ($a =~ m/^([^|]+)/);
#    my ($b0) = ($b =~ m/^([^|]+)/);
#    #print "$a0 <=> $b0\n";
#    return $a0 <=> $b0;
#}
#
#sub compare { return ($a =~ m/^([^|]+)/)[0] <=> ($b =~ m/^([^|]+)/)[0] }
#my @sorted   = sort compare @unsorted;

my @sorted   = sort { ($a =~ m/^([^|]+)/)[0] <=> ($b =~ m/^([^|]+)/)[0] } @unsorted;

# 'Works' if "use warnings;" is not in effect!
#my @sorted   = sort { return $a <=> $b } @unsorted;

print "$_\n" foreach (@sorted);

# Accidentally posted broken code as an answer (testing failed, probably
# because I didn't write the edited file), so I deleted the answer and
# couldn't get back to it for a while, by which time there was a decent
# answer in place.  Answer is fixed but is left deleted.

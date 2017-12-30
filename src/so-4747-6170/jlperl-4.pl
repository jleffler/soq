#!/usr/bin/env perl
#
# SO 4747-6170
# Assuming sorted input

use strict;
use warnings;

my $old = "";
my $fh;
#my $counter = 0;

while (<>)
{
    #my @fields = split;
    #my $pfx = substr($fields[1], 0, 3);
    #m/\S+\s+(...)/;
    #my $pfx = $1;
    my $pfx = substr($_, 12, 3);
    if ($pfx ne $old)
    {
        close $fh if (defined $fh);
        open $fh, '>>', "split_DB/${pfx}.part" or die;
        #$counter++;
        $old = $pfx;
    }
    print $fh $_;
}
close $fh if (defined $fh);

#print "$counter\n";

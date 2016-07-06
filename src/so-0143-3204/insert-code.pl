#!/usr/bin/env perl
use strict;
use warnings;

while (<>)
{
    if (m/^### (\w+\.[ch])$/)
    {
        my $file = $1;
        print $_;
        print "\n";
        open my $fh, "<", "$file" or die "Failed to open $file";
        while (<$fh>)
        {
            print "    $_";
        }
        print "\n";
    }
    else
    {
        print $_;
    }
}

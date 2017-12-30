#!/usr/bin/env perl
use strict;
use warnings;

while (<>)
{
    if (m/^#### (\w[\w.-]*\.[ch]) ####$/)
    {
        my $file = $1;
        #print $_;
        #print "\n";
        open my $fh, "<", "$file" or die "Failed to open $file";
        while (<$fh>)
        {
            s/\s+$//;
            print (($_ eq "") ? "\n" : "    $_\n");
        }
        #print "\n";
    }
    else
    {
        print $_;
    }
}

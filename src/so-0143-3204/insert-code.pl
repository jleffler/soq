#!/usr/bin/env perl
use strict;
use warnings;
use Text::Tabs;

# Need to detab makefile
$tabstop = 4;

while (<>)
{
    if (m/^### (\w+\.[mch]k?)$/)
    {
        my $file = $1;
        print $_;
        print "\n";
        open my $fh, "<", "$file" or die "Failed to open $file";
        while (<$fh>)
        {
            chomp;
            s/\s+$//;
			$_ = expand($_);
            $_ = "    $_" if length($_) > 0;
            print "$_\n";
        }
        print "\n";
    }
    else
    {
        print $_;
    }
}

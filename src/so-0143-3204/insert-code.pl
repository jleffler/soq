#!/usr/bin/env perl
use strict;
use warnings;
use Text::Tabs;

# Need to detab makefile
$tabstop = 4;

while (<>)
{
    if (m/^### (\w+\.([mch]k?))$/)
    {
        my $file = $1;
        my $extn = $2;
        print $_;
        open my $fh, "<", "$file" or die "Failed to open $file";
        my $tag = "c";
        $tag = "make" if $extn eq "mk";
        print "\n```$tag\n";
        while (<$fh>)
        {
            chomp;
            s/\s+$//;
			$_ = expand($_);
            print "$_\n";
        }
        print "```\n\n";
    }
    else
    {
        print $_;
    }
}

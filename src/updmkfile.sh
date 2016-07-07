#!/bin/sh
#
# Update soq/src/makefile when new directories are added

mklist so-* |
perl -e '
my $done = 0;
while (<>)
{
    chomp;
    if (/^\tso-\d{4}-\d{4} \\$/ .. /^$/)
    {
        print <STDIN> if ($done++ == 0);
        print "\n" if ($_ eq "");
    }
    else
    {
        print "$_\n";
    }
}' -i.bak makefile

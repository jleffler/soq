#!/usr/bin/env perl
#
#   @(#)Derivation: fixin.pl,v 1.7 2015/09/21 23:48:17
#
#   FIXIN: from Programming Perl (1st Edition)
#
#   Usage: fixin [-s] [file ...]

use warnings;
use strict;

# Configuration
my $verbose = 1;            # Verbose by default

# Construct list of directories to search.
my @absdirs = reverse grep(m!^/!, split(/:/, $ENV{'PATH'}, 999));

# Process command line arguments
if ($ARGV[0] eq '-s')
{
    shift;
    $verbose = 0;
}
die "Usage: $0 [-s] [file ...]\n" unless @ARGV || !-t;

@ARGV = '-' unless @ARGV;

# Process each file.
FILE: foreach my $filename (@ARGV)
{
    open(IN, $filename) || ((warn "Can't process $filename: $!\n"), next);
    $_ = <IN>;
    unless (/^#!/)
    {
        warn "$filename does not contain #! as the first two characters\n";
        next FILE;
    }

    my $line = $_;
    chomp($line);
    $line =~ s/^#! *//;
    my ($cmd, $arg) = split(' ', $line, 2);
    $cmd =~ s!^.*/!!;

    # Now look (in reverse) for interpreter in absolute path
    my $found = '';
    if ($cmd eq "env")
    {
        $found = "/usr/bin/env";
    }
    else
    {
        foreach my $dir (@absdirs)
        {
            if (-x "$dir/$cmd")
            {
                warn "Ignoring $found\n" if $verbose && $found;
                $found = "$dir/$cmd";
            }
        }
    }

    # Figure out how to invoke interpreter on this machine
    if ($found)
    {
        warn "Changing $filename to $found\n" if $verbose;
        $_ = "#!$found";
        $_ .= ' ' . $arg if defined $arg;
        $_ .= "\n";
    }
    else
    {
        warn "Can't find $cmd in PATH, $filename unchanged\n" if $verbose;
        next FILE;
    }

    # Make new file if necessary
    if ($filename eq '-')
    {
        select(STDOUT);
    }
    else
    {
        rename($filename, "$filename.bak") ||
            ((warn "Can't modify $filename"), next FILE);
        open(OUT, ">$filename") ||
            die "Can't create new $filename: $!\n";
        my ($dev, $ino, $mode) = stat IN;
        $mode = 0755 unless $dev;
        chmod $mode, $filename;
        select(OUT);
    }

    # Print the new #! line (or the equivalent) and copy the rest of the file.
    print;
    while (<IN>)
    {
        print;
    }
    close IN;
    close OUT;
}

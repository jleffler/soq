#!/usr/bin/env perl
#
# SO 19747664: Shell: run four processes in parallel
# http://stackoverflow.com/questions/19747644
#
# Question code runs a simulation (instead of sleep), and can't predict
# how long a simulation will take (so sleep with random delay is a good
# model).  The object is to have N (4) processes running all the time,
# starting a new one as soon as one of the current N is complete.

use strict;
use warnings;
use constant MAX_KIDS => 4;

$| = 1;

my %pids;
my $kids = 0;   # Number of kids

for my $i (1..20)
{
    my $pid;
    if (($pid = fork()) == 0)
    {
        my $tm = int(rand(8)) + 2;
        print "$$: sleep $tm\n";
        # Using exec in a block on its own is the documented way to
        # avoid the warning:
        # Statement unlikely to be reached at filename.pl line NN.
        #   (Maybe you meant system() when you said exec()?)
        # Yes, I know the print and exit statements should never be
        # reached, but, dammit, sometimes things go wrong!
        { exec "sleep", $tm; }
        print STDERR "Oops: couldn't sleep $tm!\n";
        exit 1;
    }
    $pids{$pid} = 1;
    $kids++;
    my $time = time;
    print "PID: $pid; Kids: $kids; Time: $time\n";
    if ($kids >= MAX_KIDS)
    {
        my $kid = waitpid(-1, 0);
        print "Kid: $kid ($?)\n";
        if ($kid != -1)
        {
            delete $pids{$kid};
            $kids--;
        }
    }
}

while ((my $kid = waitpid(-1, 0)) > 0)
{
    my $time = time;
    print "Kid: $kid (Status: $?); Time: $time\n";
    delete $pids{$kid};
    $kids--;
}

# This should not do anything - and doesn't (any more!).
foreach my $pid (keys %pids)
{
    printf "Undead: $pid\n";
}


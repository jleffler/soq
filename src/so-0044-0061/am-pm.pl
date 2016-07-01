#!/usr/bin/env perl
#
# SO 440061 - using simpler hours conversion in time_12h_to_24h

use strict;
use warnings;

sub time_12h_to_24h
{
    my($t12) = @_;
    my($hh, $mm, $ampm) = $t12 =~ m/^(\d\d?):(\d\d?)\s*([AP]M?)/i;
    $hh = ($hh % 12) + (($ampm =~ m/AM?/i) ? 0 : 12);
    return sprintf("%.2d:%.2d", $hh, $mm);
}

sub time_24h_to_12h
{
    my($t24) = @_;
    my($hh, $mm) = $t24 =~ m/^(\d\d?):(\d\d?)/;
    my($ampm) = ($hh < 12) ? "am" : "pm";
    $hh %= 12;
    $hh += 12 if $hh == 0;
    return sprintf("%d:%.2d %s", $hh, $mm, $ampm);
}

while (<DATA>)
{
    chomp;
    my($input, $entry) = split / - /;
    my $time_24h = time_12h_to_24h($input);
    my $time_12h = time_24h_to_12h($time_24h);
    #print "$input - $time_24h : $time_12h - $entry\n";
    printf "%8s - %5s : %8s - %s\n", $input, $time_24h, $time_12h, $entry;
    warn "Mismatched 24h clock times $time_24h vs $entry\n" unless $time_24h eq $entry;
    warn "Mismatched 12h clock times $time_12h vs $input\n" unless $time_12h =~ m/^$input$/i;
}

__DATA__
12:00 am - 00:00
12:01 AM - 00:01
12:59 Am - 00:59
1:00 aM - 01:00
6:00 am - 06:00
10:37 am - 10:37
11:59 am - 11:59
12:00 pm - 12:00
12:59 pm - 12:59
1:00 pm - 13:00
6:15 PM - 18:15
10:45 Pm - 22:45
11:59 pM - 23:59

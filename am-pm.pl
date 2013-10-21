#!/usr/bin/env perl
use strict;
use warnings;

sub time_12h_to_24h
{
    my($t12) = @_;
    my($hh,$mm,$ampm) = $t12 =~ m/^(\d\d?):(\d\d?)\s*([AP]M?)/i;
    $hh = ($hh % 12) + (($ampm =~ m/AM?/i) ? 0 : 12);
    return sprintf("%.2d:%.2d", $hh, $mm);
}

sub time_24h_to_12h
{
    my($t24) = @_;
    my($hh,$mm) = $t24 =~ m/^(\d\d?):(\d\d?)/;
    my($ampm) = ($hh <12) ? "am" : "pm";
    $hh %= 12;
    $hh += 12 if $hh == 0;
    return sprintf("%d:%.2d %s", $hh, $mm, $ampm);
}

while (<>)
{
    chomp;
    my($input, $entry) = split / - /;
    my $time_24h = time_12h_to_24h($input);
    my $time_12h = time_24h_to_12h($time_24h);
    print "$input - $time_24h : $time_12h - $entry\n";
    #printf "%8s - %5s : %8s - %s\n", $input, $time_24h, $time_12h, $entry;
}

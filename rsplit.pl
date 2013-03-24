#!/usr/bin/env perl
use strict;
use warnings;
use Getopt::Std;
use Modern::Perl;

my %opts;

my $usestr = "Usage: $0 [-hqV][-p prefix][-w width][-s start] -e 'regex' -n repeat [file ...]";
my $hlpstr = <<'EOF';
  -h         print this help message and exit
  -p prefix  use given prefix for file names (default 'rs.')
  -q         do not print file names
  -w width   minimum number of digits in the file number (default 1)
  -s start   starting number for files (default 1)
  -e regex   pattern to split on (mandatory: no default)
  -n repeat  number of times to include regex in an output file (mandatory: no default)
  -V         print version information and exit
EOF

sub rcsmunger
{
    my($string) = @_;
    $string =~ s%\s*\@\(#\)%%go;
    $string =~ s%\$(Date:) (\d\d\d\d)/(\d\d)/(\d\d) (\d\d:\d\d:\d\d) \$%\$$1 $2-$3-$4 $5 \$%go;
    $string =~ s/\$([A-Z][a-z]+|RCSfile): ([^\$]+) \$/$2/go;
    return $string;
}

die "$usestr\n" unless (getopts('qp:w:s:e:n:hV', \%opts));
if (defined $opts{h})
{
    print "$usestr\n\n$hlpstr\n";
    exit 0;
}
if (defined $opts{V})
{
    print rcsmunger '@(#)RSPLIT Version $Revision$ ($Date$)';
    exit 0;
}
die "Must specify regex and repeat\n$usestr\n" unless (defined $opts{e} && defined $opts{n});

# Configuration items - could be set by argument handling
my $prefix = $opts{p} // "rs.";
my $number = $opts{s} // 1;
my $width  = $opts{w} // 1;
my $rx     = qr/$opts{e}/;
my $limit  = $opts{n};
my $quiet  = $opts{q} // 0;

sub next_file
{
    my $name = sprintf("%s%.*d", $prefix, $width, $number++);
    open my $fh, '>', $name or die "Failed to open $name for writing";
    print "$name\n" unless $quiet;
    return $fh;
}

my $fh = next_file;
my $counter = 0;

while (<>)
{
    print $fh $_;
    $counter++ if (m/$rx/);
    if ($counter >= $limit)
    {
        close $fh;
        $fh = next_file;
        $counter = 0;
    }
}

close $fh;

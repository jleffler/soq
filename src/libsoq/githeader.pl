#!/usr/bin/env perl
#
#   Convert JLSS RCS Heading to Git

use strict;
use warnings;

my $file;
my $date;
my $revn;

while (<>)
{
    if ($_ eq "/*\n") 
    {
        print;
        next;
    }
    elsif ($_ eq "*/\n")
    {
        printf "@(#)Derivation:     $file $revn $date\n";
        print;
        last;
    }
    elsif ($_ =~ m/(.*File:\s+)\$RCSfile:\s+([^,]+),v\s+\$/)
    {
        print "$1$2\n";
        $file = $2;
    }
    elsif ($_ =~ m/Last\s+[cC]hanged:\s+\$Date:\s+(\S+\s+\S+)\s+\$/)
    {
        $date = $1;
    }
    elsif ($_ =~ m/Version:\s+\$Revision:\s+(\S+)\s+\$/)
    {
        $revn = $1;
    }
    #elsif ($_ =~ m/Copyright:\s+\s+(\S+)\s+\$/)
    #{
    #
    #}
    elsif ($_ =~ m/Product:\s+:PRODUCT:/)
    {
        next;
    }
    else
    {
        print;
    }
}

print while (<>);

__END__

Input...

/*
@(#)File:           $RCSfile: kludge.c,v $
@(#)Version:        $Revision: 1.10 $
@(#)Last changed:   $Date: 2015/02/21 06:21:52 $
@(#)Purpose:        Library support for KLUDGE macro
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995,1997-98,2003,2005,2015
@(#)Product:        :PRODUCT:
*/

Output...

/*
@(#)File:           kludge.c
@(#)Purpose:        Library support for KLUDGE macro
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1995,1997-98,2003,2005,2015-16
@(#)Derivation:     kludge.c,v 1.10 2015/02/21 06:21:52 
*/
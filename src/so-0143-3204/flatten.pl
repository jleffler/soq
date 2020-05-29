#!/usr/bin/perl -p00
#
# Read file in paragraph mode.  Flatten running text - six or more
# alphanumeric words in a row somewhere in a paragraph

if (m/\w+(?: \w+){5,}/)
{
    if (m/^>\s/)
    {
        s/^>\s+//gm;
        $_ = "> $_";
    }
    s/\n/ /gms;
    s/\s+/ /g;
    $_ .= "\n\n";
}

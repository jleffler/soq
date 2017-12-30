#!/usr/bin/awk -f
#
# Convert data into table

BEGIN {
    t_tee="╦"
    b_tee="╩"
    l_tee="╠"
    r_tee="╣"
    blc="╚"
    tlc="╔"
    brc="╝"
    trc="╗"
    x_mid="╬"
    x_bar="═"
    x_pip="║"
}

function end_group()
{
    if (colno == 0) return      # Leading or consecutive blank lines
    if (grpno == 1) maxcol = colno
    else if (maxcol != colno)
    {
        print "Mismatched columns in group", grpno
        print "Got ", colno, "compared with", maxcol, "for 1st group"
    }
    colno = 0
    #print "End group", grpno
    maxgrp = grpno
}

/^[[:space:]]*$/ { end_group(); next }

{
    if (colno == 0) ++grpno
    ++colno
    #print "Data for group", grpno, "column", colno ":", $0;
    data[grpno,colno] = $0
    width = length($0)
    if (width > colwidth[colno]) colwidth[colno] = width
}

function print_line(c1, c2, c3, c4)
{
    line = ""
    mark = c1
    for (c = 1; c <= maxcol; c++)
    {
        for (i = 0; i < colwidth[c] + 3; i++)
        {
            line = line mark
            mark = c2
        }
        mark = c3
    }
    line = line c4
    print line
}

function print_data(c1, row)
{
    line = ""
    for (c = 1; c <= maxcol; c++)
    {
        line = line sprintf("%s %*s ", c1, colwidth[c], data[row,c])
    }
    line = line c1
    print line
}

END {
    #print "End group in END"
    end_group()
    #for (c = 1; c <= maxcol; c++)
    #    print "Width", c, "=", colwidth[c]
    #for (g = 1; g <= maxgrp; g++)
    #{
    #    for (c = 1; c <= maxcol; c++)
    #        print "Data[" g "," c "] =", data[g,c]
    #}
    print_line(tlc, x_bar, t_tee, trc)
    print_data(x_pip, 1)
    print_line(l_tee, x_bar, x_mid, r_tee)
    for (g = 2; g <= maxgrp; g++)
        print_data(x_pip, g)
    print_line(blc, x_bar, b_tee, brc)
}

# Stack Overflow Question 4747-6170

[SO 4747-6170](https://stackoverflow.com/q/47476170) &mdash;
Conditional splitting of a HUGE file

There are several other answers, and then there's this monstrosity.

This benchmarks the code in the other answers, and provides independent
shell and Perl scripts that turn out to be pretty effective, the Perl
script in particular.

This code uses an enormous amount of support code, some of it developed
for this answer, some of it modified for use with this answer.  The key points
though are the 7 scripts that process the data, and the resulting timing.

## Results

    ╔═════════════════╦════╦═════════╦═════════╦═════════╦═════════╗
    ║  Script Variant ║  N ║    Mean ║ Std Dev ║     Min ║     Max ║
    ╠═════════════════╬════╬═════════╬═════════╬═════════╬═════════╣
    ║   Lucas A Shell ║ 11 ║ 426.425 ║  16.076 ║ 408.044 ║ 456.926 ║
    ║ Chepner 1 Shell ║ 11 ║  39.582 ║   2.002 ║  37.404 ║  43.609 ║
    ║         Awk 256 ║ 11 ║  38.916 ║   2.925 ║  30.874 ║  41.737 ║
    ║ Chepner 2 Shell ║ 11 ║  16.033 ║   1.294 ║  14.685 ║  17.981 ║
    ║   Leffler Shell ║ 11 ║  15.683 ║   0.809 ║  14.375 ║  16.561 ║
    ║     Python 7000 ║ 11 ║   7.052 ║   0.344 ║   6.358 ║   7.771 ║
    ║        Awk 7000 ║ 11 ║   6.403 ║   0.384 ║   5.498 ║   6.891 ║
    ║       Perl 7000 ║ 11 ║   1.138 ║   0.037 ║   1.073 ║   1.204 ║
    ╚═════════════════╩════╩═════════╩═════════╩═════════╩═════════╝

## Processing scripts

### Lucas A Shell — aka `opscript.sh`

    cat "$@" |
    while read line
    do
        PREFIX=$(echo "$line" | cut -f2 | cut -c1-3)
        echo -e "$line" >> split_DB/$PREFIX.part
    done

### Chepner 1 Shell — aka `chepner-1.sh`

    cat "${@}" |
    while read -r line; do
        read -r _ col2 _ <<< "$line"
        prefix=${col2:0:3}
        # If the first column has a fixed width, you can forgo the previous two lines and use
        #   prefix=${line:12:3}
        printf '%s\n' "$line" >> split_DB/$prefix.part
    done

### Chepner 2 Shell - aka `chepner-2.sh`

    cat "${@}" |
    while read -r line; do
        prefix=${line: 12: 3}
        printf '%s\n' "$line" >> split_DB/$prefix.part
    done

### Leffler Shell — aka `jlscript.sh`

    sed 's/^[^ ]*  \(...\)/\1 &/' "$@" |
    while read key line
    do
        echo "$line" >> split_DB/$key.part
    done

### Python — aka `pyscript.py`

    import fileinput

    output_files = {}
    #with open(file) as fh:
    #    for line in fh:
    for line in fileinput.input():
        cols = line.strip().split()
        prefix = cols[1][0:3]
        # Cache the output file handles, so that each is opened only once.
        #outfh = output_files.setdefault(prefix, open("../split_DB/{}.part".format(prefix), "w"))
        outfh = output_files.setdefault(prefix, open("split_DB/{}.part".format(prefix), "w"))
        print(line, file=outfh)

    # Close all the output files
    for f in output_files.values():
        f.close()

### Awk — aka `awkscript.sh` (and `awkscript-256.sh`)

    exec ${AWK:-awk} '{s=substr($2,1,3); print >> "split_DB/" s ".part"}' "$@"

This wins for simplicity and has decent performance when used with GNU
Awk and enough file descriptors.
Note that `awkscript-256.sh` is simply a symbolic link to `awkscript.sh`
so that the different results can be separated automatically in the
scripts processing the results.

### Perl — aka `jlscript.pl`

    #!/usr/bin/env perl
    use strict;
    use warnings;

    my %fh;

    while (<>)
    {
        my @fields = split;
        my $pfx = substr($fields[1], 0, 3);
        open $fh{$pfx}, '>>', "split_DB/${pfx}.part" or die
            unless defined $fh{$pfx};
        my $fh = $fh{$pfx};
        print $fh $_;
    }

    foreach my $h (keys %fh)
    {
        close $fh{$h};
    }

You can easily argue that the explicit file handle closing is not
needed; that will be taken care of by Perl and/or the system.
The loop is present for symmetry with the Python script, to ensure
Perl is not getting an 'unfair advantage' somehow.

### Test Driver — aka `test-script.sh`

    #!/bin/bash
    #
    # Test suite for SO 4747-6170

    set_num_files()
    {
        nfiles=${1:-256}
        if [ "$(ulimit -n)" -ne "$nfiles" ]
        then if ulimit -S -n "$nfiles" 
             then : OK
             else echo "Failed to set num files to $nfiles" >&2
                  ulimit -HSa >&2
                  exit 1
             fi
         fi
    }

    test_python_7000()
    {
        set_num_files 7000
        timecmd -smr python3 pyscript.py "$@"
    }

    test_perl_7000()
    {
        set_num_files 7000
        timecmd -smr perl jlscript.pl "$@"
    }

    test_awk_7000()
    {
        set_num_files 7000
        AWK=/opt/gnu/bin/awk timecmd -smr sh awkscript.sh "$@"
    }

    test_awk_256()
    {
        set_num_files 256   # Default setting on macOS 10.13.1 High Sierra
        AWK=/opt/gnu/bin/awk timecmd -smr sh awkscript-256.sh "$@"
    }

    test_op_shell()
    {
        timecmd -smr sh opscript.sh "$@"
    }

    test_jl_shell()
    {
        timecmd -smr sh jlscript.sh "$@"
    }

    test_chepner_1_shell()
    {
        timecmd -smr bash chepner-1.sh "$@"
    }

    test_chepner_2_shell()
    {
        timecmd -smr bash chepner-2.sh "$@"
    }

    shopt -s nullglob

    # Setup - the test script reads 'file'.
    # The SOQ global .gitignore doesn't permit 'file' to be committed.
    rm -fr split_DB
    rm -f file
    ln -s generated.data file

    # Ensure cleanup
    trap 'rm -fr split_DB; exit 1' 0 1 2 3 13 15

    for function in \
        test_awk_256 \
        test_awk_7000 \
        test_chepner_1_shell \
        test_chepner_2_shell \
        test_jl_shell \
        test_op_shell \
        test_perl_7000 \
        test_python_7000
    do
        mkdir split_DB
        boxecho "${function#test_}"
        time $function file
        # Basic validation - the same information should appear for all scripts
        ls split_DB | wc -l
        wc split_DB/* | tail -n 2
        rm -fr split_DB
    done

    trap 0

The `timecmd` program is a C code program, and reports when a process is
started, and when it finishes, and how long it ran, and how it exited,
and so on.
It is simpler to manage than the `time` built-in, which can be
incredibly hard to handle.
The `boxecho` command is a simple script that adds a box of stars around
whatever needs to be echoed.

The various `bash.YYYYMMDD-HHMMSS` files were logged by a program `Trace`.

The test script was run using:

    time (ulimit -n 7000; TRACEDIR=. Trace bash test-script.sh)

This sets the number of file descriptors to 7000.
When I tried to increase the limit inside the shell script, Bash got
antsy and declined to increase the limit.
I'm not clear whether that's really a limit imposed by the o/s somehow
(but since I can increase the limit ordinarily, it isn't clear that it
is an o/s limitation).
This cost me some more grey hairs (they vanished — they're already
grey!).

I also found that I couldn't just run that command a few times in
background and go to bed; macOS didn't schedule the code nicely when I
wasn't at the machine, which was irksome.


## Support scripts

### `data.generator.sh`

    #!/bin/sh
    #
    # Generate random data for SO 4747-6170
    # Crude argument handling

    number=1000000
    if [ $# -ge 1 ]
    then number=$1; shift
    fi

    # Generated with seed: -S 0xE946DD5B
    random -n ${1:-1000000} "$@" \
        -T '%W%[0:9]d%W%03[0:999]d%3W%[0:9]d.%[0:9]d    %6[100000:999999]d  %[1000000:999999999]d' |
    sed 's/^[^.]*/&  &/'

The template `-T` generates a letter, a digit (number in the range
0..9), a letter, a number in the range 0..999 printed with leading
zeroes, 3 letters, another digit, a dot, and another digit; then some
spaces, a 6-digit number, some spaces, and a varying-length number with
7-9 digits.
The `sed` script replicates the material before the decimal point as
column 1.

The code for `random` is not currently available on GitHub; it is not
elegant enough yet.  It is about to undergo a rewrite.

### `data.summarizer.sh`

This script collects the execution times from the trace files
(`bash.YYYYMMDD-HHMMSS` files) and runs multiple scripts to generate the
pretty table at the top.
It uses custom program `samplestats` (which in turn uses `colnum`,
`gsplit`, and `pstats`), and the script `map-names.sh` to map script
names to the table entry names, and `tabulate.sh` (which uses
`tab-normal.sh` and `fmt-tabulate.awk`).
The dance with the second `sed` cleans up the output from `pstats` and
allows `tr` to convert the information to one record per line, then use
the '-g` (general numeric sort) option to (BSD or GNU) `sort` to sort
the mean time column in reverse order (slowest first), then reintroduces
newlines for the tabulate script.

    {
    echo "Script Variant"
    echo "N"
    echo "Mean"
    echo "Std Dev"
    echo "Min"
    echo "Max"
    echo

    grep -hE -e '  -  [0-9]+\.[0-9]+s  -  ' bash.* |
    sed -e 's/^.*  -  \([0-9]\)/\1/' -e 's/s  -  [a-z][a-z0-9]*//' -e 's/ file$//' |
    SAMPLE_STATS="-n -mean -sd -min -max -f %.3f" samplestats -k2 -v1 |
    sed -e 's/^[^#]/$@&/' \
        -e 's/^# [^=]*= \([0-9][0-9.]*\).*/\1/' \
        -e 's/$/ |/' |
    tr -d '\n' |
    tr '$' '\n' |
    sort -t'|' -k3gr,3 |
    sh map-names.sh |
    tr '@|' '\n\n'
    } |

    sh tabulate.sh


### `fmt-tabulate.awk`

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


### `map-names.sh`

    #!/bin/sh
    #
    # Map script names to descriptive names

    sed -e 's/chepner-1.sh/Chepner 1 Shell/' \
        -e 's/pyscript.py/Python 7000/' \
        -e 's/jlscript.sh/Leffler Shell/' \
        -e 's/jlscript.pl/Perl 7000/' \
        -e 's/awkscript-256.sh/Awk 256/' \
        -e 's/awkscript.sh/Awk 7000/' \
        -e 's/opscript.sh/Lucas A Shell/' \
        -e 's/chepner-2.sh/Chepner 2 Shell/' \
        "$@"

### `tab-normal.sh`

    #!/bin/sh
    #
    # Trim leading and trailimg spaces; normalize internal spaces; delete comments

    sed -e 's/^[[:space:]]\{1,\}//' \
        -e 's/[[:space:]]\{1,\}$//'  \
        -e 's/[[:space:]]\{1,\}/ /g'  \
        -e '/^#/d' \
        "$@"

### `tabulate.sh`

    #!/bin/sh
    #
    # Convert suitably laid out data into a boxed table
    #
    # The suitable layout is an arbitrary number of blocks of data, where
    # each block consists of one line per field.
    # The blocks should have a uniform number of entries.
    # There can be multiple blank lines, and fields can start or end with
    # stray white space, which will be removed, and with multiple spaces
    # within a field which will be normalized to single spaces.
    # Comment lines start with a hash `#` and are ignored.
    # This normalization is controlled by tab-normal.sh.
    #
    # The table is then layed out with Unicode box characters.  It should
    # present tidily in constant width font.  The first block of data is
    # treated as column headings and is separated from the other lines.
    # There is no maximum width for the table or fields.
    # Data is right justified; there's no way to left justify it yet.
    #
    # See tab-example.1 and tab-example.2 for illustrations.

    sh tab-normal.sh "$@" | awk -f fmt-tabulate.awk


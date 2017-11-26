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

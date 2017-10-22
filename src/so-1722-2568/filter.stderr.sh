#!/bin/bash
#
# Proof of concept for SO 17222568 Send Standard Error to Pipe.
# https://stackoverflow.com/questions/17222568

# Detailed auxilliary testing verifies that standard output is unchanged
# and standard error is filtered (but still sent to standard error).

set -x
rm -f out.[123]
./genouterr.sh 1>/dev/null
./genouterr.sh 2>/dev/null
( ./genouterr.sh 2>&1 1>&3 | grep '[0-9]0' >&2) 3>out.3 2>out.2 1>out.1
ls -l out.[123]
( ./genouterr.sh 2>&1 1>&3 | grep '[0-9]0' >&2) 3>&1

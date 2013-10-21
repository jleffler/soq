#!/bin/bash
set -x
rm -f out.[123]
./genouterr.sh 1>/dev/null
./genouterr.sh 2>/dev/null
( ./genouterr.sh 2>&1 1>&3 | grep '[0-9]0' >&2) 3>out.3 2>out.2 1>out.1
ls -l out.[123]
( ./genouterr.sh 2>&1 1>&3 | grep '[0-9]0' >&2) 3>&1

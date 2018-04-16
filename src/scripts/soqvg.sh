#!/bin/sh
#
# SOQ Valgrind - add suppressions from SOQ directory to command

: "${VALGRIND:=valgrind}"
: "${SOQDIR:=$HOME/soq}"
: "${SUPPRESSIONS:=suppressions-macos-10.13.4}"

exec ${VALGRIND} --suppressions="${SOQDIR}/etc/${SUPPRESSIONS}" "$@"

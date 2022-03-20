#!/bin/sh
#
# Create links between scripts in $HOME/soq/bin and $HOME/bin

SOQDIR="${HOME}/soq"
SOQBIN="${SOQDIR}/bin"
BINDIR="${HOME}/bin"

for file in "${SOQBIN}"/*
do
    if [ -f "${file}" ]
    then
        base=$(basename "${file}")
        if [ ! -f "${BINDIR}/${base}" ]
        then ln -s "${file}" "${BINDIR}"
        fi
    fi
done

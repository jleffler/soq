# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../etc/soq-head.mk

BASEDIR = ..

PROG01 = #mm11
PROG02 = #mm47
PROG03 = #mm61
PROG04 = mm89
PROG05 = mm97

PROGRAMS = ${PROG01} ${PROG02} ${PROG03} ${PROG04} ${PROG05}

all: ${PROGRAMS}

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} ${DEBRIS} *.dSYM

realclean:
	+cd src; ${MAKE} clean

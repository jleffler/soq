# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include etc/soq-head.mk

IFLAGS  = -I./inc
LDFLAG1 = -L./lib

default:
	@echo "You must specify a target to build"

MERGELIST.o = list.o mergelist.o
MERGELIST   = mergelist

PROGRAMS = \
	${MERGELIST} \
	keysort1 \
	keysort2 \
	merge \
	mergesort \
	mergesort2 \
	msort \
	piped-merge-sort \
	qs2 \
	qs3 \
	qs7 \
	radixsort \
	so-20271977 \
	sorttest

all: ${PROGRAMS}

${MERGELIST}: ${MERGELIST.o}
	${CC} -o $@ ${CFLAGS} ${MERGELIST.o} ${LDFLAGS} ${LDLIBS}

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out ${PROGRAMS}

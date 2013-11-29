CC     = gcc #/usr/bin/gcc
RM_FR  = rm -fr --
WFLAG1 = -Wall 
WFLAG2 = -Wextra
WFLAG3 = -Wmissing-prototypes 
WFLAG4 = -Wstrict-prototypes 
WFLAG5 = -Wold-style-definition
WFLAG6 =
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6} 
SFLAGS = -std=c11
GFLAGS = -g
OFLAGS = -O3
UFLAGS =
IFLAG1 = -I${HOME}/inc
IFLAGS =  ${IFLAG1}

IXXFLAGS = ${IFLAGS}
SXXFLAGS = -std=c++11
WXXFLAGS = -Wall -Wextra
UXXFLAGS =
OXXFLAGS = -O3
GXXFLAGS = -g

LDFLAG1 = -L${HOME}/lib/64
LDLIB1  = -ljl
LDFLAGS =  ${LDFLAG1}
LDLIBS  =  ${LDLIB1}

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${UFLAGS}
CXXFLAGS = ${OXXFLAGS} ${GXXFLAGS} ${IXXFLAGS} ${SXXFLAGS} ${WXXFLAGS} ${UXXFLAGS}

MERGELIST.o = list.o mergelist.o
MERGELIST   = mergelist

null:
	@echo "You must specify a target to build"

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

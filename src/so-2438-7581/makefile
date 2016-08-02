# @(#)$Id: makefile,v 1.3 2016/01/23 20:24:55 jleffler Exp $
#
# Makefile for demonstrating cross-library linking

CC     = gcc #/usr/bin/gcc
RM_FR  = rm -fr --
WFLAG1 = -Wall
WFLAG2 = -Wextra
WFLAG3 = -Wmissing-prototypes
WFLAG4 = -Wstrict-prototypes
WFLAG5 = -Wold-style-definition
WFLAG6 = -Werror
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6}
SFLAGS = -std=c11
GFLAGS = -g
OFLAGS = -O3
UFLAGS = # Set on command line
IFLAG1 = #-I${HOME}/inc
IFLAGS = ${IFLAG1}

SOEXT   = dylib
LDFLAG1 = -L.
LDLIB1  = -lrary1
LDLIB2  = -lrary2
LDFLAGS = ${LDFLAG1}
LDLIBS1 = ${LDLIB1} ${LDLIB2}
LDLIBS2 = ${LDLIB2} ${LDLIB1}

CFLAGS  = ${OFLAGS} ${GFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

LNKSHLIB = -shared

LIBRARY1 = library1.${SOEXT}
LIBRARY2 = library2.${SOEXT}

HEADERS = lib1.h lib2.h
LIB1.o  = lib1a.o lib1b.o
LIB2.o  = lib2a.o lib2b.o
TEST1.o = ${PROGRAM1}.o

PROGRAM1 = test1
PROGRAM2 = test2
PROGRAMS = ${PROGRAM1} ${PROGRAM2}

all: headers programs

test: all
	${PROGRAM1} | tee ${PROGRAM1}.out
	${PROGRAM2} | tee ${PROGRAM2}.out
	diff -u ${PROGRAM1}.out ${PROGRAM2}.out || true

headers: ${HEADERS}
programs: ${PROGRAMS}

${PROGRAM1}: ${TEST1.o} ${LIBRARY1} ${LIBRARY2}
	${CC} ${CFLAGS} -o $@ ${TEST1.o} ${LDFLAGS} ${LDLIBS1}

${PROGRAM2}: ${TEST1.o} ${LIBRARY1} ${LIBRARY2}
	${CC} ${CFLAGS} -o $@ ${TEST1.o} ${LDFLAGS} ${LDLIBS2}

${LIBRARY1}: ${LIB1.o} ${LIBRARY2}
	${CC} ${CFLAGS} ${LNKSHLIB} -o $@ ${LIB1.o} ${LDFLAGS} ${LDLIB2}

${LIBRARY2}: ${LIB2.o}
	${CC} ${CFLAGS} ${LNKSHLIB} -o $@ ${LIB2.o}

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out ${PROGRAM1}.out ${PROGRAM2}.out
	${RM_FR} ${PROGRAMS} ${LIBRARY1} ${LIBRARY2}

.DEFAULT:
	@echo "No commands specified for building $@"

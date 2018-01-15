# @(#)SO 2438-7581 - Cross-library Linking
#
# Makefile for demonstrating cross-library linking

include ../../etc/soq-head.mk

# Configured for Mac OS X - specify SOEXT=so or equivalent on other platforms
SOEXT   = dll		# Cygwin
SOEXT   = so        # Ubuntu (Linux)
SOEXT   = dylib     # macOS (Mac OS X)
OFLAGS  = -O3 -fPIC # Ubuntu (Linux)
OFLAGS  = -O3       # macOS (Mac OS X)
LDFLAG1 = -L.
LDLIB1  = -lrary1
LDLIB2  = -lrary2
LDFLAGS = ${LDFLAG1}
LDLIBS1 = ${LDLIB1} ${LDLIB2}
LDLIBS2 = ${LDLIB2} ${LDLIB1}

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

OUTFILES = ${LIBRARY1} ${LIBRARY2} ${PROGRAM1}.out ${PROGRAM2}.out

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

include ../../etc/soq-tail.mk

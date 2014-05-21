CC     = gcc
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

LDFLAG1 = #-L${HOME}/lib/64
LDLIB1  = #-ljl
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1}

CFLAGS  = ${OFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

PROG1   = prog1
PROG1.o = prog1.o file1.o file2.o

PROG2   = prog2
PROG2.o = prog2.o file10.o file11.o file12.o

PROG3   = prog3
PROG3.o = prog3.o file1a.o file2a.o

PROG4   = prog4
PROG4.o = prog4.o file1b.o file2b.o

PROGS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGS}

${PROG1}: ${PROG1.o}
	${CC} -o $@ ${CFLAGS} ${PROG1.o} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${PROG2.o}
	${CC} -o $@ ${CFLAGS} ${PROG2.o} ${LDFLAGS} ${LDLIBS}

${PROG3}: ${PROG3.o}
	${CC} -o $@ ${CFLAGS} ${PROG3.o} ${LDFLAGS} ${LDLIBS}

${PROG4}: ${PROG4.o}
	${CC} -o $@ ${CFLAGS} ${PROG4.o} ${LDFLAGS} ${LDLIBS}

clean:
	${RM_FR} *.o *.dSYM core a.out ${PROGS}

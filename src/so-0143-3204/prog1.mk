# Minimal makefile for prog1

PROGRAM = prog1
FILES.c = prog1.c file1.c file2.c
FILES.h = prog1.h file3.h
FILES.o = ${FILES.c:.c=.o}

CC      = gcc
SFLAGS  = -std=c11
GFLAGS  = -g
OFLAGS  = -O3
WFLAG1  = -Wall
WFLAG2  = -Wextra
WFLAG3  = -Werror
WFLAG4  = -Wstrict-prototypes
WFLAG5  = -Wmissing-prototypes
WFLAGS  = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5}
UFLAGS  = # Set on command line only

CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS}
LDFLAGS =
LDLIBS  =

all:	${PROGRAM}

${PROGRAM}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

# If it exists, prog1.dSYM is a directory on macOS
DEBRIS = a.out core *~ *.dSYM
RM_FR  = rm -fr

clean:
	${RM_FR} ${FILES.o} ${PROGRAM} ${DEBRIS}


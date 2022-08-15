# Makefile to demonstrate inconsistency between GCC 11.2.0 and Apple Clang.

CC = gcc

OFLAGS = -O3
GFLAGS = -g
SFLAGS = -std=c11
WFLAG1 = -Werror
WFLAG2 = -Wall
WFLAG3 = -Wextra
WFLAG4 = -pedantic
WFLAG5 = -pedantic-errors
UFLAGS = # Set on command line

WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5}
CFLAGS = ${OFLAGS} ${GFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

PROG1 = gcc23
FILE.c = ${PROG1}.c

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

${PROG1}:
	${CC} ${CFLAGS} ${FILE.c} -o $@

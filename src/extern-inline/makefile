# Makefile for illustrating inline functions

include ../../etc/soq-head.mk

RELINK = relink -s

WFLAGS = -Werror -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes

CC_C11 = gcc -std=c11 -pedantic
CC_G90 = gcc -std=gnu90 #-pedantic

DFLAGS_G90 = -DTEST_G90
DFLAGS_C11 = -DTEST_C11

UFLAGS_C11 = # Set on command line
UFLAGS_G90 = # Set on command line
UFLAGS     = ${UFLAGS_C11} ${UFLAGS_G90}

CFLAGS_C11 = ${WFLAGS} ${DFLAGS_C11} ${UFLAGS_C11}
CFLAGS_G90 = ${WFLAGS} ${DFLAGS_G90} ${UFLAGS_G90}

PROG_C11 = c11-program
PROG_G90 = g90-program

PROGRAM.c  = program.c

PROG_G90.c = g90-program.c
PROG_C11.c = c11-program.c

PROGRAMS = ${PROG_C11} ${PROG_G90}

G90_HDR = g90-config.h g90-extern.h g90-inline.h
G90_SRC = g90-program.c g90-define.c g90-user1.c g90-user2.c
G90_OBJ = ${G90_SRC:.c=.o}

C11_HDR = c11-config.h c11-extern.h c11-inline.h
C11_SRC = c11-program.c c11-define.c c11-user1.c c11-user2.c
C11_OBJ = ${C11_SRC:.c=.o}

all: ${PROGRAMS}

${PROG_G90}: ${G90_OBJ}
	${CC_G90} -o $@ ${CFLAGS_G90} ${G90_OBJ}

${PROG_C11}: ${C11_OBJ}
	${CC_C11} -o $@ ${CFLAGS_C11} ${C11_OBJ}

${G90_OBJ}: $$*.c
	${CC_G90} -c ${CFLAGS_G90} $*.c

${C11_OBJ}: $$*.c
	${CC_C11} -c ${CFLAGS_C11} $*.c

# Links
${PROG_G90.c}: ${PROGRAM.c}
	${RELINK} ${PROGRAM.c} ${PROG_G90.c}

${PROG_C11.c}: ${PROGRAM.c}
	${RELINK} ${PROGRAM.c} ${PROG_C11.c}

include ../../etc/soq-tail.mk

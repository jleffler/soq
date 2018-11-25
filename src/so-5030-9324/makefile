# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk

PROG1 = send29
PROG2 = recv29

FILE1.o = ${PROG1}.o dumpreq.o
FILE2.o = ${PROG2}.o dumpreq.o

PROGRAMS = ${PROG1} ${PROG2}

all:	${PROGRAMS}

${PROG1}: ${FILE1.o}
	${CC} -o $@ ${CFLAGS} ${FILE1.o} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${FILE2.o}
	${CC} -o $@ ${CFLAGS} ${FILE2.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

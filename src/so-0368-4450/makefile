# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk

PROG1 = openness1
PROG2 = openness2
PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}

FILES1.o = openness1.o reveal1.o
FILES2.o = openness2.o reveal2.o

${PROG1}: ${FILES1.o}
	${CC} -o $@ ${CFLAGS} ${FILES1.o} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${FILES2.o}
	${CC} -o $@ ${CFLAGS} ${FILES2.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

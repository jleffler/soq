# SO 48252451

include ../../etc/soq-head.mk

PROG1 = fifo-rdr-41
PROG2 = fifo-wrt-41

SHARED.c = fifo-tst-41.c
SHARED.h = ${SHARED.c:.c=.h}

PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}

FILES1.c = ${PROG1}.c ${SHARED.c}
FILES2.c = ${PROG2}.c ${SHARED.c}

FILES1.o = ${FILES1.c:.c=.o}
FILES2.o = ${FILES2.c:.c=.o}

${PROG1}: ${FILES1.o}
	${CC} -o $@ ${CFLAGS} ${FILES1.o} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${FILES2.o}
	${CC} -o $@ ${CFLAGS} ${FILES2.o} ${LDFLAGS} ${LDLIBS}

${FILES1.o}: ${SHARED.h}
${FILES2.o}: ${SHARED.h}

include ../../etc/soq-tail.mk

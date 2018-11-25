# SO 0618-7908

include ../../etc/soq-head.mk

PROG1    = dynstruct
PROGRAMS = ${PROG1}

FILES.c = dynstruct.c other.c
FILES.o = ${FILES.c:.c=.o}

all: ${PROGRAMS}

${PROG1}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

# SO 19016840

include ../../etc/soq-head.mk

PROG1 = mergelist

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

FILES.c = mergelist.c list.c
FILES.o = ${FILES.c:.c=.o}

${PROG1}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

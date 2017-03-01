# SO 29691159

include ../../etc/soq-head.mk

PROG1 = shm-master
PROG2 = run-shm-master

PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}

FILES.c = shm-master.c
FILES.o = ${FILES.c:.c=.o}

${PROG1}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

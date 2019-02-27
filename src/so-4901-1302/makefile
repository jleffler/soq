# SO 4901-1302

include ../../etc/soq-head.mk

FILES.c = cache_example.c cache_reader.c
FILES.o = ${FILES.c:.c=.o}
FILES.h = cache_reader.h

PROG1 = cache_example

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

${PROG1}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

${FILES.o}: ${FILES.h}

include ../../etc/soq-tail.mk

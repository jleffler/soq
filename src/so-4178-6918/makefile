# SO 41786918

include ../../etc/soq-head.mk

PROG1 = qs-hp37
PROG2 = qs37

OBJS0 = qs-main.o
OBJS1 = qs-hp37.o ${OBJS0}
OBJS2 = qs37.o    ${OBJS0}

PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}

${PROG1}: ${OBJS1}
	${CC} -o $@ ${CFLAGS} ${OBJS1} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${OBJS2}
	${CC} -o $@ ${CFLAGS} ${OBJS2} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

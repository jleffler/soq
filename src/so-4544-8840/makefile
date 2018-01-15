# SO 45448840

include ../../etc/soq-head.mk

PROG1 = pth17
PROG2 = pth31
PROG3 = pth47
PROG4 = pth79
PROG5 = pth97

LDLIB2 = -lpthread -lm

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5}

all: ${PROGRAMS}

pth17:
	${CC} -o $@ ${CFLAGS} $*.c ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

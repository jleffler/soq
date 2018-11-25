# SO 4829-1562

include ../../etc/soq-head.mk

PROG1 = sort2d-53
PROG2 = sort2d-37
PROG3 = sort2d-59
PROG4 = time.sort2d-31
PROG5 = sort2d-mk2-67
PROG6 = sort2d-mk2-73

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5} ${PROG6}

all: ${PROGRAMS}

FILES4.c = \
	time.sort2d-31.c \
	time.sort2d-71.c \
	time.sort2d-83.c \
	time.sort2d-89.c \
	time.sort2d-97.c \

FILES4.o = ${FILES4.c:.c=.o}

${PROG4}: ${FILES4.o}
	${CC} -o $@ ${CFLAGS} ${FILES4.o} ${LDFLAGS} ${LDLIBS}

${FILES4.o}: time.sort2d-31.h

include ../../etc/soq-tail.mk

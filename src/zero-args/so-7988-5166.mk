include ../../etc/soq-head.mk

LDLIBS=
LDFLAGS=
IFLAGS=

PROG1 = argv89
PROG2 = so-7988-5166

PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}
	${PROG1} ${PROG2}

include ../../etc/soq-tail.mk

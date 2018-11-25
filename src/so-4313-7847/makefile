# SO 4313-7847

include ../../etc/soq-head.mk

IFLAG1 = -I${INCDIR}
IFLAG2 = -I.
IFLAG3 = -I${HOME}/inc
IFLAGS = ${IFLAG1} ${IFLAG2} ${IFLAG3}

LDFLAG1 = -L${LIBDIR}
LDFLAG2 = -L${HOME}/lib/64
LDFLAGS = ${LDFLAG1} ${LDFLAG2}
LDLIB1  = -l${SOQBASE}
LDLIB2  = #-l${CS50BASE}
LDLIB3  = -ljl
LDLIBS  = ${LDLIB1} ${LDLIB2} ${LDLIB3}

PROG1 = pm23
PROG2 = pm43

PROGRAMS = ${PROG1} ${PROG2}

all: ${PROGRAMS}

PROG2.o = pm43.o polynomial.o

${PROG2}: ${PROG2.o}
	${CC} -o $@ ${CFLAGS} ${PROG2.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

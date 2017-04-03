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

PROG1 = pm43

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

PROG1.o = pm43.o polynomial.o

${PROG1}: ${PROG1.o}
	${CC} -o $@ ${CFLAGS} ${PROG1.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

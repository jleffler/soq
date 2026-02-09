# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk

PROG1 = argc37
PROG2 = argv89
PROG3 = so-7988-5166

SCRIPTS = maxargs

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS} ${SCRIPTS}
	${PROG2} ${PROG1}
	${PROG2} ${PROG3}

OUTFILES = ${SCRIPTS}

include ../../etc/soq-tail.mk

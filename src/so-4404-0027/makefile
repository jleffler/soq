# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk

PROG1 = sc19
PROG2 = sc61
PROG3 = sc59
PROG4 = spell-checker-ac
PROG5 = mknopunct

PROGS = ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5}

all: ${PROGS}

clean:
	${RM_F} ${PROGS}
	${RM_FR} ${DEBRIS} *.dSYM

realclean:

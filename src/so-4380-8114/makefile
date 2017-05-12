# Makefile for SO 4380-8114
#
# Sort/merge issues

include ../../etc/soq-head.mk

PROG1 = ms11
PROG2 = ms13
PROG3 = ms83
PROG4 = mulprocsPipemergesortwords0

PROGS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGS}

clean:
	${RM_F} ${PROGS}
	${RM_FR} ${DEBRIS} *.dSYM

realclean: clean

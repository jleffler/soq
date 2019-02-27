# Makefile for SO 4380-8114
#
# Sort/merge issues

include ../../etc/soq-head.mk

PROG1 = ms11
PROG2 = ms83
PROG3 = mulprocsPipemergesortwords0

LDLIB2 = -lpthread

PROGS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGS}

clean:
	${RM_F} ${PROGS}
	${RM_FR} ${DEBRIS} *.dSYM

realclean: clean

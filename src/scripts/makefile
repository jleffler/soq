# Makefile for miscellany directory

include ../../etc/soq-head.mk

CP      = cp
BINDIR  = ../../bin
CPFLAGS = -pf

PROG01 = posixcmd
PROG02 = posixfun
PROG03 = posixhdr
PROG04 = wso
PROG05 = so
PROG06 = sops
PROG07 = sow

PROGRAMS = \
	${PROG01} \
	${PROG02} \
	${PROG03} \
	${PROG04} \
	${PROG05} \
	${PROG06} \
	${PROG07} \

all: ${PROGRAMS}

install: all
	${CP} ${CPFLAGS} ${PROGRAMS} ${BINDIR}

include ../../etc/soq-tail.mk

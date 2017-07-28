# Makefile for miscellany directory

include ../../etc/soq-head.mk

CP      = cp
BINDIR  = ../../bin
CPFLAGS = -pf
LN      = ln
LNFLAGS = -s

PROG01 = posixcmd
PROG02 = posixfun
PROG03 = posixhdr
PROG04 = wso
PROG05 = so
PROG06 = sops
PROG07 = sow
PROG08 = rfn
PROG09 = ddpr
PROG10 = so-late
PROG11 = so-books

PROG08_LINK1 = ${PROG08}-c
PROG08_LINK2 = ${PROG08}-h
PROG08_LINK3 = ${PROG08}-sh
PROG08_LINK4 = ${PROG08}-cpp
PROG08_LINK5 = ${PROG08}-sql
PROG08_LINK6 = ${PROG08}-pl

PROG08_LINKS = \
	${PROG08_LINK1} \
	${PROG08_LINK2} \
	${PROG08_LINK3} \
	${PROG08_LINK4} \
	${PROG08_LINK5} \
	${PROG08_LINK6} \

PROGRAMS = \
	${PROG01} \
	${PROG02} \
	${PROG03} \
	${PROG04} \
	${PROG05} \
	${PROG06} \
	${PROG07} \
	${PROG08} \
	${PROG09} \
	${PROG10} \
	${PROG11} \

all: ${PROGRAMS} ${PROG08_LINKS}

install: all
	${CP} ${CPFLAGS} ${PROGRAMS} ${PROG08_LINKS} ${BINDIR}

${PROG08_LINKS}: ${PROG08}
	${LN} ${LNFLAGS} ${PROG08} $@

include ../../etc/soq-tail.mk

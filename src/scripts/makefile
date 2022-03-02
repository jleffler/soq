# Makefile for src/scripts directory
#
# Scripts get 'compiled' from the version in Git by removing the suffix,
# fixing the interpreter if necessary, and being made executable.

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
PROG12 = fixin
PROG13 = sscce
PROG14 = so-stderr
PROG15 = pipe-rot
PROG16 = soa
PROG17 = so-getchar
PROG18 = so-c-reserved
PROG19 = soqvg
PROG20 = so-quotes
PROG21 = so-reformat-c
PROG22 = so-esql
PROG23 = so-dotarrow
PROG24 = man7
PROG25 = so-primes
PROG26 = dienet
PROG27 = so-return-0
PROG28 = wso-es
PROG29 = wso-ja
PROG30 = wso-pt
PROG31 = wso-ru
PROG32 = so-swrecs
PROG33 = so-factorials
PROG34 = so-sqlcmd
PROG35 = so-premature
PROG36 = so-c-indent
PROG37 = so-c-reference-sites
PROG38 = so-sqltables
PROG39 = soac
PROG40 = sostats
PROG41 = tpop
PROG42 = openbsd
PROG43 = netbsd
PROG44 = freebsd

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
	${PROG12} \
	${PROG13} \
	${PROG14} \
	${PROG15} \
	${PROG16} \
	${PROG17} \
	${PROG18} \
	${PROG19} \
	${PROG20} \
	${PROG21} \
	${PROG22} \
	${PROG23} \
	${PROG24} \
	${PROG25} \
	${PROG26} \
	${PROG27} \
	${PROG28} \
	${PROG29} \
	${PROG30} \
	${PROG31} \
	${PROG32} \
	${PROG33} \
	${PROG34} \
	${PROG35} \
	${PROG36} \
	${PROG37} \
	${PROG38} \
	${PROG39} \
	${PROG40} \
	${PROG41} \
	${PROG42} \
	${PROG43} \
	${PROG44} \

all: ${PROGRAMS} ${PROG08_LINKS}

install: all
	${CP} ${CPFLAGS} ${PROGRAMS} ${PROG08_LINKS} ${BINDIR}

${PROG08_LINKS}: ${PROG08}
	${LN} ${LNFLAGS} ${PROG08} $@

include ../../etc/soq-tail.mk

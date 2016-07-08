# SO 15559979

include ../../etc/soq-head.mk

PROG1 = rsplit
OUTFILES = rs.0001 rs.0002 rs.0003 rs.0004
PROGRAMS = ${PROG1}
DATA = rsplit.data

all: ${PROGRAMS}

test: all
	${PERL} ${PROG1} ${DATA}

include ../../etc/soq-tail.mk

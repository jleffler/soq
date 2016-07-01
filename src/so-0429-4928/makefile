# SO 0429-4928

# Assumes etc/soq-head.mk is already included.
include ../../etc/soq.mk

PROG1    = send
PROG2    = recv
PROGRAMS = ${PROG1} ${PROG2}

all:	${PROGRAMS}

${PROG1}: ${LIBPATH}
${PROG2}: ${LIBPATH}

include ../../etc/soq-tail.mk

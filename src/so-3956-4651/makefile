# SO 39564651
#
# Size of code using varying numbers of arrow operators

include ../../etc/soq-head.mk

WFLAG4 =
WFLAG5 =
WFLAG6 =
WFLAG7 =
IFLAGS =
OFLAGS =

PROG1 = node1.o
PROG2 = node2.o
PROG3 = node3.o
PROG4 = node4.o

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGRAMS}

test:
	@for oflags in O0 O1 O2 O3 Os; \
	do ${CC} ${CFLAGS} -c "-$$oflags" node1.c node2.c node3.c node4.c; \
	   echo; echo "OFLAGS = -$$oflags"; size node1.o node2.o node3.o node4.o | d8; \
	done

include ../../etc/soq-tail.mk

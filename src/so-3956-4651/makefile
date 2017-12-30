# SO 39564651
#
# Size of code using varying numbers of arrow operators

include ../../etc/soq-head.mk

#WFLAG4 =
#WFLAG5 =
#WFLAG6 =
#WFLAG7 =

OFLAGS  =
IFLAGS  =
LDFLAGS =
LDLIBS  =

SRC_1 = node1.c
SRC_2 = node2.c
SRC_3 = node3.c
SRC_4 = node4.c
SOURCE = ${SRC_1} ${SRC_2} ${SRC_3} ${SRC_4}

PROG1 = node1.o
PROG2 = node2.o
PROG3 = node3.o
PROG4 = node4.o

SIZE = size
# D8 = pr -e8 -t -l1
D8   = d8

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGRAMS}
	${SIZE} ${PROGRAMS}
	@echo "For the maximum information, run: ${MAKE} test"

test:
	@for oflags in O0 O1 O2 O3 Os; \
	do \
		${CC} ${CFLAGS} -c "-$$oflags" ${SOURCE}; \
		echo; echo "OFLAGS = -$$oflags"; ${SIZE} ${PROGRAMS} | ${D8}; \
	done

include ../../etc/soq-tail.mk

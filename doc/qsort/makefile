# SO 11027679

include ../../etc/soq-head.mk

PROG00 = qs47

PROG01 = qs-01-int
PROG02 = qs-02-str
PROG03 = qs-03-2da
PROG04 = qs-04-asp
PROG05 = qs-05-date
PROG06 = qs-06-bad
PROG07 = qs-07-int
PROG08 = ls73
PROG09 = ls79
PROG10 = oddascevendesc
PROG11 = qs79
PROG12 = sr19
PROG13 = qs8m

COMPARATOR_SOURCE = altcmp1.c

PROGRAMS = \
	${PROG00} \
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

all: ${PROGRAMS}

${PROG07}:
	${CC} -o $@ ${CFLAGS} ${PROG07}.c -DCOMPARATOR_SOURCE='"${COMPARATOR_SOURCE}"' ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

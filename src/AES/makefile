include ../../etc/soq-head.mk

VFLAG1 = -DTEST
VFLAG2 = -DFIXED_TABLES

OUTFILES = ${PROG2}.c ${FILES.c}

PROGRAMS = ${PROG1} ${PROG2}

PROG1 = aes
PROG2 = aes-fixed

FILE1.o = aes-obj.o
FILE2.o = aes-fixed-obj.o
FILES.o = ${FILE1.o} ${FILE2.o}

FILE1.c = ${FILE1.o:.o=.c}
FILE2.c = ${FILE2.o:.o=.c}
FILES.c = ${FILES.o:.o=.c}

all: ${PROGRAMS} ${FILES.o}

${PROG2}.c: ${PROG1}.c
	${LN} -s ${PROG1}.c ${PROG2}.c

${FILE1.c}: ${PROG1}.c
	${LN} -s ${PROG1}.c ${FILE1.c}

${FILE2.c}: ${PROG2}.c
	${LN} -s ${PROG2}.c ${FILE2.c}

${PROG1}: ${PROG1}.c
	${CC} -o $@ ${CFLAGS} ${VFLAG1} $@.c ${LDFLAGS} ${LDLIBS}

${PROG2}: ${PROG2}.c
	${CC} -o $@ ${CFLAGS} ${VFLAG1} ${VFLAG2} $@.c ${LDFLAGS} ${LDLIBS}

${FILE1.o}: ${FILE1.c}
	${CC} -c ${CFLAGS} $*.c

${FILE2.o}: ${FILE2.c}
	${CC} -c ${CFLAGS} ${VFLAG2} $*.c

test: all
	time ${PROG1}
	time ${PROG2}

include ../../etc/soq-tail.mk

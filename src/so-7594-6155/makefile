# SO 7594-6155
#
# Random Password Generator

include ../../etc/soq-head.mk

PROG1 = grpwd43

PROGRAMS = ${PROG1}

# You shoudl not normally need crc.c
FILES1.c = grpwd43.c prng48.c randseed.c
FILES1.o = ${FILES1.c:.c=.o}

all: ${PROGRAMS}

${PROG1}: ${FILES1.o}
	${CC} -o $@ ${CFLAGS} ${FILES1.o} ${LDFLAGS} ${LDLIBS}

grpwd43.o: CFLAGS += -DTEST

include ../../etc/soq-tail.mk

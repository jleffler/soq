# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk


PROG1 = list

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

SOURCE = main.c genlist.c
OBJECT = $(SOURCE:.c=.o)

${PROG1}: ${OBJECT}
	${CC} -o $@ ${CFLAGS} ${OBJECT} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

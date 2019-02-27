# SO 5008-7213

include ../../etc/soq-head.mk

LDFLAGS =
LDLIBS  =
IFLAGS  =

YFLAGS  = -d

FILES.o = shellg.o shell.o

PROGRAM = shell

all: ${PROGRAM}

${PROGRAM}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

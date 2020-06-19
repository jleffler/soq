# SO 0067-5039

include ../../etc/soq-head.mk

PROG1 = mkpath

FILES.c = \
	emalloc.c \
	estrdup.c \
	mkpath.c \
	stderr.c \

FILES.o = ${FILES.c:.c=.o}

LIBBASE = mkpath
LIBNAME = lib${LIBBASE}.a

LDFLAGS = -L.
LDLIBS  = -l${LIBBASE}

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

${PROG1}: ${LIBNAME}
	${CC} -o $@ ${CFLAGS} -DTEST ${PROG1}.c ${LDFLAGS} ${LDLIBS}

${LIBNAME}: ${FILES.o}
	${AR} ${ARFLAGS} ${LIBNAME} ${FILES.o}

include ../../etc/soq-tail.mk

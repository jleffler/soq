# Makefile for SOQ library

include ../../etc/soq.mk

CP      = cp
CPFLAGS = -fp

FILES.c = \
	gcd.c \
	stderr.c

FILES.o = ${FILES.c:.c=.o}
FILES.h = ${FILES.c:.c=.h}

all: ${LIBNAME} ${FILES.h}

${LIBNAME}:	${FILES.o}
	${AR} ${ARFLAGS} ${LIBNAME} ${FILES.o}

install: ${LIBNAME} ${FILES.h}
	${CP} ${CPFLAGS} ${LIBNAME} ${LIBDIR}
	${CP} ${CPFLAGS} ${FILES.h} ${HDRDIR}

clean:
	${RM_F} ${DEBRIS} ${FILES.o}

realclean: clean
	${RM_F} ${LIBNAME}

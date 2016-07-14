# Makefile for SOQ library

include ../../etc/soq-head.mk

# Temporarily, the best way to build test programs is
# rmk TFLAGS=-DTEST program ...
#
#TFLAGS  = -DTEST
CP      = cp
CPFLAGS = -fp

FILES.c = \
	chkstrint.c \
	debug.c \
	emalloc.c \
	filter.c \
	gcd.c \
	kludge.c \
	range.c \
	stderr.c \
	timer.c \

AUXFILES.c = \
	errhelp.c \
	filterio.c \
	isqrt32.c \
	isqrt64.c \
	range2.c \
	range3.c \
	strtoi.c \
	strtosize.c \

AUXFILES.h = \
	isqrt.h \
	jlss.h \
	posixver.h \
	wraphead.h

FILES.o = ${FILES.c:.c=.o} ${AUXFILES.c:.c=.o}
FILES.h = ${FILES.c:.c=.h} ${AUXFILES.h}

all: ${LIBNAME} ${FILES.h}

${LIBNAME}:	${FILES.o}
	${AR} ${ARFLAGS} ${LIBNAME} ${FILES.o}

install: ${LIBNAME} ${FILES.h}
	${CP} ${CPFLAGS} ${LIBNAME} ${LIBDIR}
	${CP} ${CPFLAGS} ${FILES.h} ${HDRDIR}

PROGRAMS = ${FILES.c:.c=} ${AUXFILES.c:.c=}

#${PROGRAMS}: CFLAGS += -DTEST

include ../../etc/soq-tail.mk

# Makefile for SOQ library

include ../../etc/soq-head.mk

# Temporarily, the best way to build test programs is
# rmk TFLAGS=-DTEST program ...
#
#TFLAGS  = -DTEST
CP      = cp
CPFLAGS = -fp
CFLAGS += -DHAVE_NANOSLEEP

# FILES.c lists source files for which there is a matching header
FILES.c = \
	aomcopy.c \
	aommngd.c \
	aomptr.c \
	aoscopy.c \
	aosptr.c \
	chkstrint.c \
	debug.c \
	emalloc.c \
	escape.c \
	filter.c \
	gcd.c \
	imageprt.c \
	kludge.c \
	mddebug.c \
	memdup.c \
	microsleep.c \
	range.c \
	stderr.c \
	stderrloc.c \
	timer.c \
	timespec_io.c \
	timespec_math.c \
	timeval_io.c \
	timeval_math.c \

# AUXFILES.c lists source files for which there isn't a matching header
AUXFILES.c = \
	errhelp.c \
	estrdup.c \
	filterio.c \
	isqrt32.c \
	isqrt64.c \
	range2.c \
	range3.c \
	strtoi.c \
	strtosize.c \
	strupper.c \

# AUXFILES.h list headers for which there isn't a matching source file
AUXFILES.h = \
	aomcore.h \
	isqrt.h \
	jlss.h \
	matmaxfldwid.h \
	noreturn.h \
	posixver.h \
	reldiff.h \
	vecmaxfldwid.h \
	wraphead.h \

FILES.o = ${FILES.c:.c=.o} ${AUXFILES.c:.c=.o}
FILES.h = ${FILES.c:.c=.h} ${AUXFILES.h}

all: ${LIBNAME} ${FILES.h}

${LIBNAME}:	${FILES.o}
	${AR} ${ARFLAGS} ${LIBNAME} ${FILES.o}

install: ${LIBNAME} ${FILES.h}
	${CP} ${CPFLAGS} ${LIBNAME} ${LIBDIR}
	${CP} ${CPFLAGS} ${FILES.h} ${INCDIR}

PROGRAMS = ${FILES.c:.c=} ${AUXFILES.c:.c=}

#${PROGRAMS}: CFLAGS += -DTEST

include ../../etc/soq-tail.mk

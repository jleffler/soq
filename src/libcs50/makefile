# Makefile for SOQ library

include ../../etc/soq-head.mk

CP      = cp
CPFLAGS = -fp

FILES.c = cs50.c

FILES.o = ${FILES.c:.c=.o}
FILES.h = ${FILES.c:.c=.h}

all: ${CS50NAME} ${FILES.h}

${CS50NAME}:	${FILES.o}
	${AR} ${ARFLAGS} ${CS50NAME} ${FILES.o}

install: ${CS50NAME} ${FILES.h}
	${CP} ${CPFLAGS} ${CS50NAME} ${LIBDIR}
	${CP} ${CPFLAGS} ${FILES.h}  ${HDRDIR}

clean:
	${RM_F} ${DEBRIS} ${FILES.o}

realclean: clean
	${RM_F} ${CS50NAME}

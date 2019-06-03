# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../etc/soq-head.mk

BASEDIR = ..

IFLAG2  = -I${HOME}/inc
LDFLAG2 = -L${HOME}/lib/64
LDLIB2  = -ljl
LDLIB3  = -lrt
LDLIBS  = ${LDLIB1} ${LDLIB2} ${LDLIB3}

PROG1    = chunker79
PROGRAMS = ${PROG1}

all: ${PROGRAMS}

include ../etc/soq-tail.mk

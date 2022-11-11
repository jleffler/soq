# SO 0612-7503

include ../../etc/soq-head.mk

# Temporary measure - needed for fyshuffle.h and libjl.a
LDFLAGS = -L${HOME}/lib/64
LDLIBS  = -ljl
IFLAGS  = -I${HOME}/inc
TFLAGS  = -DTEST

PROG1 = genshuffle
PROG2 = check-conservation
PROG3 = compare-arrays
PROG4 = antonin-gavrel-shuffle

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

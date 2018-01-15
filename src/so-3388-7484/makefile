# SO 33887484

include ../../etc/soq-head.mk

# This works on the development machine, but not yet via GitHub
LDLIB2 = -ljl -lm
IFLAGS = -I${INCDIR} -I${HOME}/inc
LDFLAGS = ${LDFLAG1} -L${HOME}/lib/64

# At the moment, ratcalc includes so.33887484.c directly.
# Clearly, this is not the long-term way; the code in so.33887484.c would be in a library.
# Unless you believe in SQLite Amalgamations as the way to go for everything.
PROG1 = ratcalc
PROG2 = rational
#PROG3 = so.33887484

SOURCE = so.3388-7484.txt
ANSWER = so.3388-7484.md
INSERT = insert-code.pl
PERL   = perl

PROGRAMS = ${PROG1} ${PROG2} #${PROG3}

all: ${PROGRAMS} ${ANSWER}

${PROG1}: so.33887484.c so.33887484.h

${ANSWER}: ${SOURCE} ${INSERT} so.33887484.c so.33887484.h ratcalc.c
	${PERL} ${INSERT} ${SOURCE} > ${ANSWER}

include ../../etc/soq-tail.mk

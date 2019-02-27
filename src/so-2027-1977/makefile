# SO 2027-1977

include ../../etc/soq-head.mk

# PROG1 doesn't have a main() function!
PROG1 = #so-20271977-core
PROG2 = so-20271977

PROGRAMS = ${PROG1} ${PROG2}

FILES.c = so-20271977-core.c so-20271977.c
FILES.o = ${FILES.c:.c=.o}

all: ${FILES.o} ${PROGRAMS}

include ../../etc/soq-tail.mk

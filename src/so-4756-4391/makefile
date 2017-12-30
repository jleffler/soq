# SO 47564391

include ../../etc/soq-head.mk

PCRE_BASE = /opt/gnu
IFLAG2    = -I${PCRE_BASE}/include
LDFLAG2   = -L${PCRE_BASE}/lib
LDLIB2    = -lpcre

PROG1 = rx-posix-59
PROG2 = rx-pcre-73
PROG3 = pcre

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

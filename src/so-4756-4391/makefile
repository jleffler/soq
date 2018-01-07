# SO 47564391
#
# It is clunky linking both -lpcre and -lpcre2-8 into an
# executable, but it is fiddly to do otherwise.
# Eventually, this should work with RMK too.
#   ${PROG2}: LDLIB2 = -lpcre
#   ${PROG3}: LDLIB2 = -lpcre2-8

include ../../etc/soq-head.mk

PCRE_BASE = /opt/gnu
IFLAG2    = -I${PCRE_BASE}/include
LDFLAG2   = -L${PCRE_BASE}/lib
LDLIB2    = -lpcre -lpcre2-8

PROG1 = rx-posix-59
PROG2 = rx-pcre1-73
PROG3 = rx-pcre2-83

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

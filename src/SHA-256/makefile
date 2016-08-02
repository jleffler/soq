# Makefile for reference SHA-256 implementation from IETF RFC 4634

CC     = gcc
RM_FR  = rm -fr --
WFLAG1 = -Wall
WFLAG2 = -Wextra
WFLAG3 = -Wmissing-prototypes
WFLAG4 = -Wstrict-prototypes
WFLAG5 = -Wold-style-definition
WFLAG6 = -Werror
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6}
SFLAGS = -std=c11
GFLAGS = -g
OFLAGS = -O3
UFLAGS = # Set on command line
IFLAGS =

LDFLAGS =
LDLIBS  =

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${UFLAGS}

FILES.h = \
	sha-private.h \
	sha.h \

FILES.c = \
	hmac.c \
	sha1.c \
	sha224-256.c \
	sha384-512.c \
	shatest-ietf.c \
	usha.c \

FILES.o = ${FILES.c:.c=.o}

PROG1 = shatest-ietf

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

${PROG1}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_FR} ${PROGRAMS}

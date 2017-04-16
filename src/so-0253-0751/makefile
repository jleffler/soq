# Makefile for test code related to SO 0253-0751
#
# Speed of string searching (KMP vs BM).

DFLAGS = -DPARANOID
GFLAGS = -g
IFLAGS = -I../libsoq
OFLAGS = -O3
SFLAGS = -std=c11
UFLAGS = # Set on command line only
WFLAGS = -Wmissing-prototypes -Wstrict-prototypes -pedantic -Wall -Wextra

CFLAGS  = ${DFLAGS} ${GFLAGS} ${IFLAGS} ${OFLAGS} ${SFLAGS} ${UFLAGS} ${WFLAGS}

SOURCES_0 = ptest.c kmp.c bm.c timer.c stderr.c kludge.c #dbmalloc.c
OBJECTS_0 = ${SOURCES_0:.c=.o}
SOURCES_1 = ptest.c kmp.c bm.c timer.c stderr.c kludge.c dbmalloc.c
OBJECTS_1 = ${SOURCES_1:.c=.o}
SOURCES_2 = ptest2.c kmp.c bm.c timer.c stderr.c kludge.c dbmalloc.c
OBJECTS_2 = ${SOURCES_2:.c=.o}

all:	ptest ptest2

ptest0:	${OBJECTS_0}
	${CC} ${CFLAGS} -o $@ ${OBJECTS_0}

ptest:	${OBJECTS_1}
	${CC} ${CFLAGS} -o $@ ${OBJECTS_1}

ptest2:	${OBJECTS_2}
	${CC} ${CFLAGS} -o $@ ${OBJECTS_2}

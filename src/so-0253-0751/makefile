SOURCES_1 = ptest.c kmp.c bm.c timer.c stderr.c dbmalloc.c
OBJECTS_1 = ${SOURCES_1:.c=.o}
SOURCES_2 = ptest2.c kmp.c bm.c timer.c stderr.c dbmalloc.c
OBJECTS_2 = ${SOURCES_2:.c=.o}
CFLAGS  = -g -std=c11 -Wmissing-prototypes -Wstrict-prototypes -pedantic -Wall -Wextra -DPARANOID

all:	ptest ptest2

ptest:	${OBJECTS_1}
	${CC} ${CFLAGS} -o $@ ${OBJECTS_1}

ptest2:	${OBJECTS_2}
	${CC} ${CFLAGS} -o $@ ${OBJECTS_2}

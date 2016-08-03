# Makefile for SO 0143-3204 (How to use extern to share variables in C)

# NB: The mkdep program used may not have exactly the same interface as
#     the 'standard' versions of the program.

PERL   = perl
UNIQ   = uniq
MKDEP  = mkdep
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
IFLAGS = # -I/where/ever

LDFLAGS = # -L/some/directory
LDLIBS  = # -lsome

CFLAGS  = ${OFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

PROG1   = prog1
PROG1.o = prog1.o file1.o file2.o

PROG2   = prog2
PROG2.o = prog2.o file10.o file11.o file12.o

PROG3   = prog3
PROG3.o = prog3.o file1a.o file2a.o

PROG4   = prog4
PROG4.o = prog4.o file1b.o file2b.o

PROG5   = prog5
PROG5.o = prog5.o file3c.o file4c.o

PROG6   = prog6
PROG6.o = prog5.o file5c.o file4c.o

PROG7   = prog7
PROG7.o = prog5.o file6c.o file4c.o

PROG8   = prog8
PROG8.o = prog8.o file7c.o file9c.o

PROG9   = prog9
PROG9.o = prog8.o file8c.o file9c.o

PROGS = ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5} ${PROG6} ${PROG7} ${PROG8} ${PROG9}

INSERT_CODE = insert-code.pl

SOURCE = extern-definitions
ANSWER = extern-definitions.txt

FILES.c = \
	file1.c \
	file10.c \
	file11.c \
	file12.c \
	file1a.c \
	file1b.c \
	file2.c \
	file2a.c \
	file2b.c \
	file3c.c \
	file4c.c \
	file5c.c \
	file6c.c \
	file7c.c \
	file8c.c \
	file9c.c

PROGS.c = \
	prog1.c \
	prog2.c \
	prog3.c \
	prog4.c \
	prog5.c \
	prog8.c

FILES.h = \
	external.h \
	externdef.h \
	file1c.h \
	file2c.h \
	file2d.h \
	file3.h \
	file3a.h \
	file3b.h \
	file8c.h \
	prog1.h \
	prog2.h \
	prog3.h \
	prog4.h

BOGUS.h = \
	broken_header.h \
	faulty_header.h \
	seldom_correct.h

MAKEFILE = makefile
TAR      = tar
TARFLAGS = -czf
TARFILE  = so-1433204.tar.gz
TAR_LIST = \
	${ANSWER} \
	${BOGUS.h} \
	${CHECK} \
	${FILES.c} \
	${FILES.h} \
	${INSERT_CODE} \
	${MAKEFILE} \
	${PROGS.c} \
	${SOURCE}

CHECK = check-references.sh

all: ${CHECK} check ${PROGS} ${ANSWER} ${TARFILE}

check:
	${SHELL} ${CHECK} ${SOURCE} ${FILES.c} ${FILES.h} ${PROGS.c} ${BOGUS.h}

${PROG1}: ${PROG1.o}
	${CC} -o $@ ${CFLAGS} ${PROG1.o} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${PROG2.o}
	${CC} -o $@ ${CFLAGS} ${PROG2.o} ${LDFLAGS} ${LDLIBS}

${PROG3}: ${PROG3.o}
	${CC} -o $@ ${CFLAGS} ${PROG3.o} ${LDFLAGS} ${LDLIBS}

${PROG4}: ${PROG4.o}
	${CC} -o $@ ${CFLAGS} ${PROG4.o} ${LDFLAGS} ${LDLIBS}

${PROG5}: ${PROG5.o}
	${CC} -o $@ ${CFLAGS} ${PROG5.o} ${LDFLAGS} ${LDLIBS}

${PROG6}: ${PROG6.o}
	${CC} -o $@ ${CFLAGS} ${PROG6.o} ${LDFLAGS} ${LDLIBS}

${PROG7}: ${PROG7.o}
	${CC} -o $@ ${CFLAGS} ${PROG7.o} ${LDFLAGS} ${LDLIBS}

${PROG8}: ${PROG8.o}
	${CC} -o $@ ${CFLAGS} ${PROG8.o} ${LDFLAGS} ${LDLIBS}

${PROG9}: ${PROG9.o}
	${CC} -o $@ ${CFLAGS} ${PROG9.o} ${LDFLAGS} ${LDLIBS}

clean:
	${RM_FR} *.o *.dSYM core a.out ${PROGS} ${ANSWER} ${TARFILE}

${ANSWER}: ${SOURCE} ${FILES.c} ${PROGS.c} ${FILES.h}
	${PERL} ${INSERT_CODE} ${SOURCE} | ${UNIQ} > ${ANSWER}

${TARFILE}: ${TAR_LIST}
	${TAR} ${TARFLAGS} ${TARFILE} ${TAR_LIST}

depend: ${FILES.c} ${FILES.h} ${PROGS.c}
	${MKDEP} ${FILES.c} ${PROGS.c}

# DO NOT DELETE THIS LINE or the blank line after it -- make depend uses them.

file1.o: file1.c
file1.o: file3.h
file1.o: prog1.h
file10.o: file10.c
file10.o: prog2.h
file11.o: file11.c
file11.o: prog2.h
file12.o: file12.c
file12.o: prog2.h
file1a.o: file1a.c
file1a.o: file3a.h
file1a.o: prog3.h
file1b.o: external.h
file1b.o: file1b.c
file1b.o: file1c.h
file1b.o: file3b.h
file2.o: file2.c
file2.o: file3.h
file2.o: prog1.h
file2a.o: file2a.c
file2a.o: file3a.h
file2a.o: prog3.h
file2b.o: external.h
file2b.o: file1c.h
file2b.o: file2b.c
file2b.o: file3b.h
file3c.o: external.h
file3c.o: file1c.h
file3c.o: file2c.h
file3c.o: file3c.c
file4c.o: external.h
file4c.o: file1c.h
file4c.o: file2c.h
file4c.o: file4c.c
file5c.o: external.h
file5c.o: file1c.h
file5c.o: file2c.h
file5c.o: file5c.c
file6c.o: external.h
file6c.o: file1c.h
file6c.o: file2c.h
file6c.o: file6c.c
file7c.o: external.h
file7c.o: externdef.h
file7c.o: file1c.h
file7c.o: file2d.h
file7c.o: file7c.c
file8c.o: external.h
file8c.o: externdef.h
file8c.o: file1c.h
file8c.o: file2d.h
file8c.o: file8c.c
file8c.o: file8c.h
file9c.o: external.h
file9c.o: file1c.h
file9c.o: file2d.h
file9c.o: file9c.c
prog1.o: file3.h
prog1.o: prog1.c
prog1.o: prog1.h
prog2.o: prog2.c
prog2.o: prog2.h
prog3.o: file3a.h
prog3.o: prog3.c
prog3.o: prog3.h
prog4.o: external.h
prog4.o: file1c.h
prog4.o: file3b.h
prog4.o: prog4.c
prog4.o: prog4.h
prog5.o: external.h
prog5.o: file1c.h
prog5.o: file2c.h
prog5.o: prog5.c
prog8.o: external.h
prog8.o: file1c.h
prog8.o: file2d.h
prog8.o: prog8.c

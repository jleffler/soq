# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

CC     = gcc #/usr/bin/gcc
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
IFLAG1 = #-I${HOME}/inc
IFLAGS = ${IFLAG1}

LDFLAG1 = #-L${HOME}/lib/64
LDLIB1  = #-ljl
LDLIB2  = #-lcs50
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS  = ${OFLAGS} ${GFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

all: avl1 avl2 avl3

OBJECT.1 = AVL_tree.o test.o
OBJECT.2 = AVL_tree.o avl2.o
OBJECT.3 = AVL_tree.o avl3.o

avl1: ${OBJECT.1}
	${CC} -o $@ ${CFLAGS} ${OBJECT.1} ${LDFLAGS} ${LDLIBS}

avl2: ${OBJECT.2}
	${CC} -o $@ ${CFLAGS} ${OBJECT.2} ${LDFLAGS} ${LDLIBS}

avl3: ${OBJECT.3}
	${CC} -o $@ ${CFLAGS} ${OBJECT.3} ${LDFLAGS} ${LDLIBS}

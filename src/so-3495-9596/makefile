# SO 3495-9596 and SO 3611-6746

include ../../etc/soq-head.mk

PROG1 = avl1
PROG2 = avl2
PROG3 = avl3
PROG4 = avl-tree
PROG5 = avl-36116746

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5}

all: ${PROGRAMS}

OBJECT.1 = AVL_tree.o test.o
OBJECT.2 = AVL_tree.o avl2.o
OBJECT.3 = AVL_tree.o avl3.o

${PROG1}: ${OBJECT.1}
	${CC} -o $@ ${CFLAGS} ${OBJECT.1} ${LDFLAGS} ${LDLIBS}

${PROG2}: ${OBJECT.2}
	${CC} -o $@ ${CFLAGS} ${OBJECT.2} ${LDFLAGS} ${LDLIBS}

${PROG3}: ${OBJECT.3}
	${CC} -o $@ ${CFLAGS} ${OBJECT.3} ${LDFLAGS} ${LDLIBS}

include ../../etc/soq-tail.mk

CC     = /usr/bin/gcc
RM_FR  = rm -fr --
WFLAG1 = -Wall 
WFLAG2 = -Wextra
WFLAG3 = -Wmissing-prototypes 
WFLAG4 = -Wstrict-prototypes 
WFLAG5 = -Wold-style-definition
WFLAG6 =
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6} 
SFLAGS = -std=c99
OFLAGS = -g #-O
UFLAGS =
IFLAGS = -I${HOME}/inc

LDFLAGS = -L${HOME}/lib/64
LDLIBS  = -ljl

CFLAGS = ${OFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

all:
	@echo "You must specify a target to build"

clean:
	${RM_FR} *.o *.dSYM core a.out

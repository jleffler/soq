# SO 30794962
# SO 35147784
# SO 37075084 - now deleted

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
IFLAG1 = -I${HOME}/inc
IFLAGS = ${IFLAG1}
CFLAGS = ${OFLAGS} ${GFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

LDFLAG1 = -L${HOME}/lib/64
LDLIB1  = -ljl
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1}

PROGRAMS = \
	binsearch-speed \
	bs-files \
	bsmax \
	bsmin \
	modbinsearch \
	shiftbinsearch \

all: ${PROGRAMS}

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_FR} ${PROGRAMS}

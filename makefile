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
IFLAG1 = -I./inc
IFLAGS = ${IFLAG1}

IXXFLAGS = ${IFLAGS}
SXXFLAGS = -std=c++11
WXXFLAG1 = -Wall
WXXFLAG2 = -Wextra
WXXFLAG3 = -Werror
WXXFLAG4 =
WXXFLAGS = ${WXXFLAG1} ${WXXFLAG2} ${WXXFLAG3} ${WXXFLAG4}
UXXFLAGS = # Set on comand line
OXXFLAGS = -O3
GXXFLAGS = -g

LDFLAG1 = -L./lib
LDLIB1  = -lsoq
LDLIB2  = #-lcs50
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${UFLAGS}
CXXFLAGS = ${OXXFLAGS} ${GXXFLAGS} ${IXXFLAGS} ${SXXFLAGS} ${WXXFLAGS} ${UXXFLAGS}

# Non-compiling source, or source not compiling to a program
#    incunabulum.c \
#    modern-incunabulum.c \
#    cmpfltint.c \

SCRIPT_PROGRAMS = \
	check-rename \
	rangesquash1 \
	rangesquash2 \
	rangesquash3 \
	rangesquash4 \
	run-processes \

C_ONLY_PROGRAMS = \
	pthread-37 \
	rev \
	revlist \
	term-pgrp \
	test-rename \

CXX_ONLY_PROGRAMS = \
	map \
	mppsel \
	qsel \
	stld \

C_CXX_DUAL_PROGRAMS = \
	bst-1 \
	bst-2 \
	computist-1 \
	computist-2 \
	e2big \
	factors \
	gai \
	ll3 \
	partition-4 \
	pbb \
	pthread-1 \
	pthread-2 \
	pthread-3 \
	quine \
	readdir \
	roundup \
	sigalrm \
	sigchld \
	signals \
	test-fstatat \
	uint128 \

PROGRAMS = \
	${SCRIPT_PROGRAMS} \
	${C_ONLY_PROGRAMS} \
	${CXX_ONLY_PROGRAMS} \
	${C_CXX_DUAL_PROGRAMS}

default:
	@echo "You must specify a target to build"

all: ${PROGRAMS}

script:		${SCRIPT_PROGRAMS}
c_only:		${C_ONLY_PROGRAMS}
cxx_only:	${CXX_ONLY_PROGRAMS}
dual:		${C_CXX_DUAL_PROGRAMS}

#pthread-1: CFLAGS += -Wno-deprecated-declarations

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_FR} ${PROGRAMS}

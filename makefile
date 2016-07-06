# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include etc/soq-head.mk

IFLAGS  = -I./inc
LDFLAG1 = -L./lib

SCRIPT_PROGRAMS = \
	check-rename \

C_ONLY_PROGRAMS = \
	pthread-37 \
	rev \
	revlist \
	term-pgrp \
	test-rename \

CXX_ONLY_PROGRAMS = \
	map \

C_CXX_DUAL_PROGRAMS = \
	bst-1 \
	bst-2 \
	gai \
	pthread-1 \
	pthread-2 \
	pthread-3 \
	readdir \
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

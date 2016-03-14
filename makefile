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

LDFLAG1 = -L${HOME}/lib/64
LDLIB1  = -ljl
LDLIB2  = #-lcs50
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${UFLAGS}
CXXFLAGS = ${OXXFLAGS} ${GXXFLAGS} ${IXXFLAGS} ${SXXFLAGS} ${WXXFLAGS} ${UXXFLAGS}

# Non-compiling source, or source not compiling to a program
#    incunabulum.c \
#    modern-incunabulum.c \
#    cmpfltint.c \
#	 substr.c \		# -DTEST to make executable
#	 rangesquash1.pl
#	 rangesquash2.pl
#	 rangesquash3.pl
#	 rangesquash4.pl
#

SCRIPT_PROGRAMS = \
	am-pm \
	check-rename \
	expand_tilde \
	filter.stderr \
	genouterr \
	multiopts \
	rangesquash1 \
	rangesquash2 \
	rangesquash3 \
	rangesquash4 \
	run-processes

C_ONLY_PROGRAMS = \
	binary \
	if \
	if-jl \
	if-strict \
	matmul99 \
	visit

CXX_ONLY_PROGRAMS = \
	heapprt \
	map \
	mppsel \
	qsel \
	test-rename

C_CXX_DUAL_PROGRAMS = \
	2da \
	3dalloc1 \
	3dalloc2 \
	3dalloc3 \
	3dalloc4 \
	arraysize \
	bst-1 \
	bst-2 \
	cntinv \
	colourpartition \
	computist-1 \
	computist-2 \
	e2big \
	excel-rc \
	factors \
	fault \
	fifocircle \
	fifosize \
	gai \
	isprime \
	ll3 \
	madump \
	marquee \
	marquee3 \
	marquee4 \
	matmake3d \
	matmul89 \
	mda \
	partition-4 \
	pbb \
	pipecircle \
	pipesize \
	prime-factors \
	pthread-1 \
	pthread-2 \
	pthread-3 \
	q7 \
	quine \
	ratcalc \
	rational \
	readdir \
	recv \
	regress \
	roundup \
	scan \
	send \
	sigalrm \
	sigchld \
	signals \
	so.33887484 \
	streplace \
	test-fstatat \
	timezeromoves \
	uint128 \
	unwrap

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

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_FR} ${PROGRAMS}

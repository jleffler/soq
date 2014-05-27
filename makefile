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
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1}

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

PROGRAMS = \
	3-star \
	4-star \
	am-pm \
	arraysize \
	binary \
	bst \
	cntinv \
	colourpartition \
	computist-1 \
	computist-2 \
	e2big \
	excel-rc \
	expand_tilde \
	factors \
	fault \
	fifocircle \
	fifosize \
	filter.stderr \
	gai \
	genouterr \
	heapprt \
	ll3 \
	madump \
	matmake3d \
	matmul89 \
	matmul99 \
	mda \
	multiopts \
	pipecircle \
	pipesize \
	prime-factors \
	pthread-1 \
	pthread-2 \
	pthread-3 \
	q7 \
	quine \
	readdir \
	recv \
	regress \
	roundup \
	scan \
	send \
	sigalrm \
	sigchld \
	signals \
	streplace \
	timezeromoves \
	uint128 \
	unwrap \
	visit

default:
	@echo "You must specify a target to build"

all: ${PROGRAMS}

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_FR} ${PROGRAMS}

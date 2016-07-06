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
DFLAGS = -DDEBUG

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
DXXFLAGS = #

LDFLAG1 = -L${HOME}/lib/64
LDLIB1  = -ljl
LDFLAGS = ${LDFLAG1}
LDLIBS  = ${LDLIB1}

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${UFLAGS}   ${DFLAGS}
CXXFLAGS = ${OXXFLAGS} ${GXXFLAGS} ${IXXFLAGS} ${SXXFLAGS} ${WXXFLAGS} ${UXXFLAGS} ${DXXFLAGS}

CXX_ONLY_PROGRAMS = \
	so28005392

C_CXX_DUAL_PROGRAMS = \
	eratosthenes-1 \
	eratosthenes-2 \
	eratosthenes-3 \
	eratosthenes-4 \
	eratosthenes-5 \
	eratosthenes-6

C_CXX_PROGRAMS = ${C_CXX_DUAL_PROGRAMS:=-cxx}

C_ONLY_PROGRAMS = \
	isprime \
	minimal-primes \
	prime-factors \
	project-euler-87

PROGRAMS = \
	${C_ONLY_PROGRAMS} \
	${CXX_ONLY_PROGRAMS} \
	${C_CXX_DUAL_PROGRAMS}

all: ${PROGRAMS}

c_only:     ${C_ONLY_PROGRAMS}
cxx_only:	${CXX_ONLY_PROGRAMS}
dual:		${C_CXX_DUAL_PROGRAMS}
dual_cxx:	${C_CXX_PROGRAMS}

C_CXX_SOURCE = ${C_CXX_PROGRAMS:=.cpp}

LN_S = ln -s
RM_F = rm -f

${C_CXX_SOURCE}: ${@:-cxx.cpp=.c}
	${LN_S} ${@:-cxx.cpp=.c} $@

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} *.o *.dSYM core a.out
	${RM_F} ${PROGRAMS}
	${RM_F} ${C_CXX_PROGRAMS}
	${RM_F} ${C_CXX_SOURCE}

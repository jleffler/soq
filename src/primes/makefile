# Primes - various prime number programs

include ../../etc/soq-head.mk

CXX_ONLY_PROGRAMS = \
	so28005392 \

C_CXX_DUAL_PROGRAMS = \
	eratosthenes-1 \
	eratosthenes-2 \
	eratosthenes-3 \
	eratosthenes-4 \
	eratosthenes-5 \
	eratosthenes-6 \

C_CXX_PROGRAMS = ${C_CXX_DUAL_PROGRAMS:=-cxx}

C_ONLY_PROGRAMS = \
	alt-min-primes \
	isprime \
	minimal-primes \
	prime-factors \
	project-euler-87 \

PROGRAMS = \
	${C_ONLY_PROGRAMS} \
	${CXX_ONLY_PROGRAMS} \
	${C_CXX_DUAL_PROGRAMS} \
	${C_CXX_PROGRAMS} \

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

OUTFILES = \
	eratosthenes-1-cxx.cpp \
	eratosthenes-2-cxx.cpp \
	eratosthenes-3-cxx.cpp \
	eratosthenes-4-cxx.cpp \
	eratosthenes-5-cxx.cpp \
	eratosthenes-6-cxx.cpp \

include ../../etc/soq-tail.mk

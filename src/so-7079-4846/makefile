# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include ../../etc/soq-head.mk

SOQBASE = jl
IFLAGS = -I${HOME}/inc
LDFLAGS = -L${HOME}/lib/64

PROG1 = csqm-fla-23
PROG2 = csqm-vla-29
PROG3 = csqm-vla-q-31
PROG4 = csqm-vla-args-37
PROG5 = so-tshiono-bust
PROG6 = so-tshiono-work
PROG7 = so-tshiono-ans1
PROG8 = so-tshiono-ans2

PROGRAMS = \
	${PROG1} \
	${PROG2} \
	${PROG3} \
	${PROG4} \
	${PROG5} \
	${PROG6} \
	${PROG7} \
	${PROG8} \

TEST_PROGRAMS = \
	${PROG1} \
	${PROG2} \
	${PROG4} \

all: ${PROGRAMS}

TESTS = \
	test.1 \
	test.2 \
	test.3 \
	test.4 \
	test.5 \
	test.6 \
	test.7 \
	test.8 \
	test.9 \

test: ${TEST_PROGRAMS} ${TESTS}
	for prog in ${TEST_PROGRAMS}; \
	do \
	    for test in ${TESTS}; \
		do \
			echo "$$prog: $$test"; \
			$$prog < $$test; \
		done \
	done

include ../../etc/soq-tail.mk

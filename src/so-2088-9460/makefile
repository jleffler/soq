# SO 20889460

include ../../etc/soq-head.mk

PROG1 = example
PROG2 = listsyshdrs
PROG3 = mksurrogates

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS}

HEADER1   = class_a.hpp
HEADER2   = class_b.hpp
HEADER3   = class_c.hpp
HEADERS   = ${HEADER1} ${HEADER2} ${HEADER3}
SOURCE    = example.cpp

MKPATH    = mkdir -p
SYSHDRDIR = system-headers

.PHONY: make-surrogates test

make-surrogates:	${PROG2} ${PROG3} ${SOURCE} ${HEADERS}
	${MKPATH} ${SYSHDRDIR}
	${PROG3} $$(${PROG2} ${SOURCE} ${HEADERS})

# Clean-up
OUTDIRS = ${SYSHDRDIR}

# GNU Make manages to interpret this OK, but RMK truncates at the `#`.
# Is there a sensible way to fix this?
# How does GNU Make handle strings vs comments?
# Is it 'white space before #'?

test: make-surrogates
	${CXX} -E -D'include=#include' -I. -I${SYSHDRDIR} example.cpp | \
	grep -v '^# [0-9]'

include ../../etc/soq-tail.mk

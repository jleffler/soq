# SO 20889460

include ../../etc/soq-head.mk

PROG1 = example
PROG2 = listsyshdrs
PROG3 = mksurrogates

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS}

# GNU Make manages to interpret this OK, but RMK truncates at the `#`.
# Is there a sensible way to fix this?
# How does GNU Make handle strings vs comments?
# Is it 'white space before #'?

test:
	${CXX} -E -D'include=#include' -I. -Isystem-headers example.cpp | \
	grep -v '^# [0-9]'

include ../../etc/soq-tail.mk

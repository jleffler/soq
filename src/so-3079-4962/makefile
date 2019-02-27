# SO 3079-4962
# SO 3514-7784
# SO 3707-5084 - now deleted
# SO 4477-2009
# SO 4584-8084

include ../../etc/soq-head.mk

# Weirdnesses
# 1. bsearch.c is a symlink to bsearch-4477-2009.c
# 2. bscheck.c includes bsearch.c
# Consequently:
# * Don't include bsearch or bsearch-4477-2009 in programs list
# * Don't need a special commands to compile/link bscheck.

PROGRAMS = \
	binsearch-speed \
	bscheck \
	bs-files \
	bsmax \
	bsmin \
	bsrange \
	bsrange-chux-00 \
	bsrange-chux-01 \
	modbinsearch \
	rangebinsearch \
	shiftbinsearch \

all: ${PROGRAMS}

bscheck: bscheck.c bsearch.c

include ../../etc/soq-tail.mk

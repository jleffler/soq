# SO 42522720

include ../../etc/soq-head.mk

PROG1 = so-4252-2720

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

test:	${PROGRAMS}
	${PROG1} < data.0 #&& cat man0.txt
	@echo
	${PROG1} < data.1 #&& cat man0.txt
	@echo
	${PROG1} < data.2 #&& cat man0.txt

include ../../etc/soq-tail.mk

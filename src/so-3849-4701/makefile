# SO 3849-4701

include ../../etc/soq-head.mk

PROG1 = gen-samples1
PROG2 = gen-samples2
PROG3 = join-samples
PROG4 = three-file-solution

# sampleXX.file  from gen-samples1
# sample-XX.file from gen-samples2
OUTFILES = sample[0-9][0-9].file sample-[0-9][0-9].file

PROGRAMS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

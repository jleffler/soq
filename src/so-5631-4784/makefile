# Makefile for SO 5631-4784

include ../../etc/soq-head.mk

# It's necessary to link with -lrt on Linux
# There is no libert.{a,so,dylib} on macOS 10.14.5 Mojave or earlier versions.
# For macOS, compile with: make UFLAGS=-DUSE_SETITIMER LDLIB2=
LDLIB2   = -lrt
PROG1    = chunker79
PROGRAMS = ${PROG1}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

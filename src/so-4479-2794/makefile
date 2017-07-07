# Makefile for SO 4479-2794
#
# Copy directory hierarchy — client/server

include ../../etc/soq-head.mk

IFLAG1 =
IFLAG2 = -I${HOME}/inc
LDFLAG2 = -L${HOME}/lib/64
LDLIB1 =
LDLIB2 = -ljl

PROGRAMS = cpd-client cpd-server client-20170706 server-20170706

all: ${PROGRAMS}

cpd-client: cpd.h
cpd-server: cpd.h

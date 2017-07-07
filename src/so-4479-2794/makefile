# Makefile for SO 4479-2794
#
# Copy directory hierarchy — client/server

include ../../etc/soq-head.mk

DFLAG1 = -DHAVE_CONFIG_H
DFLAG2 = -DUSE_STDERR_SYSLOG
DFLAGS = ${DFLAG1} ${DFLAG2}
IFLAG1 =
IFLAG2 = #-I${HOME}/inc
LDFLAG1 = -L.
LDFLAG2 = #-L${HOME}/lib/64
LDLIB1 =
LDLIB2 = -l${LIBBASE}

LIBOBJ = \
	daemonize.o \
	errhelp.o \
	stderr.o \
	tcp_accept.o \
	tcp_connect.o \
	tcp_listen.o \

LIBBASE = cpd
LIBNAME = lib${LIBBASE}.a

PROGRAMS = cpd-client cpd-server client-20170706 server-20170706

all: ${LIBNAME} ${PROGRAMS}

${LIBNAME}: ${LIBNAME}(${LIBOBJ})

cpd-client: ${LIBNAME} cpd.h
cpd-server: ${LIBNAME} cpd.h

# Makefile for SO 4479-2794
#
# Copy directory hierarchy — client/server

CC     = gcc
DFLAG1 = -DHAVE_CONFIG_H
DFLAG2 = -DUSE_STDERR_SYSLOG
DFLAGS = ${DFLAG1} ${DFLAG2}
GFLAGS = -g
IFLAG1 = #-I${INCDIR}
IFLAG2 = #-I${HOME}/inc
IFLAGS = ${IFLAG1} ${IFLAG2}
OFLAGS = -O3
SFLAGS = -std=c11
UFLAGS = # Set on command line
WFLAG1 = -Wall
WFLAG2 = -Wextra
WFLAG3 = -Werror
WFLAG4 = -Wmissing-prototypes
WFLAG5 = -Wstrict-prototypes
WFLAG6 = #-Wold-style-declaration   # Strict GCC only (not clang, it would seem).
WFLAG7 = #-Wold-style-definition    # Part of -Wextra in GCC 7.1.0
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6} ${WFLAG7}

LDFLAG1 = -L.
LDFLAG2 = #-L${HOME}/lib/64
LDFLAGS = ${LDFLAG1} ${LDFLAG2}
LDLIB1  = -l${LIBBASE}
LDLIB2  = #-l${CS50BASE}
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS  = ${OFLAGS} ${GFLAGS} ${DFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

DEBRIS = core a.out *~ *.o *.dSYM
RM_FR  = rm -fr
RM_F   = rm -f

LIBOBJ = \
	daemonize.o \
	emalloc.o \
	errhelp.o \
	estrdup.o \
	mkpath.o \
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

clean:
	${RM_FR} ${LIBNAME} ${PROGRAMS} ${DEBRIS}

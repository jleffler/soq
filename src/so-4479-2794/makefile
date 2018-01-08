# Makefile for SO 4479-2794
#
# Copy directory hierarchy — client/server

CC     = gcc
DFLAG1 = -DHAVE_CONFIG_H
DFLAG2 = -DUSE_STDERR_SYSLOG
DFLAGS = ${DFLAG1} ${DFLAG2}
GFLAGS = -g
IFLAG1 = -I.
IFLAG2 = -I${HOME}/inc
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
LDFLAG2 = -L${HOME}/lib/64
LDFLAGS = ${LDFLAG1} ${LDFLAG2}
LDLIB1  = #-l${LIBBASE}
LDLIB2  = -ljl
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS  = ${OFLAGS} ${GFLAGS} ${DFLAGS} ${IFLAGS} ${SFLAGS} ${WFLAGS} ${UFLAGS}

DEBRIS = core a.out *~ *.o *.dSYM
RM_FR  = rm -fr
RM_F   = rm -f
LN_S   = ln -s

HDR_DIR = ${HOME}/inc
SRC_DIR = ${HOME}/lib/JL

LIBSRC = \
	daemonize.c \
	emalloc.c \
	errhelp.c \
	estrdup.c \
	mkpath.c \
	stderr.c \
	tcp_accept.c \
	tcp_connect.c \
	tcp_listen.c \

LIBHDR = \
	config.h \
	debug.h \
	emalloc.h \
	kludge.h \
	mkpath.h \
	posixver.h \
	stderr.h \
	sysstat.h \
	unp.h \
	unpv13e.h \

LIBOBJ = ${LIBSRC:.c=.o}

LIBBASE = cpd
LIBNAME = lib${LIBBASE}.a

PROGRAMS = cpd-client cpd-server client-20170706 server-20170706

all: ${LIBNAME} ${PROGRAMS}

${LIBNAME}: ${LIBNAME}(${LIBOBJ})

cpd-client: ${LIBNAME} cpd.h
cpd-server: ${LIBNAME} cpd.h

headers: ${LIBHDR}
source:  ${LIBSRC}

${LIBSRC}:
	${LN_S} ${SRC_DIR}/$@ .

${LIBHDR}:
	${LN_S} ${HDR_DIR}/$@ .

clean:
	${RM_FR} ${LIBNAME} ${PROGRAMS} ${DEBRIS}

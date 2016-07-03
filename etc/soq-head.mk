# Makefile fragment for SOQ GitHub Project
#
# Use: include ../../etc/soq.mk in a per-directory source file

BASEDIR = ../..

LIBBASE = soq
LIBNAME = lib${LIBBASE}.a
LIBDIR  = ${BASEDIR}/lib
HDRDIR  = ${BASEDIR}/inc
LIBPATH = ${LIBDIR}/${LIBNAME}

CC     = gcc
TFLAGS = # Set to -DTEST when needed
SFLAGS = -std=c11
WFLAG1 = -Wall
WFLAG2 = -Wextra
WFLAG3 = -Werror
WFLAG4 = -Wmissing-prototypes
WFLAG5 = -Wstrict-prototypes
WFLAG6 = #-Wold-style-declaration # Strict GCC only (not clang, it would seem).
WFLAG7 = -Wold-style-definition
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6} ${WFLAG7}
OFLAGS = -O3
GFLAGS = -g
UFLAGS = # Set on command line
IFLAGS = -I${BASEDIR}/inc

CFLAGS = ${SFLAGS} ${OFLAGS} ${GFLAGS} ${WFLAGS} ${UFLAGS} ${IFLAGS} ${TFLAGS}

LDFLAGS = -L${BASEDIR}/lib
LDLIBS  = -lsoq

DEBRIS = core a.out *~ *.o
RM_FR  = rm -fr
RM_F   = rm -f


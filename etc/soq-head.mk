# Makefile fragment for SOQ GitHub Project
#
# Use: include ../../etc/soq.mk in a per-directory source file

BASEDIR = ../..
LIBDIR  = ${BASEDIR}/lib
HDRDIR  = ${BASEDIR}/inc

SOQBASE = soq
SOQNAME = lib${SOQBASE}.a
SOQPATH = ${LIBDIR}/${SOQNAME}

# Backwards compatibility
LIBBASE = ${SOQBASE}
LIBNAME = ${SOQNAME}
LIBPATH = ${SOQPATH}

CS50BASE = cs50
CS50NAME = lib${CS50BASE}.a
CS50PATH = ${LIBDIR}/${CS50NAME}

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
IFLAGS = -I${HDRDIR}

CFLAGS = ${SFLAGS} ${OFLAGS} ${GFLAGS} ${WFLAGS} ${UFLAGS} ${IFLAGS} ${TFLAGS}

LDFLAGS = -L${LIBDIR}
LDLIBS  = -l${SOQBASE}

DEBRIS = core a.out *~ *.o
RM_FR  = rm -fr
RM_F   = rm -f


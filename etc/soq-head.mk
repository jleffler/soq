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
GFLAGS = -g
IFLAGS = -I${HDRDIR}
OFLAGS = -O3
SFLAGS = -std=c11
TFLAGS = # Set to -DTEST (or similar) when needed
UFLAGS = # Set on command line
WFLAG1 = -Wall
WFLAG2 = -Wextra
WFLAG3 = -Werror
WFLAG4 = -Wmissing-prototypes
WFLAG5 = -Wstrict-prototypes
WFLAG6 = #-Wold-style-declaration # Strict GCC only (not clang, it would seem).
WFLAG7 = -Wold-style-definition
WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6} ${WFLAG7}

GXXFLAGS = -g
IXXFLAGS = ${IFLAGS}
OXXFLAGS = -O3
SXXFLAGS = -std=c++11
TXXFLAGS = # Set to -DTEST (or similar) when needed
UXXFLAGS = # Set on comand line
WXXFLAG1 = -Wall
WXXFLAG2 = -Wextra
WXXFLAG3 = -Werror
WXXFLAG4 =
WXXFLAGS = ${WXXFLAG1} ${WXXFLAG2} ${WXXFLAG3} ${WXXFLAG4}

LDFLAG1 = -L${LIBDIR}
LDFLAGS = ${LDFLAG1}
LDLIB1  = -l${SOQBASE}
LDLIB2  = #-l${CS50BASE}
LDLIBS  = ${LDLIB1} ${LDLIB2}

CFLAGS   = ${OFLAGS}   ${GFLAGS}   ${IFLAGS}   ${SFLAGS}   ${WFLAGS}   ${TFLAGS}   ${UFLAGS}
CXXFLAGS = ${OXXFLAGS} ${GXXFLAGS} ${IXXFLAGS} ${SXXFLAGS} ${WXXFLAGS} ${TXXFLAGS} ${UXXFLAGS}

DEBRIS = core a.out *~ *.o
RM_FR  = rm -fr
RM_F   = rm -f


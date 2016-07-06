# SO 27733348

# Non-compiling code
#    if.c \         # Archaic code; cannot be compiled by GCC 5 or 6
#                   # Requires minimal compilation options and GCC 4.x
#                   # (or possibly an earlier version).
#    if-jl.c        # Also archaic code; compiles OK with GCC 6.1.0 with
#                   # gcc -o if-jl -std=c90 if-jl.c

include ../../etc/soq-head.mk

PROG1 = #if-jl
PROG2 = if-strict
PROG3 = #if

PROGRAMS = ${PROG1} ${PROG2} ${PROG3}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

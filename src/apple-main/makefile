# Demonstrate Apple-specific 4-argument main()

include ../../etc/soq-head.mk

# Suppress warning about number of arguments to main()
# ala.c:15:5: error: 'main' takes only zero or two arguments [-Werror=main]
WFLAGS += -Wno-main

PROG1 = ala

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

include ../../etc/soq-tail.mk

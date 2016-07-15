# To suppress JL-specific options:
# LDLIBS= LDFLAGS= IFLAGS=

include etc/soq-head.mk

BASEDIR = .

default:
	@echo "You must specify a target to build"

.DEFAULT:
	+cd src; ${MAKE} $@

remove:
	@if [ -z "${PROG}" ]; then echo "You must set PROG=name on command line" && exit 1; else exit 0; fi
	${RM_FR} ${PROG} ${PROG}.*

clean:
	${RM_FR} ${DEBRIS} *.dSYM

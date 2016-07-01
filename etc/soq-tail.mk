# Makefile fragment for inclusion at end of SOQ makefiles
#
# Provides target 'clean' to do sensible cleaning.
# Relies on user to set macro PROGRAMS (plural) for removing programs.
# Assumes etc/soq-head.mk is already included.

clean:
	${RM_F} *.o *.a ${DEBRIS}
	${RM_F} ${PROGRAMS}
	${RM_FR} *.dSYM

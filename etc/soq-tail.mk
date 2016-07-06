# Makefile fragment for inclusion at end of SOQ makefiles
#
# Provides target 'clean' to do sensible cleaning.
# Relies on user to set macro PROGRAMS (plural) for removing programs.
# Assumes etc/soq-head.mk is already included.
# OUTFILES is set per makefile to hold output file names that should be
# cleaned.

clean:
	${RM_F} *.o *.a ${DEBRIS} ${OUTFILES}
	${RM_F} ${PROGRAMS}
	${RM_FR} *.dSYM

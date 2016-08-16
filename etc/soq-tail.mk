# Makefile fragment for inclusion at end of SOQ makefiles
#
# Provides target 'clean' to do sensible cleaning.
# Relies on user to set macro PROGRAMS (plural) for removing programs.
# Assumes etc/soq-head.mk is already included.
# OUTFILES can be set per makefile to hold output file names that should
# be cleaned.  OUTDIRS can be set per makefile to hold output directory
# names that should be cleaned.
# .dSYM directories are an artefact of building single-file programs on
# .Mac OS X (or using dsymutil).

.DEFAULT:
	@echo "No commands specified for building $@"

clean:
	${RM_F} *.o *.a ${DEBRIS} ${OUTFILES}
	${RM_F} ${PROGRAMS}
	${RM_FR} *.dSYM ${OUTDIRS}

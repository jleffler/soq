# Makefile for src directory in SOQ project

include ../etc/soq.mk

BUILD_DIRECTORIES = \
	lib \
	so-0429-4928 \
	so-3333-8314 \
	so-3388-7484 \
	so-3757-7522 \
	so-3775-3785 \
	so-3799-7620 \
	so-3807-9550 \

.DEFAULT all:
	+for dir in ${BUILD_DIRECTORIES}; \
	do (echo "+++ $${dir}"; cd "$${dir}" && ${MAKE} $@ && echo "--- $${dir}") \
	done

# Makefile for src directory in SOQ project

include ../etc/soq-head.mk

BUILD_DIRECTORIES = \
	lib \
	so-0044-0061 \
	so-0429-4928 \
	so-0765-1397 \
	so-1251-5755 \
	so-1348-4943 \
	so-1718-2582 \
	so-1886-3184 \
	so-1930-4085 \
	so-2029-3405 \
	so-2801-0892 \
	so-3029-4129 \
	so-3109-6894 \
	so-3257-8455 \
	so-3333-8314 \
	so-3388-7484 \
	so-3567-8399 \
	so-3757-7522 \
	so-3775-3785 \
	so-3799-7620 \
	so-3807-9550 \

.DEFAULT all:
	+for dir in ${BUILD_DIRECTORIES}; \
	do (echo "+++ $${dir}"; cd "$${dir}" && ${MAKE} $@ && echo "--- $${dir}") \
	done

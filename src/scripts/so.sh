#!/bin/sh
#
# Indent by four spaces for Stack Overflow

exec sed '/./s/^/    /' "$@"

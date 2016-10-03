set -x
make -f gccbug.mk -B CC=clang gccbug && gccbug < gccbug.tsv
make -f gccbug.mk -B CC=gcc   gccbug && gccbug < gccbug.tsv

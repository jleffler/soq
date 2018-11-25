# Project 3 - CS221 Fall 2018
# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -O0 -Wall -Werror -g -pedantic
FLAGS = -std=c99 -O3 -Wall -Werror -g -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wextra

climate: climate.c
	$(CC) $(FLAGS) climate.c -o climate

clean:
	rm -f climate
	rm -rf *.dSYM


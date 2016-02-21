all: sleeper install

install: sleeper
	install sleeper ../bin/sleeper

sleeper: sleeper.c
	gcc -Wall -o $@ $<

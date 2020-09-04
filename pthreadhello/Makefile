#
# Makefile for pthreadhello


PROGRAMS=pthreadhello
CC=gcc -pthread -Wall

all:	$(PROGRAMS)

pthreadhello:	pthreadhello.c
	$(CC) -o pthreadhello pthreadhello.c

clean::
	/bin/rm -f $(PROGRAMS)

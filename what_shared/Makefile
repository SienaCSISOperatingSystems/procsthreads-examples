# Makefile for pthread/for what_shared example
#
# Jim Teresco, CS 338, CS 432
# Williams College
#
# Wed Feb 26 11:35:20 EST 2003
#
CFILES=what_shared.c
OFILES=$(CFILES:.c=.o)
CC=gcc -pthread -Wall

what_shared:	$(OFILES)
	$(CC) -o what_shared $(OFILES)

clean::
	/bin/rm -f what_shared $(OFILES)

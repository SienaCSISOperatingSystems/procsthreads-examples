# Makefile for pthread tree program
#
# Jim Teresco, CS 338
# Williams College
#
# Wed Feb 12 23:34:58 EST 2003
#
# $Id$
#
CFILES=proctree_threads.c
OFILES=$(CFILES:.c=.o)
CC=gcc -pthread -Wall

proctree_threads:	$(OFILES)
	$(CC) -o proctree_threads $(OFILES)

clean::
	/bin/rm -f proctree_threads $(OFILES)

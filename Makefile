#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
# Time-stamp: <Tue Aug  8 10:34:37 EDT 2017 ferguson>
#

PROGRAMS = IntSet_test LinkedList_test auto
CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

IntSet_test: IntSet_test.o IntSet.o
	$(CC) -o $@ $^

LinkedList_test: LinkedList_test.o LinkedList.o IntSet.o
	$(CC) -o $@ $^

auto: auto.o nfa.o dfa.o IntSet.o LinkedList.o translator.o
	$(CC) -o $@ $^

clean:
	-rm $(PROGRAMS) *.o

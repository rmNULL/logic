CC=gcc
FLAGS=-Wall -std=gnu11 -pedantic-errors

tmp: test
	valgrind --tool=memcheck --leak-check=full ./op
	make clean

test: gates.o tests.c ds/slist.o
	$(CC) $(FLAGS) $^ -o op

gates.o: gates.c gates.h
ds/slist.o: ds/slist.h ds/slist.c

clean:
	$(RM) gates.o op a.out ds/slist.o

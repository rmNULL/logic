CC=gcc
FLAGS=-Wall -std=c99 -pedantic-errors -Wconversion
LIB_PATH=./lib
LIB_NAME=logic

OBJ=gates.o ds/slist.o

tmp: test
	valgrind --tool=memcheck --leak-check=full ./op
	make clean

test: $(LIB_PATH)/liblogic.a tests.c
	$(CC) $(FLAGS) -L$(LIB_PATH) tests.c -o op -l$(LIB_NAME)

gates.o: gates.h gates.c ds/slist.o
ds/slist.o: ds/slist.h ds/slist.c

build: gates.o
	ar -cvr lib/liblogic.a $(OBJ)

clean:
	$(RM) op a.out $(OBJ)

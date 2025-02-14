CC=gcc
LDFLAGS= -lutils
CFLAGS=-c -Wall -Wextra -g

ARRAY_FILE=stack_array.c
LIST_FILE=stack_list.c
BIN=stack

all:
	@echo "Usage: make <array | list>"

list:
	$(CC) $(CFLAGS) $(LIST_FILE) -o stack_list.o
	$(CC) stack_list.o test.c $(LDFLAGS) -o $(BIN)

array:
	$(CC) $(CFLAGS) $(ARRAY_FILE) -o stack_array.o
	$(CC) stack_array.o test.c $(LDFLAGS) -o $(BIN)

clean:
	rm -f *.o $(BIN)
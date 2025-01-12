CC=gcc
LDFLAGS= -lutils
CFLAGS=-c -Wall -Wextra -g

ARRAY_FILE=queue_array.c
LIST_FILE=queue_list.c
BIN=queue

all:
	@echo "Usage: make <array | list>"

list:
	$(CC) $(CFLAGS) $(LIST_FILE) -o queue_list.o
	$(CC) queue_list.o test.c $(LDFLAGS) -o $(BIN)

array:
	$(CC) $(CFLAGS) $(ARRAY_FILE) -o queue_array.o
	$(CC) queue_array.o test.c $(LDFLAGS) -o $(BIN)

clean:
	rm *.o $(BIN)
CC=gcc
LDFLAGS= -lutils
CFLAGS=-c -Wall -Wextra -g

CLOSED=closed_adressing.c
OPEN=open_adressing.c
CUCKOO=cuckoo_hashing.c
HOPSCOCTH=hopscotch_hashing.c

BIN=hash

all:
	@echo "Usage: make <closed | open | cuckoo | hopscotch>"

closed: hash_functions.o test.c
	$(CC) $(CFLAGS) $(CLOSED) -o closed_adressing.o
	$(CC) closed_adressing.o $^ $(LDFLAGS) -o $(BIN)

open: hash_functions.o test.c
	$(CC) $(CFLAGS) $(OPEN) -o open_adressing.o
	$(CC) open_adressing.o $^ $(LDFLAGS) -o $(BIN)

cuckoo: hash_functions.o test.c
	$(CC) $(CFLAGS) $(CUCKOO) -o cuckoo_hashing.o
	$(CC) cuckoo_hashing.o $^ $(LDFLAGS) -o $(BIN)

hopscotch: hash_functions.o test.c
	$(CC) $(CFLAGS) $(HOPSCOCTH) -o hopscotch_hashing.o
	$(CC) hopscotch_hashing.o $^ $(LDFLAGS) -o $(BIN)

hash_functions.o: hash_functions.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(BIN)
CC=gcc
LDFLAGS= -lutils
CFLAGS=-Wall -Wextra -g -fsanitize=address

CLOSED=closed_adressing.c
OPEN=open_adressing.c
CUCKOO=cuckoo_hashing.c
HOPSCOCTH=hopscotch_hashing.c

BIN=hash

all:
	@echo "Usage: make <closed | open | cuckoo | hopscotch>"

closed: hash_functions.o test.c
	$(CC) -c $(CFLAGS) $(CLOSED) -o closed_adressing.o
	$(CC) $(CFLAGS) closed_adressing.o $^ $(LDFLAGS) -o $(BIN)

open: hash_functions.o test.c
	$(CC) -c $(CFLAGS) $(OPEN) -o open_adressing.o
	$(CC) $(CFLAGS) open_adressing.o $^ $(LDFLAGS) -o $(BIN)

cuckoo: hash_functions.o test.c
	$(CC) -c $(CFLAGS) $(CUCKOO) -o cuckoo_hashing.o
	$(CC) $(CFLAGS) cuckoo_hashing.o $^ $(LDFLAGS) -o $(BIN)

hopscotch: hash_functions.o test.c
	$(CC) -c $(CFLAGS) $(HOPSCOCTH) -o hopscotch_hashing.o
	$(CC) $(CFLAGS) hopscotch_hashing.o $^ $(LDFLAGS) -o $(BIN)

hash_functions.o: hash_functions.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o $(BIN)
CC=gcc
LDFLAGS=-lutils
CFLAGS=-Wall -Wextra

CFILES=$(filter-out test.c, $(wildcard *.c))
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=algorithms

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
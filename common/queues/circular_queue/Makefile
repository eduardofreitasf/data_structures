CC=gcc
LDFLAGS=
CFLAGS=-Wall -Wextra -g

CFILES=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=circular_queue

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
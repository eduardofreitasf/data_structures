CC=gcc
LDFLAGS=
CFLAGS=-Wall -Wextra -g

CFILES=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=lists

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
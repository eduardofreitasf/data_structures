CC=gcc
LDFLAGS=
CFLAGS=-c -Wall -Wextra -g

CFILES=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=sorts

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
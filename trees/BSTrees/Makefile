CC=gcc
LDFLAGS=-lutils -lm
CFLAGS=-Wall -Wextra -g -fsanitize=address -static-libasan -fno-omit-frame-pointer

CFILES=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=trees

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
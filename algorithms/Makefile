CC=gcc
LDFLAGS=-lutils -lcriterion 
CFLAGS=-Wall -Wextra -fPIC -fprofile-arcs -ftest-coverage

CFILES=$(filter-out test.c, $(wildcard *.c))
OBJS=$(patsubst %.c, %.o, $(CFILES))
BIN=algorithms

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -fPIC -fprofile-arcs -ftest-coverage $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm $(OBJS) $(BIN)
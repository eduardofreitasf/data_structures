#==========================================================================================
BLD_DIR=build
DOC_DIR=docs
INC_DIR=include
SRC_DIR=src
#------------------------------------------------------------------------------------------
CC=gcc
OPTS=-O2
LDFLAGS=-lm
CFLAGS=-Wall -Wextra $(OPTS) -pedantic-errors -I $(INC_DIR)
#------------------------------------------------------------------------------------------
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(C_FILES))
#------------------------------------------------------------------------------------------
PROGRAM=program
#==========================================================================================

.DEFAULT_GOAL = all

all: setup $(PROGRAM)

$(PROGRAM): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: setup
setup:
	@mkdir -p $(BLD_DIR)

# tools for debugging
.PHONY: debug
debug: CFLAGS = -Wall -Wextra -pedantic -O0 -g -I $(INC_DIR)
debug: all
	gdb $(PROGRAM)

# @gdb $(PROGRAM)

.PHONY: memory
memory: CFLAGS = -Wall -Wextra -pedantic -O0 -g -I $(INC_DIR)
memory: all
	@valgrind ./$(PROGRAM)

# generates the documentation
.PHONY: docs
docs:
	@doxygen -q $(DOC_DIR)/Doxyfile
	@firefox docs/html/index.html

# formates the code
.PHONY: fmt
fmt:
	@-clang-format -verbose -i $(SRC_DIR)/* $(INC_DIR)/*
	@shfmt -w -i 2 -l -ci .

# cleans the executable and the build directory
.PHONY: clean
clean:
	rm -r $(BLD_DIR)
	rm $(PROGRAM)

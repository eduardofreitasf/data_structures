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
PROGRAM=hash
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
debug: CFLAGS = -Wall -Wextra -pedantic -O0 -g
debug: all
	@gdb $(PROGRAM)

# generates the documentation
.PHONY: docs
docs:
	@doxygen $(DOC_DIR)/Doxyfile

# determines the complexity of each function in your code
.PHONY: complexity
complexity:
	@echo | pmccabe -v
	@pmccabe $(SRC_DIR)/*.c | sort -nr | awk '{if($$1>5)print}'

# gives advice on how to improve code
.PHONY: check
check:
	@cppcheck -I $(INC_DIR) --enable=all --suppress=missingIncludeSystem .

# generates hints to improve code
.PHONY: lint
lint:
	@splint -retvalint -hints -I $(INC_DIR) $(SRC_DIR)/*

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

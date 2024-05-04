# Use the GCC compiler
CC = gcc

# Turn on warnings and specify our C standard
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

# Optional bounds check
CFLAGS += -DENABLE_BOUNDS_CHECK

# Choose row or column major order here. 
# One of these MUST be uncommented.
#CFLAGS += -DROW_MAJOR_ORDER
CFLAGS += -DCOLUMN_MAJOR_ORDER

# Main library sources and targets
SRCS = matrix.c
OBJS = $(SRCS:.c=.o)
TARGET = matrix

# Test sources and targets
TEST_SRC = tests.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test_matrix

.PHONY: all clean

# Compilation rules
all: $(TARGET)

# This is set to compile a library instead of an executable.
# Since my matrix.c does not actaully contain a main function, this is needed.
# To compile the library, use the command `make`
$(TARGET): $(OBJS)
	ar rcs lib$(TARGET).a $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Test rules
test: $(TEST_TARGET)

# This is set to compile the tests as an executable and run them.
# To run the tests use the command `make test`
# Subsequent runs should happen AFTER a `make clean`, for example with `make clean && make test`
$(TEST_TARGET): $(OBJS) $(TEST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	./$(TEST_TARGET)

# Clean up by deleting unused files between runs
# To run the cleanup, run `make clean`
clean:
	rm -f $(OBJS) $(TARGET) lib$(TARGET).a $(TEST_OBJ) $(TEST_TARGET) 
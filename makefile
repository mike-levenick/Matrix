# Use the GCC compiler
CC = gcc

# Turn on warnings and specify our C standard
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

# Optional bounds check
CFLAGS += -DENABLE_BOUNDS_CHECK

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

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Test rules
test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	./$(TEST_TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)
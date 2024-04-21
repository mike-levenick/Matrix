CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

# Optional bounds check
CFLAGS += -DENABLE_BOUNDS_CHECK

SRCS = matrix.c
OBJS = $(SRCS:.c=.o)
TARGET = matrix

TEST_SRC = tests.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test_matrix

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Perform tests
test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	./$(TEST_TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)
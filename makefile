CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRCS = matrix.c
OBJS = $(SRCS:.c=.o)
TARGET = matrix

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
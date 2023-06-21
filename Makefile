CC=gcc
CFLAGS=-Wall -Wextra -Isrc

# Source files
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

# Application file
APP=Application/main

# Build target
TARGET=app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(APP).c -o $(TARGET)

%.o: %.CC	
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
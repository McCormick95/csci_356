CC = gcc
CFLAGS = -g -Wall -pthread
TARGET = war_networked
SRCS = war_networked.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

.PHONY: clean
clean:
	rm -f $(TARGET)
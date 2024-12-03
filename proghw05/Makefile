CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c scheduler.c my_queue.c
OBJS = $(SRCS:.c=.o)
TARGET = scheduler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
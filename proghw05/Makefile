# Author: Ryan McCormick
# Date: 10/06/2024
# Make file to compile all files for proghw05 

CC=gcc
PROGS=scheduler
CFLAGS=-std=c99 -Wall -g
LFLAGS=-lm

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
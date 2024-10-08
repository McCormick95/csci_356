CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99
DEPS = my_queue.h credit_rating.h
OBJ = my_queue.o credit_rating.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

credit_rating: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# .PHONY: clean

clean:
	rm -f *.o credit_rating
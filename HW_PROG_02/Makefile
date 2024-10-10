CFLAGS=-g -Wall
PROGS=credit_rating
OBJECTS=credit_rating.o my_queue.o
LDFLAGS=
CC=gcc

all: $(PROGS)

credit_rating: $(OBJECTS)
	$(CC) -o credit_rating $(OBJECTS) $(LDFLAGS)

credit_rating.o: credit_rating.c credit_rating.h my_queue.h
	$(CC) $(CFLAGS) -c credit_rating.c

my_queue.o: my_queue.c my_queue.h
	$(CC) $(CFLAGS) -c my_queue.c

clean:
	rm -f $(PROGS) *.o core*
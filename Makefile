CC = gcc
CFLAGS = -g -Wall
DEPS = mymalloc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

memtest: memtest.o mymalloc.o
	$(CC) -o $@ $^ $(CFLAGS)

memgrind: memgrind.o mymalloc.o
	$(CC) -o $@ $^ $(CFLAGS)
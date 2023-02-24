CC = gcc
CFLAGS = -g -Wall
DEPS = mymalloc.h
OBJ = memtest.o mymalloc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

memtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
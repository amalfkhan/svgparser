CC = gcc
CFLAGS = -Wall -std=c11 -Iinclude -I/usr/include/libxml2/ -lxml2 -lm -pedantic

MAKEOBJ: src/*.c include/*.h
	$(CC) $(CFLAGS) src/*.c test/*.c -o a

CLEAN:
	rm a

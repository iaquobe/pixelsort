
CC:=gcc
CFLAGS+=-g -o 

.PHONY: all clean

all: main

main: src/main.c src/lodepng.c src/compare.c src/pixelsort.c src/sort.c src/split.c
	$(CC) $(CFLAGS) $@ $^

clean: 
	rm main

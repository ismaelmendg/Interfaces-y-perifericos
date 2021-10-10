CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = cp.out
DEBUG = -g
SOURCES = cp.c

all:
	$(CC) $(SOURCES) $(CFLAGS) -O $(OUTPUT)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all

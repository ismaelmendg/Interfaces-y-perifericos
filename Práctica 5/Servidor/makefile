CC = gcc
CFLAGS = -Wall -lwiringPi
OUTPUT = practica5.out
DEBUG = -g
SOURCES = practica5.c

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all
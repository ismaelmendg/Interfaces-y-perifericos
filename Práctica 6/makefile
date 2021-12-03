CC = gcc
CFLAGS = -Wall -lwiringPi -lpthread
OUTPUT = practica6_prueba.out
DEBUG = -g
SOURCES = practica6_prueba.c

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all
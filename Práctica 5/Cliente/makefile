CC = gcc
CFLAGS = -Wall 
OUTPUT = client.out
RECORDS = Records.h
DEBUG = -g
SOURCES = client.c

all:
	$(CC) $(SOURCES) $(CFLAGS) $(RECORDS) -o $(OUTPUT)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) $(RECORDS) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all

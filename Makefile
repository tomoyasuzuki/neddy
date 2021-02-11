CC = gcc

all: 
	$(CC) -o neddy main.c 

clean: 
	rm -rf neddy
CC = gcc
TARGET = neddy
OBJECTS = main.o tap.o ether.o arp.o util.o icmp.o ip.o

all: 
	make $(TARGET)

%.o: %.c Makefile
	$(CC) -c $<

$(TARGET): $(OBJECTS) Makefile
	$(CC) -o $(TARGET) $(OBJECTS)

clean: 
	rm -rf $(TARGET) $(OBJECTS)
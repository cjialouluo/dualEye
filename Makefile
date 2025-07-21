CC=gcc
CFLAGS=-Wall -g
LIBS=-lgpiod

OBJS=main.o gc9d01.o spi.o gpio.o

all: gc9d01_demo

gc9d01_demo: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f *.o gc9d01_demo
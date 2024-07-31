CC = gcc
CFLAGS = -Wall -O2
LIBS = -lnet -lpcap

all: ip_spoofer

ip_spoofer: main.o spoof.o network.o utils.o
	$(CC) $(CFLAGS) -o ip_spoofer main.o spoof.o network.o utils.o $(LIBS)

main.o: main.c spoof.h network.h utils.h
	$(CC) $(CFLAGS) -c main.c

spoof.o: spoof.c spoof.h network.h utils.h
	$(CC) $(CFLAGS) -c spoof.c

network.o: network.c network.h utils.h
	$(CC) $(CFLAGS) -c network.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o ip_spoofer

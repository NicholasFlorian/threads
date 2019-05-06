CC = gcc
CFLAGS = -Wall -g -Iinclude/ -std=c11 

main: system


#system

system: system.o
	$(CC) $(CFLAGS) system.o -lpthread -o bin/system 

system.o:
	$(CC) $(CFLAGS) -c src/system.c

#------------------------------------------------------------------------------------

#Utility Funtions

clean:
	rm *.o
	rm bin/system


run:
	./bin/*

cclear:
	clear
	clear

r: cclear clean main run
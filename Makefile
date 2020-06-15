all: main.exe

CC = g++
INCLUDE = .
CFLAGS = -Wall -Wextra -std=gnu++14

main.exe: main.o Jonah.o STATE.o
	$(CC) -o main.exe main.o Jonah.o STATE.o
main.o: main.cpp 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.cpp
Jonah.o: Jonah.cpp Jonah.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Jonah.cpp
STATE.o: STATE.cpp STATE.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c STATE.cpp


clean:
	rm -f main.exe main.o Jonah.o STATE.o

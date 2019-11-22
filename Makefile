CC=g++
CFLAGS= -c -Wall -std=c++11
POSIXFLAG=-pthread -std=c++11

all: main

main: main.o Node.o List.o clockcalendar.o clock.o calendar.o InterfacePC.o Maquina.o
	$(CC) $(POSIXFLAG) main.cpp Node.o List.o clockcalendar.o clock.o calendar.o InterfacePC.o Maquina.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) $(POSIXFLAG) main.cpp

InterfacePC.o: InterfacePC.cpp
	$(CC) $(CFLAGS) InterfacePC.cpp

Maquina.o: Maquina.cpp
	$(CC) $(CFLAGS) Maquina.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) Node.cpp

List.o: List.cpp
	$(CC) $(CFLAGS) List.cpp

clockcalendar.o: clockcalendar.cpp
	$(CC) $(CFLAGS) clockcalendar.cpp

clock.o: clock.cpp
	$(CC) $(CFLAGS) clock.cpp

calendar.o: calendar.cpp
	$(CC) $(CFLAGS) calendar.cpp

clean:
	rm -rf *o main

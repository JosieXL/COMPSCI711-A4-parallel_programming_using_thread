b.out: main.o functions.o factorial.o
	g++ -o b.out main.o functions.o factorial.o
main.o: main.cpp
	g++ -o main.o -c main.cpp
functions.o: functions.cpp functions.h
	g++ -o functions.o -c functions.cpp
factorial.o: factorial.cpp factorial.h
	g++ -o factorial.o -c factorial.cpp

all: start

start: main.o method3.o
	g++ method3.o main.o -o start

main.o: main.cpp
	g++ -c main.cpp

method3.o: method3.h
	g++ -c method3.h

clean:
	rm -rf *.o start
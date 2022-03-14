# Makefile
CXX_FLAG = --std=c++11 -g

all: game

game: game.o cards.o
	g++ $(CXX_FLAG) -o game main.o cards.o

game.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

clean:
	rm -f game cards *.o

CC=g++
CFLAGS= -std=c++11

ageofwar: main.o parser.o game.o unit.o player.o model.o

parser: game.o model.o parser.cpp parser.hpp
	$(CC) -o 

game: unit.o player.o model.o game.cpp game.hpp
	$(CC) -o game.o $(CFLAGS)

unit: player.o model.o unit.cpp unit.hpp
	$(CC) -o unit.o -c unit.cpp player.o model.o $(CFLAGS)

player: player.cpp player.hpp
	$(CC) -o player.o -c player.cpp $(CFLAGS)

model: model.cpp model.hpp
	$(CC) -o model.o -c model.cpp $(CFLAGS) 

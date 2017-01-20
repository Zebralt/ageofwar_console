CC=g++
CFLAGS= -std=c++11

all: 
	$(CC) -o ageofwar *.cpp $(CFLAGS)

ageofwar: main.o parser.o game.o unit.o player.o model.o
	$(CC) -o $@ $^ $(CFLAGS)

parser: game.o player.o model.o parser.cpp parser.hpp
	$(CC) -o parser.o $^ $(CFLAGS)

unit: player.o model.o game.o unit.cpp unit.hpp
	$(CC) -o unit.o $^ $(CFLAGS)

game: player.o model.o game.cpp game.hpp
	$(CC) -o game.o $^ $(CFLAGS)

player: player.cpp player.hpp
	$(CC) -o player.o -c player.cpp $(CFLAGS)

model: model.cpp model.hpp
	$(CC) -o model.o -c model.cpp $(CFLAGS) 

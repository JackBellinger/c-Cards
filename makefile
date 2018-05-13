all: main clean

main: Main.o Deck.o Game.o
	g++ -std=c++11 Main.o Deck.o Game.o -o main
Main.o:
	g++ -std=c++11  -c Main.cpp
Deck.o:
	g++ -std=c++11  -c Deck.cpp
Game.o:
	g++ -std=c++11  -c Game.cpp
clean:
	rm -rf *o

all: main clean

main: Main.o Deck.o Game.o
	g++ Main.o Deck.o Game.o -o main
Main.o:
	g++ -c Main.cpp
Deck.o:
	g++ -c Deck.cpp
Game.o:
	g++ -c Game.cpp
clean:
	rm -rf *o

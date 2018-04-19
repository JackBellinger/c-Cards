all: main clean

main: Main.o Deck.o
	g++ Main.o Deck.o -o main
Main.o:
	g++ -c Main.cpp
Deck.o:
	g++ -c Deck.cpp
clean:
	rm -rf *o

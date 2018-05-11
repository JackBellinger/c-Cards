#ifndef CARDS_H
#define CARDS_H
#include <iostream>
using namespace std;

class Card
{
public:
	int rank;
	int suit;

	static const char spade[4];
	static const char club[4];
	static const char heart[4];
	static const char diamond[4];
	static const char* pics[4];

	Card(int r = 1, int s = 0){rank = r; suit = s;}

	bool operator == (const Card);
	bool operator != (const Card);
	bool operator > (const Card);
	bool operator >= (const Card);
	bool operator < (const Card);
	bool operator <= (const Card);
	//Card operator [] (int);
	
	friend ostream& operator << (ostream &stream, const Card &card);
};

class Deck
{
public:
	Card cards[52];
	int nextCard;
	
	void swap(int, int);

	Deck();
	void shuffle();
	Card drawCard();
	void printDeck();
};
#endif

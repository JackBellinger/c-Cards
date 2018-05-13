#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>
using namespace std;

class Card
{
public:
	int rank;
	int suit;

	static const string spade;
	static const string club;
	static const string heart;
	static const string diamond;
	static const string pics[4];

	static const string startColor;
	static const string endColor;
	static const string blankLine;
	string oneSuitLine;
	string twoSuitLine;

	Card(int r = 1, int s = 0);
	string getRow(int);

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
